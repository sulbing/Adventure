#include "stdafx.h"
#include "worldPlayer.h"


worldPlayer::worldPlayer()
{
}
worldPlayer::~worldPlayer()
{
}

HRESULT worldPlayer::init()
{
	_x = 100;
	_y = 100;
	return S_OK;
}

void worldPlayer:: release(void)
{

}
void worldPlayer:: update(void)
{
	keyControl();
	basicMove();



}
void worldPlayer:: render(void)
{
	Rectangle(getMemDC(), _finnRC.left, _finnRC.top, _finnRC.right, _finnRC.bottom);
	Rectangle(getMemDC(), _jakeRC.left, _jakeRC.top, _jakeRC.right, _jakeRC.bottom);

}

void worldPlayer::keyControl(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_speedY = 3;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_speedY = -3;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_speedX = 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_speedX = -3;
	}

	if (!(KEYMANAGER->isStayKeyDown(VK_LEFT)) && !(KEYMANAGER->isStayKeyDown(VK_RIGHT)))
	{
		_speedX = 0;
	}

	if (!(KEYMANAGER->isStayKeyDown(VK_UP)) && !(KEYMANAGER->isStayKeyDown(VK_DOWN)))
	{
		_speedY = 0;
	}




}

void worldPlayer::basicMove(void)
{
	_x += _speedX;
	_y -= _speedY;


	
	if (FJDISTANCE <= getDistance(_x, _y, _jakeX, _jakeY))
	{
		_jakeAngle = getAngle(_jakeX, _jakeY, _x, _y);
		_jakeX = _x - (cosf(_jakeAngle) * (FJDISTANCE));
		_jakeY = _y - (-sinf(_jakeAngle) * (FJDISTANCE));

	}

	if (_speedX != 0 || _speedY != 0)
	{
		_jakeX += cosf(_jakeAngle) * 3;
		_jakeY += -sinf(_jakeAngle) * 3;
	}
	


	_finnRC = RectMakeCenter(_x, _y, 50, 50);
	_jakeRC = RectMakeCenter(_jakeX, _jakeY, 50, 50);

}

