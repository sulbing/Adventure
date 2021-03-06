#include "stdafx.h"
#include "mainGame.h"

//======================================
// 생성자랑 소멸자는 쓰지 않는다
//======================================
mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}


//======================================
// 생성자랑 소멸자는 쓰지 않는다
//======================================


//초기화는 앞으로 여기에다가 해라
HRESULT mainGame::init(void)
{
	gameNode::init(true);
	addImage();
	addSound();

	DATABASE->init();

	DATABASE->setstatus(0, 0, 0, 0, 8);


	SCENEMANAGER->addScene("SCENE_OPENEING", new openingScene);
	SCENEMANAGER->addScene("SCENE_WORLDMAP", new worldMapScene);
	SCENEMANAGER->addScene("SCENE_SAVE_POINT", new nymphStage);
	SCENEMANAGER->addScene("STAGE1", new stage1);
	SCENEMANAGER->addScene("STAGE2", new stage2);
	SCENEMANAGER->addScene("STAGE3", new stage3);
	SCENEMANAGER->addScene("CHEST_STAGE", new cheststage);
	SCENEMANAGER->addScene("DARK_FOREST_SCENE", new darkForest);
	SCENEMANAGER->addScene("BOSS_SCENE", new bossScene);

	SCENEMANAGER->changeScene("SCENE_OPENEING");

	return S_OK;
}

//메모리 해제는 앞으로 여기에다가 해라
void mainGame::release(void)
{
	gameNode::release();

}

//연산은(는) 앞으로 여기에다가 해라
void mainGame::update(void)
{
	gameNode::update();
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		DATABASE->changeInven();
	}
	KEYANIMANAGER->update();
	if(!DATABASE->getInvenOn()) SCENEMANAGER->update();
	else DATABASE->getInterface()->update();
}

//앞으로 여기에다 그려라 
void mainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지마라 ================

	if (!DATABASE->getInvenOn()) SCENEMANAGER->render();
	else DATABASE->getInterface()->render();

	//TIMEMANAGER->render(getMemDC());

	//===============아래도 건들지마라 =================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
