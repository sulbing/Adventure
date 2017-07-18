#include "stdafx.h"
#include "worldMapScene.h"


worldMapScene::worldMapScene() {}
worldMapScene::~worldMapScene() {}


HRESULT worldMapScene::init(void)
{

	_background = IMAGEMANAGER->findImage("WORLDMAP");
	_mapSizeWidth = _background->getWidth();
	_mapSizeHeight = _background->getHeight();

	_cameraX = _cameraY = 0;

	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;

	return S_OK;
}

void worldMapScene::release(void)
{

}

void worldMapScene::update(void)
{

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _x -= 5;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _x += 5;
	if (KEYMANAGER->isStayKeyDown(VK_UP)) _y -= 5;
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) _y += 5;

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SCENEMANAGER->changeScene("SCENE_SAVE_POINT");
	}
}

void worldMapScene::render(void)
{
	IMAGEMANAGER->findImage("WORLDMAP")->render(getMemDC(), 0, 0, _cameraX, _cameraY, WINSIZEX, WINSIZEY);
}
