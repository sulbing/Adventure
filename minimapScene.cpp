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
	_x = 135+DATABASE->getWorldstate().x / 6.297297 + 4 ;
	_y = 81+DATABASE->getWorldstate().y / 6.297297 - 4 ;

	_rc = RectMakeCenter(_x, _y, _face->getWidth(), _face->getHeight());

	changeScene();
}

void minimapScene::render()	
{
	_worldMap->render(getMemDC(), 0, 0);
	_face->render(getMemDC(), _rc.left, _rc.top);

}

void minimapScene::changeScene(void)
{
	RECT _rcSelect[4];
	for (int i = 0; i < 4; i++)
	{
		_rcSelect[i] = RectMake(717, 43 + 108 * i, 83, 100);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 4; i++)
		{
			if (PtInRect(&_rcSelect[i], _ptMouse))
			{
				if (i != 2 && i != 3)
				{
					DATABASE->changeNum(i);
				}
			}
		}
	}
}