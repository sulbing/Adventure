#include "stdafx.h"
#include "mainGame.h"

void mainGame::addImage()
{
	//페이드 인아웃
	IMAGEMANAGER->addImage("BLACK", "Image/BLACK.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));

	//오프닝
	IMAGEMANAGER->addImage("START", "Image/START.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//월드맵
	IMAGEMANAGER->addImage("WORLDMAP", "Image/WORLDMAP.bmp", 2800, 2330, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("WORLDMAP_PIXEL_COLLISION", "Image/WORLDMAP_PIXEL_COLLISION.bmp", 2800, 2330, true, RGB(255, 0, 255));

	//워터님프
	IMAGEMANAGER->addImage("savePointCollision", "Image/NYMPH_PIXEL_COLLISION.bmp", 860, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("savePoint", "Image/WATTERNYMPH_BACKGROUND.bmp", 860, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("nymph", "Image/WATTERNYMPH.bmp", 1752, 148, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("X", "Image/X.bmp", 38, 37, true, RGB(255, 0, 255));

	//스테이지1
	IMAGEMANAGER->addImage("STAGE1", "Image/STAGE1_GROUND.bmp", 6379, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE1_PIXEL_COLLISION", "Image/STAGE1_GROUND_PIXEL_COLLISION.bmp", 6379, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE_BACKGROUND", "Image/STAGE_BACKGROUND.bmp", 1600, 480, true, RGB(255, 0, 255));

	//스테이지2
	IMAGEMANAGER->addImage("STAGE2", "Image/STAGE2_GROUND.bmp", 6656, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE2_PIXEL_COLLISION", "Image/STAGE2_GROUND_PIXEL_COLLISION.bmp", 6656, 480, true, RGB(255, 0, 255));

	//스테이지3
	IMAGEMANAGER->addImage("STAGE3", "Image/STAGE3_GROUND.bmp", 6379, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("STAGE3_PIXEL_COLLISION", "Image/STAGE3_GROUND_PIXEL_COLLISION.bmp", 6379, 480, true, RGB(255, 0, 255));

	//보스 스테이지
	IMAGEMANAGER->addImage("BOSS_STAGE", "Image/FINALBOSS_STAGE.bmp", 800, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ENDING", "Image/엔딩.bmp", 800, 480, true, RGB(255, 0, 255));

	//체스트스테이지
	IMAGEMANAGER->addImage("CHEST_STAGE_BACKGROUND", "Image/CHESTSTAGE_BACKGROUND.bmp", 1150, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("CHEST_STAGE_PIXEL_COLLISION", "Image/CHESTSTAGE_PIXEL_COLLISION.bmp", 1150, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("DARK_FOREST_STAGE", "Image/DARK_FOREST_STAGE.bmp", 800, 480, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("CHEST_IDLE", "Image/CHEST_IDLE.bmp", 58, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("CHEST_OPEN", "Image/CHEST_OPEN.bmp", 58, 56, true, RGB(255, 0, 255));

	//인벤토리씬, 아이템
	IMAGEMANAGER->addImage("INVENTORY", "Image/INVENTORY.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ITEM", "Image/ITEM.bmp", 192, 384, 3, 6, true, RGB(255, 0, 255));

	//스테이터스 씬
	IMAGEMANAGER->addImage("STATUS", "Image/STATUS.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("STAR", "Image/STAR.bmp", 68, 36, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PLUS", "Image/PLUS.bmp", 34, 36, true, RGB(255, 0, 255));

	//에너미
	IMAGEMANAGER->addFrameImage("bigWorm", "Image/bigWorm.bmp", 2860, 2880, 11, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("liileWorm", "Image/liitleWorm.bmp", 1602, 712, 18, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bullet", "Image/BOSS_BULLET.bmp", 320, 40, 8, 1, true, RGB(255, 0, 255));


	//미니맵
	IMAGEMANAGER->addImage("MINIMAP", "Image/MINIMAP.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("MINIMAP_FINN", "Image/MINIMAP_FINN.bmp", 20, 20, true, RGB(255, 0, 255));

	//UI
	IMAGEMANAGER->addFrameImage("UI_HEART", "Image/UI_HEART.bmp", 200, 46, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_HEART_END", "Image/UI_HEART_END.bmp", 25, 46, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_HEART_0", "Image/UI_HEART_0.bmp", 40, 46, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_HEART_1", "Image/UI_HEART_1.bmp", 40, 46, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_HEART_2", "Image/UI_HEART_2.bmp", 40, 46, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_HEART_3", "Image/UI_HEART_3.bmp", 40, 46, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_HEART_4", "Image/UI_HEART_4.bmp", 40, 46, true, RGB(255, 0, 255));
}