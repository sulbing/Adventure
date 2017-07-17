#include "stdafx.h"
#include "worldMapScene.h"


worldMapScene::worldMapScene() {}
worldMapScene::~worldMapScene() {}


HRESULT worldMapScene::init(void)
{
	IMAGEMANAGER->addImage("WORLDMAP", "Image/WORLDMAP.bmp", 2600, 2130, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("WORLDMAP_PIXEL_COLLISION", "Image/ WORLDMAP_PIXEL_COLLISION.bmp", 2600, 2130, true, RGB(255, 0, 255));

	_cameraX = _cameraY = 0;
	return S_OK;
}

void worldMapScene::release(void)
{

}

void worldMapScene::update(void)
{

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _cameraX -= 5;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _cameraX += 5;
	if (KEYMANAGER->isStayKeyDown(VK_UP)) _cameraY -= 5;
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) _cameraY += 5;

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SCENEMANAGER->changeScene("SCENE_SAVE_POINT");
	}
}

void worldMapScene::render(void)
{
	IMAGEMANAGER->findImage("WORLDMAP")->render(getMemDC(), 0, 0, _cameraX, _cameraY, WINSIZEX, WINSIZEY);
}
