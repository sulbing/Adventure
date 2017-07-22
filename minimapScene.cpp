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
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	return S_OK;
}

void minimapScene::release() 
{

}

void minimapScene::update()	 
{

}

void minimapScene::render()	
{
	_worldMap->render(getMemDC(), 0, 0);
	_face->render(getMemDC(), DATABASE->getWorldstate().x, DATABASE->getWorldstate().y);

}