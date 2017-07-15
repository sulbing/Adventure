#pragma once
#include "singletonBase.h"
#include <string>
#include <map>

class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
public:
	// iOS -> vector NSMUTABLEARRAY // map -> NSMUTBLEDICTIONARY

	//          first(키 값)    second(자료)
	typedef map<string, gameNode*> mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;

private:
	static gameNode* _currentScene;
	static gameNode* _loadingScene;
	static gameNode* _readyScene;

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	DWORD _loadingThreadID;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//씬 추가하는 함수
	gameNode* addScene(string sceneName, gameNode* scene);

	gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	HRESULT changeScene(string sceneName);
	HRESULT changeScene(string sceneName, string loadingSceneName);

	friend DWORD CALLBACK loadingThread(LPVOID prc);

	sceneManager();
	~sceneManager();
};

