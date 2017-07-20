#include "stdafx.h"
#include "stage1.h"


HRESULT stage1::init(void)
{
	_stageFinn = new stagePlayer;
	_stageFinn->init(2, 0, 0, 8, WINSIZEX / 4, WINSIZEY - 100, true);

	_camX = _camY = 0;

	return S_OK;
}

void stage1::release(void)
{
}

void stage1::update(void)
{

	//ÇÉ ¾÷µ¥ÀÌÆ®
	_stageFinn->update();
	pixelCollision();

	camMove();
}

void stage1::render(void)
{
	IMAGEMANAGER->findImage("STAGE1_PIXEL_COLLISION")->render(getMemDC(), 0, 0, _camX, _camY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("STAGE_BACKGROUND")->render(getMemDC(), 0, 0, _camX / 10, _camY / 10, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("STAGE1")->render(getMemDC(), 0, 0, _camX, _camY, WINSIZEX, WINSIZEY);


	//ÇÉ ·£´õ
	_stageFinn->render();
}

void stage1::pixelCollision(void)
{
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
		for (int i = _stageFinn->getX() - _stageFinn->getWidth() / 2; i < _stageFinn->getX() - _stageFinn->getWidth() / 2 + 10; ++i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("STAGE1_PIXEL_COLLISION")->getMemDC(), i, _stageFinn->getY() + _stageFinn->getHeight() / 2 - 10);

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

	if (_stageFinn->getState() == JUMP || _stageFinn->getState() == HIT)
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
}

void stage1::camMove(void)
{
	if (_stageFinn->getIsRight() == true)
	{
		if (_camX >= 0 && _camX < 6370 - WINSIZEX)
		{
			if (_stageFinn->getX() > WINSIZEX / 3)
			{
				_camX = _stageFinn->getX() - WINSIZEX / 3;
				_stageFinn->setCamX(_camX);
			}
		}
	}

	else if (_stageFinn->getIsRight() == false)
	{
		if (_camX > 0 && _camX <= 6379 - WINSIZEX)
		{
			if (_stageFinn->getX() < 6379 - WINSIZEX / 3)
			{
				_camX = _stageFinn->getX() - WINSIZEX / 3 * 2;
				_stageFinn->setCamX(_camX);
			}
		}
	}
}

stage1::stage1()
{
}


stage1::~stage1()
{
}
