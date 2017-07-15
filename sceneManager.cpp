#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

DWORD CALLBACK loadingThread(LPVOID prc)
{
	//사용될 씬(체인지가 일어날 씬)을 셋팅해놓고
	sceneManager::_readyScene->init();

	// 현재 씬에 대입해준다
	sceneManager::_currentScene = sceneManager::_readyScene;

	sceneManager::_loadingScene->release();
	sceneManager::_loadingScene = NULL;
	sceneManager::_readyScene = NULL;

	return 0;
}

gameNode* sceneManager::_currentScene = NULL;
gameNode* sceneManager::_loadingScene = NULL;
gameNode* sceneManager::_readyScene = NULL;

sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{

}

HRESULT sceneManager::init(void)
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;

	return S_OK;
}

void sceneManager::release(void)
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->release();

			SAFE_DELETE(miSceneList->second);

			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	_mSceneList.clear();
}

void sceneManager::update(void)
{
	if (_currentScene) _currentScene->update();
}

void sceneManager::render(void)
{
	if (_currentScene) _currentScene->render();
}


//씬 추가하는 함수
gameNode* sceneManager::addScene(string sceneName, gameNode* scene)
{
	//해당 씬이 없다면 널 처리
	if (!scene) return NULL;

	//	맵에 추가한다 				  키값       씬
	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;

}


gameNode* sceneManager::addLoadingScene(string loadingSceneName, gameNode* scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}


HRESULT sceneManager::changeScene(string sceneName)
{
	//이터레이터로        찾고자하는 키값을 대입받는다
	mapSceneIter find = _mSceneList.find(sceneName);

	//이터레이터가 끝과 같다면      없다고 반환
	if (find == _mSceneList.end()) return E_FAIL;

	//이터레이터가 현재씬	         바꿀필요 없죠
	if (find->second == _currentScene) return S_OK;

	//찾았다면 해당 씬을 초기화
	if (SUCCEEDED(find->second->init()))
	{
		if (_currentScene) _currentScene->release();

		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}

HRESULT sceneManager::changeScene(string sceneName, string loadingSceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;

	if (find->second == _currentScene) return S_OK;

	mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);

	if (find == _mLoadingSceneList.end()) return changeScene(loadingSceneName);

	if (SUCCEEDED(find->second->init()))
	{
		if (_currentScene) _currentScene->release();

		_loadingScene = findLoading->second;

		_readyScene = find->second;

		CloseHandle(CreateThread(NULL, 0, loadingThread, NULL, 0, &_loadingThreadID));
	}

	return E_FAIL;
}


