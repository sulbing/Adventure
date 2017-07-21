#include "stdafx.h"
#include "statusScene.h"


statusScene::statusScene()
{
}


statusScene::~statusScene()
{
}


HRESULT statusScene::init()
{
	_background = IMAGEMANAGER->findImage("STATUS");
	_star = IMAGEMANAGER->findImage("STAR");
	_plus = IMAGEMANAGER->findImage("PLUS");

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_Slot[i * 4 + j].starSlot = PointMake(425 + _star->getFrameWidth() * j, 157 + (_star->getFrameHeight() + 23)*i);
			_Slot[i * 4 + j].On = false;
			_Slot[i * 4 + j].rcSlot = RectMake(_Slot[i * 4 + j].starSlot.x, _Slot[i * 4 + j].starSlot.y, _star->getFrameWidth(), _star->getFrameHeight());
		}
	}

	for (int i = 0; i < 3; i++)
	{
		_Slot[12+i].starSlot = { _Slot[12 + i - 3 * (3 - i)].starSlot.x + _star->getFrameWidth()+10, _Slot[12 + i - 3 * (3 - i)].starSlot.y };
		_Slot[12+i].On = false;
		_Slot[12+i].rcSlot = RectMake(_Slot[12+i].starSlot.x, _Slot[12+i].starSlot.y, _plus->getWidth(), _plus->getHeight());
	}
	

	return S_OK;
}

void statusScene::release()
{


}

void statusScene::update()
{
	if (DATABASE->getStatusBonus() != 0 && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 12; i < 15; i++)
		{
			if (PtInRect(&_Slot[i].rcSlot, _ptMouse))
			{
				DATABASE->useBonus(i);
			}
		}
	}
}

void statusScene::render()
{
	_background->render(getMemDC(), 0, 0);
	for (int i = 0; i < 12; i++)
	{
		switch (_Slot[i].On)
		{
			case false :
			{
				_star->frameRender(getMemDC(), _Slot[i].starSlot.x, _Slot[i].starSlot.y, 1, 0);
			}
			break;
			case true:
			{
				_star->frameRender(getMemDC(), _Slot[i].starSlot.x, _Slot[i].starSlot.y, 0, 0);
			}
			break;
		}
	}

	if(DATABASE->getStatusBonus()!=0)
	{
		for (int i = 12; i < 15; i++)
		{
			_plus->render(getMemDC(), _Slot[i].starSlot.x, _Slot[i].starSlot.y);
		}
	}
}
