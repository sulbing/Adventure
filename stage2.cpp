#include "stdafx.h"
#include "stage2.h"


HRESULT stage2::init(void)
{
	_leftDoor = RectMake(0, WINSIZEY / 2, 10, 400);
	_rightDoor = RectMake(6640, WINSIZEY / 2, 10, 400);

	_sceneEffect = new sceneEffect;
	_sceneEffect->init();


	_stageFinn = new stagePlayer;
	_stageFinn->init(2, 0, 0, 8, WINSIZEX / 4, WINSIZEY - 100, true);

	_camX = _camY = 0;

	_isChange = false;
	
	return S_OK;
}

void stage2::release(void)
{
}

void stage2::update(void)
{
	_sceneEffect->update();

	//ÇÉ ¾÷µ¥ÀÌÆ®
	if (!_isChange)
	{
		_stageFinn->update();
	}
	pixelCollision();
	stageDoor();
	camMove();
}

void stage2::render(void)
{
	IMAGEMANAGER->findImage("STAGE2_PIXEL_COLLISION")->render(getMemDC(), 0, 0, _camX, _camY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("STAGE_BACKGROUND")->render(getMemDC(), 0, 0, _camX / 10, _camY / 10, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("STAGE2")->render(getMemDC(), 0, 0, _camX, _camY, WINSIZEX, WINSIZEY);

	//Rectangle(getMemDC(), _leftDoor.left, _leftDoor.top, _leftDoor.right, _leftDoor.bottom);

	//ÇÉ ·£´õ
	_stageFinn->render();

	_sceneEffect->render();
}

void stage2::pixelCollision(void)
{
	//º®¿¡ ºÎµúÈ÷¸é ¸ØÃã
	if (_stageFinn->getIsRight() == true)
	{
		for (int i = _stageFinn->getX() + _stageFinn->getWidth() / 2 - 10; i < _stageFinn->getX() + _stageFinn->getWidth() / 2; ++i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("STAGE2_PIXEL_COLLISION")->getMemDC(), i, _stageFinn->getY() + _stageFinn->getHeight() / 2 - 15);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 0 && g == 0 && b == 255))
			{
				_stageFinn->setX(i - _stageFinn->getWidth() / 2);
				_stageFinn->setSpeedX(0);
				break;
			}
		}
	}

	else if (_stageFinn->getIsRight() == false)
	{
		for (int i = _stageFinn->getX() - _stageFinn->getWidth() / 2 + 10; i > _stageFinn->getX() - _stageFinn->getWidth() / 2; --i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("STAGE2_PIXEL_COLLISION")->getMemDC(), i, _stageFinn->getY() + _stageFinn->getHeight() / 2 - 15);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 0 && g == 0 && b == 255))
			{
				_stageFinn->setX(i + _stageFinn->getWidth() / 2);
				_stageFinn->setSpeedX(0);
				break;
			}
		}
	}

	//¹Ù´Ú¿¡ ÂøÁö
	if (_stageFinn->getState() == JUMP || _stageFinn->getState() == HIT || _stageFinn->getState() == JUMPATTACK)
	{
		if (_stageFinn->getSpeedY() >= 0)
		{
			for (int i = _stageFinn->getY() + _stageFinn->getHeight() / 2 - 10; i < _stageFinn->getY() + _stageFinn->getHeight() / 2; ++i)
			{
				COLORREF color = GetPixel(IMAGEMANAGER->findImage("STAGE2_PIXEL_COLLISION")->getMemDC(), _stageFinn->getX(), i);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				if ((r == 0 && g == 0 && b == 255) || (r == 255 && g == 0 && b == 0))
				{
					_stageFinn->setY(i - _stageFinn->getHeight() / 2);
					if (KEYMANAGER->isStayKeyDown(VK_RIGHT) || KEYMANAGER->isStayKeyDown(VK_LEFT)) _stageFinn->setState(WALK);
					else _stageFinn->setState(IDLE);
					break;
				}

			}

			COLORREF color = GetPixel(IMAGEMANAGER->findImage("STAGE2_PIXEL_COLLISION")->getMemDC(), _stageFinn->getX(), _stageFinn->getY() - 50);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 0 && g == 255 && b == 0))
			{
				_stageFinn->init(2, 0, 0, 8, WINSIZEX / 4, WINSIZEY - 100, true);
			}
		}
	}

	else if (_stageFinn->getState() == WALK || _stageFinn->getState() == IDLE)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("STAGE2_PIXEL_COLLISION")->getMemDC(), _stageFinn->getX(), _stageFinn->getY() + _stageFinn->getHeight() / 2);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 0 && g == 0 && b == 255) && !(r == 255 && g == 0 && b == 0))
		{
			_stageFinn->setState(JUMP);
		}
	}

	//¾ÉÀ¸¸é »¡°£ºÎºÐ Åë°ú
	else if (_stageFinn->getState() == CROUCH)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("STAGE2_PIXEL_COLLISION")->getMemDC(), _stageFinn->getX(), _stageFinn->getY() + _stageFinn->getHeight() / 2);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_stageFinn->setY(_stageFinn->getY() + 17);
			_stageFinn->setState(JUMP);
		}
	}

	//Ãß¶ô
	else if (_stageFinn->getState() == WALK || _stageFinn->getState() == IDLE)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("STAGE2_PIXEL_COLLISION")->getMemDC(), _stageFinn->getX(), _stageFinn->getY() + _stageFinn->getHeight() / 2);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 0 && g == 0 && b == 255) && !(r == 255 && g == 0 && b == 0))
		{
			_stageFinn->setState(JUMP);
		}
	}
}

void stage2::stageDoor(void)
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
		_stageFinn->setSpeedX(0);
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

void stage2::camMove(void)
{
	if (_stageFinn->getIsRight() == true)
	{
		if (_camX >= 0 && _camX < 6650 - WINSIZEX)
		{
			if (_stageFinn->getX() + _stageFinn->getWidth() / 2 == 6650)
			{
				_stageFinn->setSpeedX(0);
			}
			if (_camX == 6650 - WINSIZEX);
			else if (_stageFinn->getX() > WINSIZEX / 3)
			{
				if (_stageFinn->getX() - _camX > WINSIZEX / 3 + 4)
				{
					_camX += (_stageFinn->getSpeedX() + 1) * 2 ;
				}
				else _camX = _stageFinn->getX() - WINSIZEX / 3 + 6;
				_stageFinn->setCamX(_camX);
			}
		}

		if (_camX > 6650 - WINSIZEX) _camX = 6650 - WINSIZEX;
	}

	else if (_stageFinn->getIsRight() == false)
	{
		if (_camX > 0 && _camX <= 6657 - WINSIZEX)
		{
			if (_stageFinn->getX() - _stageFinn->getWidth() / 2 == 0) _stageFinn->setSpeedX(0);
			if (_camX == 0);
			else if (_stageFinn->getX() < 6657 - WINSIZEX / 3)
			{
				if (_stageFinn->getX() - _camX < WINSIZEX / 3 * 2 - 4)
				{
					_camX += (_stageFinn->getSpeedX() - 1) * 2 ;
				}
				else _camX = _stageFinn->getX() - WINSIZEX / 3 * 2 - 5;
				_stageFinn->setCamX(_camX);
			}
		}

		if (_camX < 0) _camX = 0;
	}
}


stage2::stage2()
{
}


stage2::~stage2()
{
}
