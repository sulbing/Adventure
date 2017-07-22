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

	//스테이지1
	IMAGEMANAGER->addImage("STAGE1", "Image/STAGE1_GROUND.bmp", 6379, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE1_PIXEL_COLLISION", "Image/STAGE1_GROUND_PIXEL_COLLISION.bmp", 6379, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE_BACKGROUND", "Image/STAGE_BACKGROUND.bmp", 1600, 480, true, RGB(255, 0, 255));

	//스테이지2
	IMAGEMANAGER->addImage("STAGE2", "Image/STAGE1_GROUND.bmp", 6656, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE2_PIXEL_COLLISION", "Image/STAGE1_GROUND_PIXEL_COLLISION.bmp", 6656, 480, true, RGB(255, 0, 255));

	//스테이지3
	IMAGEMANAGER->addImage("STAGE3", "Image/STAGE1_GROUND.bmp", 6379, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE3_PIXEL_COLLISION", "Image/STAGE1_GROUND_PIXEL_COLLISION.bmp", 6379, 480, true, RGB(255, 0, 255));

	//인벤토리씬, 아이템
	IMAGEMANAGER->addImage("INVENTORY", "Image/INVENTORY.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ITEM", "Image/ITEM.bmp", 192, 384, 3, 6, true, RGB(255, 0, 255));

	//스테이터스 씬
	IMAGEMANAGER->addImage("STATUS", "Image/STATUS.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("STAR", "Image/STAR.bmp", 68, 36, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PLUS", "Image/PLUS.bmp", 34, 36, true, RGB(255, 0, 255));

	//에너미
	IMAGEMANAGER->addFrameImage("minion1", "Image/minion1.bmp", 535, 568, 5, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("minion2", "Image/minion2.bmp", 890, 890, 10, 10, true, RGB(255, 0, 255));

	//미니맵
	IMAGEMANAGER->addImage("MINIMAP", "Image/MINIMAP.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MINIMAP_FINN", "Image/MINIMAP_FINN.bmp", 20, 20, true, RGB(255, 0, 255));
}