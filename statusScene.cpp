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
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		changeScene();
		if (DATABASE->getStatusBonus() != 0 )
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
	

	starOn();

	
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

void statusScene::starOn(void)
{
	int H = DATABASE->getStatusHearts();
	int A = DATABASE->getStatusAttack();
	int S = DATABASE->getStatusSpeed();

	for (int i = 0; i < 4; i++)
	{
		if (i < H) _Slot[i].On = true;
		else _Slot[i].On = false;
	}

	for (int i = 4; i < 8; i++)
	{
		if (i - 4 < A) _Slot[i].On = true;
		else _Slot[i].On = false;
	}

	for (int i = 8; i < 12; i++)
	{
		if (i - 8 < S) _Slot[i].On = true;
		else _Slot[i].On = false;
	}
}

void statusScene::changeScene(void)
{
	RECT _rcSelect[4];
	for (int i = 0; i < 4; i++)
	{
		_rcSelect[i] = RectMake(717, 43 + 108 * i, 83, 100);
	}

	for (int i = 0; i < 4; i++)
	{
		if (PtInRect(&_rcSelect[i], _ptMouse))
		{
			if (i != 0 && i != 3)
			{
				DATABASE->changeNum(i);
			}
		}
	}
}