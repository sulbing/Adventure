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

	DATABASE->setstatus(0, 0, 0, 1, 5);


	SCENEMANAGER->addScene("SCENE_OPENEING", new openingScene);
	SCENEMANAGER->addScene("SCENE_WORLDMAP", new worldMapScene);
	SCENEMANAGER->addScene("SCENE_SAVE_POINT", new nymphStage);
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
	if (KEYMANAGER->isOnceKeyDown('U'))
	{
		DATABASE->changeInven();
	}
	KEYANIMANAGER->update();
	if(!DATABASE->getInvenOn()) SCENEMANAGER->update();
	else DATABASE->getInterface()->update();
}

//������ ���⿡�� �׷��� 
void mainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ������� ================

	if (!DATABASE->getInvenOn()) SCENEMANAGER->render();
	else DATABASE->getInterface()->render();

	//TIMEMANAGER->render(getMemDC());

	//===============�Ʒ��� �ǵ������� =================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
