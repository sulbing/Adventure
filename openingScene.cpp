#include "stdafx.h"
#include "openingScene.h"


openingScene::openingScene(){}
openingScene::~openingScene(){}


HRESULT openingScene::init(void)
{
	return S_OK;
}

void openingScene::release(void)	  
{

}

void openingScene::update(void)		  
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SCENEMANAGER->changeScene("SCENE_WORLDMAP");
	}
}

void openingScene::render(void)		  
{
	IMAGEMANAGER->findImage("START")->render(getMemDC(), 0, 0);
}

