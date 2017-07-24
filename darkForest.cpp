#include "stdafx.h"
#include "darkForest.h"


darkForest::darkForest()
{
}


darkForest::~darkForest()
{
}

HRESULT darkForest::init(void)
{
	_UI = new UI;
	_UI->init();


	_leftDoor = RectMake(0, WINSIZEY / 2, 10, 400);
	_rightDoor = RectMake(790, WINSIZEY / 2, 10, 400);

	_stageFinn = new stagePlayer;
	_stageFinn->init(DATABASE->getStatusHearts(), DATABASE->getStatusAttack(), DATABASE->getStatusSpeed(), DATABASE->getStatusCureentHP(), 30, WINSIZEY * 3 / 4, true);

	_sceneEffect = new sceneEffect;
	_sceneEffect->init();
	if (!_chestOpen)
	{
		_item = new item;
		_itemNum = 15;
		_item->setXY(WINSIZEX / 2, WINSIZEY - 100);
		_item->init((ITEMLIST)_itemNum, _item->getX(), _item->getY());
	}
	_isChange = _isChest = false;

	_chestRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 88, 58, 56);

	SOUNDMANAGER->play("보물상자", 0.3f);

	return S_OK;
}

void darkForest::release(void)
{
}

void darkForest::update(void)
{
	_sceneEffect->update();

	chestOpen();
	//핀 업데이트
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

void darkForest::render(void)
{
	IMAGEMANAGER->findImage("CHEST_STAGE_PIXEL_COLLISION")->render(getMemDC(), 0, 0, 0, 0, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("DARK_FOREST_STAGE")->render(getMemDC(), 0, 0, 0, 0, WINSIZEX, WINSIZEY);
	if (_chestOpen == false)
	{
		IMAGEMANAGER->findImage("CHEST_IDLE")->render(getMemDC(), WINSIZEX / 2 - (58 / 2), WINSIZEY - 60 - 56);
	}
	else if (_chestOpen == true)
	{
		IMAGEMANAGER->findImage("CHEST_OPEN")->render(getMemDC(), WINSIZEX / 2 - (58 / 2), WINSIZEY - 60 - 56);
	}

	if (_isChest)
	{
		IMAGEMANAGER->findImage("X")->render(getMemDC(), _chestRc.left + 8, _chestRc.top - 80);
	}

	//핀 랜더
	_stageFinn->render();

	_stageFinn->setCamX(0);

	_sceneEffect->render();
	if (_chestOpen) if (_item) _item->render(_item->getX(), _item->getY());
	_UI->render();
}

void darkForest::pixelCollision(void)
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

void darkForest::stageDoor(void)
{
	RECT temp;

	if (IntersectRect(&temp, &_leftDoor, &_stageFinn->getBodyRC()))
	{
		SOUNDMANAGER->stop("보물상자");

		_isChange = true;
		_sceneEffect->setFadeOUT(true);

		//씬 전환 끝나면 씬 체인지
		if (!_sceneEffect->getChangeScene())
		{
			SCENEMANAGER->changeScene("SCENE_WORLDMAP");
		}
	}

	else if (IntersectRect(&temp, &_rightDoor, &_stageFinn->getBodyRC()))
	{
		SOUNDMANAGER->stop("보물상자");

		_isChange = true;
		_sceneEffect->setFadeOUT(true);

		//씬 전환 끝나면 씬 체인지
		if (!_sceneEffect->getChangeScene())
		{
			SCENEMANAGER->changeScene("SCENE_WORLDMAP");
		}
	}
}

void darkForest::chestOpen(void)
{
	RECT temp;

	if (IntersectRect(&temp, &_stageFinn->getBodyRC(), &_chestRc))
	{
		_isChest = true;

		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			_chestOpen = true;
		}
	}
	else _isChest = false;
}

void darkForest::eatItem(void)
{
	RECT temp;
	if (IntersectRect(&temp, &_stageFinn->getBodyRC(), &_item->getRect()))
	{
		DATABASE->pushbackaddVector(_itemNum);
		DATABASE->pushbackaddVector(_itemNum);
		DATABASE->pushbackaddVector(_itemNum);
		DATABASE->pushbackaddVector(_itemNum);
		DATABASE->pushbackaddVector(_itemNum);
		SAFE_DELETE(_item);
	}
}
