#include "stdafx.h"
#include "cheststage.h"


HRESULT cheststage::init(void)
{
	_UI = new UI;
	_UI->init();

	_leftDoor = RectMake(0, WINSIZEY / 2, 10, 400);
	_rightDoor = RectMake(790, WINSIZEY / 2, 10, 400);

	_stageFinn = new stagePlayer;
	_stageFinn->init(2, 0, 0, 8, 30, WINSIZEY * 3 / 4, true);

	_sceneEffect = new sceneEffect;
	_sceneEffect->init();
	if (!_chestOpen)
	{
		_item = new item;
		_itemNum = RND->getFromIntTo(0, 2);
		_item->setXY(WINSIZEX / 2, WINSIZEY - 100);
		_item->init((ITEMLIST)_itemNum, _item->getX(), _item->getY());
	}
	_isChange = false;

	_chestRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 88, 58, 56);
	
	return S_OK;
}

void cheststage::release(void)
{
}

void cheststage::update(void)
{
	_sceneEffect->update();

	chestOpen();
	//�� ������Ʈ
	if (!_isChange) _stageFinn->update();
	pixelCollision();
	stageDoor();
	if (_chestOpen)
	{
		if (_item)
		{
			_item->update();
			eatItem();
		}
	}
	_UI->update();
}

void cheststage::render(void)
{
	IMAGEMANAGER->findImage("CHEST_STAGE_PIXEL_COLLISION")->render(getMemDC(), 0, 0, 0, 0, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("CHEST_STAGE_BACKGROUND")->render(getMemDC(), 0, 0, 0, 0, WINSIZEX, WINSIZEY);
	if (_chestOpen == false)
	{
		IMAGEMANAGER->findImage("CHEST_IDLE")->render(getMemDC(), WINSIZEX / 2 - (58 / 2), WINSIZEY - 60 - 56);
	}
	else if (_chestOpen == true)
	{
		IMAGEMANAGER->findImage("CHEST_OPEN")->render(getMemDC(), WINSIZEX / 2 - (58 / 2), WINSIZEY - 60 - 56);
	}

	//�� ����
	_stageFinn->render();

	_stageFinn->setCamX(0);
	
	_sceneEffect->render();
	if (_chestOpen) if(_item) _item->render(_item->getX(), _item->getY());
	_UI->render();
}

void cheststage::pixelCollision(void)
{
	if (_stageFinn->getState() == JUMP || _stageFinn->getState() == HIT || _stageFinn->getState() == JUMPATTACK)
	{
		if (_stageFinn->getSpeedY() >= 0)
		{
			for (int i = _stageFinn->getY() + _stageFinn->getHeight() / 2 - 10; i < _stageFinn->getY() + _stageFinn->getHeight() / 2; ++i)
			{
				COLORREF color = GetPixel(IMAGEMANAGER->findImage("savePointCollision")->getMemDC(), _stageFinn->getX(), i);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				if ((r == 0 && g == 0 && b == 255))
				{
					_stageFinn->setY(i - _stageFinn->getHeight() / 2);
					if (KEYMANAGER->isStayKeyDown(VK_RIGHT) || KEYMANAGER->isStayKeyDown(VK_LEFT)) _stageFinn->setState(WALK);
					else _stageFinn->setState(IDLE);
					break;
				}
			}
		}
	}

	else if (_stageFinn->getState() == WALK || _stageFinn->getState() == IDLE)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("savePointCollision")->getMemDC(), _stageFinn->getX(), _stageFinn->getY() + _stageFinn->getHeight() / 2);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 0 && g == 0 && b == 255))
		{
			_stageFinn->setState(JUMP);
		}

	}
}

void cheststage::stageDoor(void)
{

	RECT temp;

	if (IntersectRect(&temp, &_leftDoor, &_stageFinn->getBodyRC()))
	{
		_isChange = true;
		_sceneEffect->setFadeOUT(true);

		//�� ��ȯ ������ �� ü����
		if (!_sceneEffect->getChangeScene())
		{
			SCENEMANAGER->changeScene("SCENE_WORLDMAP");
		}
	}

	else if (IntersectRect(&temp, &_rightDoor, &_stageFinn->getBodyRC()))
	{
		_isChange = true;
		_sceneEffect->setFadeOUT(true);

		//�� ��ȯ ������ �� ü����
		if (!_sceneEffect->getChangeScene())
		{
			SCENEMANAGER->changeScene("SCENE_WORLDMAP");
		}
		_stageFinn->setSpeedX(0);
	}
}

void cheststage::chestOpen(void)
{
	RECT temp;
	for (int i = DEFAULT; i < SKILLEND; i++)
	{
		if (IntersectRect(&temp, &_stageFinn->getSkillHitBox(i), &_chestRc))
		{
			_chestOpen = true;
		}
	}
}

void cheststage::eatItem(void)
{
	RECT temp;

	if (IntersectRect(&temp, &_stageFinn->getBodyRC(), &_item->getRect()))
	{
		_stageFinn->setState(HIT);
		DATABASE->pushbackaddVector(_itemNum);
		SAFE_DELETE(_item);
	}
}

cheststage::cheststage()
{
}


cheststage::~cheststage()
{
}
