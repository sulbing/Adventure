#include "stdafx.h"
#include "mainGame.h"

//======================================
// �����ڶ� �Ҹ��ڴ� ���� �ʴ´�
//======================================
mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}


//======================================
// �����ڶ� �Ҹ��ڴ� ���� �ʴ´�
//======================================


//�ʱ�ȭ�� ������ ���⿡�ٰ� �ض�
HRESULT mainGame::init(void)
{
	gameNode::init(true);

	addImage();
	DATABASE->init();

	SCENEMANAGER->addScene("SCENE_OPENEING", new openingScene);
	SCENEMANAGER->addScene("SCENE_WORLDMAP", new worldMapScene);
	SCENEMANAGER->addScene("SCENE_SAVE_POINT", new nymphStage);
	SCENEMANAGER->addScene("SCENE_INVENTORY", new inventoryScene);
	SCENEMANAGER->addScene("SCENE_STATUS", new statusScene);
	SCENEMANAGER->addScene("SCENE_MINIMAP", new minimapScene);
	SCENEMANAGER->addScene("STAGE1", new stage1);
	SCENEMANAGER->addScene("STAGE2", new stage2);
	SCENEMANAGER->addScene("STAGE3", new stage3);
	SCENEMANAGER->addScene("CHEST_STAGE", new cheststage);

	SCENEMANAGER->changeScene("SCENE_OPENEING");

	return S_OK;
}

//�޸� ������ ������ ���⿡�ٰ� �ض�
void mainGame::release(void)
{
	gameNode::release();

}

//������(��) ������ ���⿡�ٰ� �ض�
void mainGame::update(void)
{
	gameNode::update();

	SCENEMANAGER->update();
}

//������ ���⿡�� �׷��� 
void mainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ������� ================

	SCENEMANAGER->render();

	//TIMEMANAGER->render(getMemDC());

	//===============�Ʒ��� �ǵ������� =================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
