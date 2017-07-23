#include "stdafx.h"
#include "cheststage.h"


HRESULT cheststage::init(void)
{

	_leftDoor = RectMake(0, WINSIZEY / 2, 10, 400);
	_rightDoor = RectMake(790, WINSIZEY / 2, 10, 400);

	_stageFinn = new stagePlayer;
	_stageFinn->init(2, 0, 0, 8, 30, WINSIZEY * 3 / 4, true);

	_sceneEffect = new sceneEffect;
	_sceneEffect->init();

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
	//ÇÉ ¾÷µ¥ÀÌÆ®
	if (!_isChange) _stageFinn->update();
	pixelCollision();
	
	stageDoor();
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

	//ÇÉ ·£´õ
	_stageFinn->render();
	
	_sceneEffect->render();
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

		//¾À ÀüÈ¯ ³¡³ª¸é ¾À Ã¼ÀÎÁö
		if (!_sceneEffect->getChangeScene())
		{
			SCENEMANAGER->changeScene("SCENE_WORLDMAP");
		}
	}

	else if (IntersectRect(&temp, &_rightDoor, &_stageFinn->getBodyRC()))
	{
		_isChange = true;
		_sceneEffect->setFadeOUT(true);

		//¾À ÀüÈ¯ ³¡³ª¸é ¾À Ã¼ÀÎÁö
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
	if (IntersectRect(&temp, &_stageFinn->getBodyRC(), &_chestRc))
	{
		_chestOpen = true;
	}
}

cheststage::cheststage()
{
}


cheststage::~cheststage()
{
}
