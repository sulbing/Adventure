#include "stdafx.h"
#include "stage1.h"


HRESULT stage1::init(void)
{
	_leftDoor = RectMake(0, WINSIZEY / 2, 10, 400);
	_rightDoor = RectMake(6360, WINSIZEY / 2, 10, 400);

	_sceneEffect = new sceneEffect;
	_sceneEffect->init();
	_stageFinn = new stagePlayer;

	if (DATABASE->getWorldPosition() == STAGE_1_LEFT)
	{
		_stageFinn->init(2, 0, 0, 8, WINSIZEX / 4, WINSIZEY - 100, true);

		_camX = 0;
	}
	else if (DATABASE->getWorldPosition() == STAGE_1_RIGHT)
	{
		_stageFinn->init(2, 0, 0, 8, 6200, WINSIZEY - 138, false);

		_camX = 6370 - WINSIZEX;
		_stageFinn->setCamX(_camX);
	}

	_camY = 0;

	_isChange = false;

	return S_OK;
}

void stage1::release(void)
{
}

void stage1::update(void)
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

void stage1::render(void)
{
	IMAGEMANAGER->findImage("STAGE1_PIXEL_COLLISION")->render(getMemDC(), 0, 0, _camX, _camY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("STAGE_BACKGROUND")->render(getMemDC(), 0, 0, _camX / 10, _camY / 10, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("STAGE1")->render(getMemDC(), 0, 0, _camX, _camY, WINSIZEX, WINSIZEY);

	Rectangle(getMemDC(), _leftDoor.left, _leftDoor.top, _leftDoor.right, _leftDoor.bottom);

	//ÇÉ ·£´õ
	_stageFinn->render();

	_sceneEffect->render();
}

void stage1::pixelCollision(void)
{
	//º®¿¡ ºÎµúÈ÷¸é ¸ØÃã
	if (_stageFinn->getIsRight() == true)
	{
		for (int i = _stageFinn->getX() + _stageFinn->getWidth() / 2 - 10; i < _stageFinn->getX() + _stageFinn->getWidth() / 2; ++i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("STAGE1_PIXEL_COLLISION")->getMemDC(), i, _stageFinn->getY() + _stageFinn->getHeight() / 2 - 15);

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
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("STAGE1_PIXEL_COLLISION")->getMemDC(), i, _stageFinn->getY() + _stageFinn->getHeight() / 2 - 15);

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
				COLORREF color = GetPixel(IMAGEMANAGER->findImage("STAGE1_PIXEL_COLLISION")->getMemDC(), _stageFinn->getX(), i);

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

			COLORREF color = GetPixel(IMAGEMANAGER->findImage("STAGE1_PIXEL_COLLISION")->getMemDC(), _stageFinn->getX(), _stageFinn->getY() - 50);

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
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("STAGE1_PIXEL_COLLISION")->getMemDC(), _stageFinn->getX(), _stageFinn->getY() + _stageFinn->getHeight() / 2);

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
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("STAGE1_PIXEL_COLLISION")->getMemDC(), _stageFinn->getX(), _stageFinn->getY() + _stageFinn->getHeight() / 2);

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
	else if (_stageFinn->getState() == WALK || _stageFinn->getState() == IDLE || _stageFinn->getState() == TACKLE)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("STAGE1_PIXEL_COLLISION")->getMemDC(), _stageFinn->getX(), _stageFinn->getY() + _stageFinn->getHeight() / 2);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 0 && g == 0 && b == 255) && !(r == 255 && g == 0 && b == 0))
		{
			_stageFinn->setState(JUMP);
		}
	}
}

void stage1::stageDoor(void)
{
	RECT temp;

	if (IntersectRect(&temp, &_leftDoor, &_stageFinn->getBodyRC()))
	{
		_isChange = true;
		_sceneEffect->setFadeOUT(true);

		//¾À ÀüÈ¯ ³¡³ª¸é ¾À Ã¼ÀÎÁö
		if (!_sceneEffect->getChangeScene())
		{
			//¿ùµå Æ÷Áö¼Ç
			DATABASE->setWorldPosition(STAGE_1_LEFT);

			SCENEMANAGER->changeScene("SCENE_WORLDMAP");
		}
		_stageFinn->setSpeedX(0);
	}

	if (IntersectRect(&temp, &_rightDoor, &_stageFinn->getBodyRC()))
	{
		_isChange = true;
		_sceneEffect->setFadeOUT(true);

		//¾À ÀüÈ¯ ³¡³ª¸é ¾À Ã¼ÀÎÁö
		if (!_sceneEffect->getChangeScene())
		{
			//¿ùµå Æ÷Áö¼Ç
			DATABASE->setWorldPosition(STAGE_1_RIGHT);

			SCENEMANAGER->changeScene("SCENE_WORLDMAP");
		}
		_stageFinn->setSpeedX(0);
	}
}

void stage1::camMove(void)
{
	if (_stageFinn->getIsRight() == true)
	{
		if (_camX >= 0 && _camX < 6370 - WINSIZEX)
		{
			if (_stageFinn->getX() + _stageFinn->getWidth() / 2 == 6370)
			{
				_stageFinn->setSpeedX(0);
			}
			if (_camX == 6370 - WINSIZEX);
			else if (_stageFinn->getX() > WINSIZEX / 3)
			{
				if (_stageFinn->getX() - _camX > WINSIZEX / 3 + 7)
				{
					_camX += _stageFinn->getSpeedX() * 2 + 3;
				}
				else _camX = _stageFinn->getX() - WINSIZEX / 3 + 6;
				_stageFinn->setCamX(_camX);
			}
		}

		if (_camX > 6370 - WINSIZEX) _camX = 6370 - WINSIZEX;
	}

	else if (_stageFinn->getIsRight() == false)
	{
		if (_camX > 0 && _camX <= 6379 - WINSIZEX)
		{
			if (_stageFinn->getX() - _stageFinn->getWidth() / 2 == 0) _stageFinn->setSpeedX(0);
			if (_camX == 0);
			else if (_stageFinn->getX() < 6379 - WINSIZEX / 3)
			{
				if (_stageFinn->getX() - _camX < WINSIZEX / 3 * 2 - 7)
				{
					_camX += _stageFinn->getSpeedX() * 2 - 3;
				}
				else _camX = _stageFinn->getX() - WINSIZEX / 3 * 2 - 5;
				_stageFinn->setCamX(_camX);
			}
		}

		if (_camX < 0) _camX = 0;
	}
}


stage1::stage1()
{
}


stage1::~stage1()
{
}
