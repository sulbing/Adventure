#include "stdafx.h"
#include "openingScene.h"


openingScene::openingScene(){}
openingScene::~openingScene(){}


HRESULT openingScene::init(void)
{
	_sceneEffect = new sceneEffect;
	_sceneEffect->init();

	return S_OK;
}

void openingScene::release(void)	  
{

}

void openingScene::update(void)		  
{
	_sceneEffect->update();

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_sceneEffect->setFadeOUT(true);
	}
	//¾À ÀüÈ¯ ³¡³ª¸é ¾À Ã¼ÀÎÁö
	if (!_sceneEffect->getChangeScene() && !_sceneEffect->isFadeOUT())
	{
		SCENEMANAGER->changeScene("SCENE_WORLDMAP");
	}
}

void openingScene::render(void)		  
{
	IMAGEMANAGER->findImage("START")->render(getMemDC(), 0, 0);

	_sceneEffect->render();
}

