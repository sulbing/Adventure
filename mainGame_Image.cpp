#include "stdafx.h"
#include "mainGame.h"

void mainGame::addImage()
{
	//¿ÀÇÁ´×
	IMAGEMANAGER->addImage("START", "Image/START.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//¿ùµå¸Ê
	IMAGEMANAGER->addImage("WORLDMAP", "Image/WORLDMAP.bmp", 2600, 2130, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("WORLDMAP_PIXEL_COLLISION", "Image/ WORLDMAP_PIXEL_COLLISION.bmp", 2600, 2130, true, RGB(255, 0, 255));

	//¿öÅÍ´ÔÇÁ
	IMAGEMANAGER->addImage("savePointCollision", "Image/NYMPH_PIXEL_COLLISION.bmp", 860, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("savePoint", "Image/WATTERNYMPH_BACKGROUND.bmp", 860, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("nymph", "Image/WATTERNYMPH.bmp", 1752, 148, 6, 1, true, RGB(255, 0, 255));

}