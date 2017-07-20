#include "stdafx.h"
#include "mainGame.h"

void mainGame::addImage()
{
	//페이드 인아웃
	IMAGEMANAGER->addImage("BLACK", "Image/BLACK.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));

	//오프닝
	IMAGEMANAGER->addImage("START", "Image/START.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//월드맵
	IMAGEMANAGER->addImage("WORLDMAP", "Image/WORLDMAP.bmp", 2600, 2130, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("WORLDMAP_PIXEL_COLLISION", "Image/WORLDMAP_PIXEL_COLLISION.bmp", 2600, 2130, true, RGB(255, 0, 255));

	//워터님프
	IMAGEMANAGER->addImage("savePointCollision", "Image/NYMPH_PIXEL_COLLISION.bmp", 860, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("savePoint", "Image/WATTERNYMPH_BACKGROUND.bmp", 860, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("nymph", "Image/WATTERNYMPH.bmp", 1752, 148, 6, 1, true, RGB(255, 0, 255));

	//인벤토리씬, 아이템
	IMAGEMANAGER->addImage("INVENTORY", "Image/INVENTORY.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ITEM", "Image/ITEM.bmp", 192, 384, 3, 6, true, RGB(255, 0, 255));
	//에너미
	IMAGEMANAGER->addFrameImage("minion1", "Image/minion1.bmp", 535, 568, 5, 8, true, RGB(255, 0, 255));
}