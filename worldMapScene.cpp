#include "stdafx.h"
#include "worldMapScene.h"


worldMapScene::worldMapScene(){}
worldMapScene::~worldMapScene(){}


HRESULT worldMapScene::init(void)
{

	return S_OK;
}

void worldMapScene::release(void)
{

}

void worldMapScene::update(void) 
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SCENEMANAGER->changeScene("SCENE_SAVE_POINT");
	}

}

void worldMapScene::render(void) 
{

}
