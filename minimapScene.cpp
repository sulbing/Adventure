#include "stdafx.h"
#include "minimapScene.h"


minimapScene::minimapScene()
{
}


minimapScene::~minimapScene()
{
}

HRESULT minimapScene::init()
{

	_worldMap = IMAGEMANAGER->findImage("MINIMAP");
	_face = IMAGEMANAGER->findImage("MINIMAP_FINN"); 
	return S_OK;
}

void minimapScene::release() 
{

}

void minimapScene::update()	 
{
	_x = 135+DATABASE->getWorldstate().x / 5.756756 + 4 ;
	_y = 81+DATABASE->getWorldstate().y / 5.756756 ;

	_rc = RectMakeCenter(_x, _y, _face->getWidth(), _face->getHeight());

	if (KEYMANAGER->isOnceKeyDown('1')) SCENEMANAGER->changeScene("SCENE_WORLDMAP");
}

void minimapScene::render()	
{
	_worldMap->render(getMemDC(), 0, 0);
	_face->render(getMemDC(), _rc.left, _rc.top);

}