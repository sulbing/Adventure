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
	_state = WORLDIDLE;
	_x = 100;
	_y = 100;
	_jakeSpeedX = 0;
	_jakeSpeedY = 0;
	return S_OK;
}

void worldPlayer:: release(void)
{

}
void worldPlayer:: update(void)
{
	if (_state == WORLDIDLE)
	{
		keyControl();
		basicMove();
	}
	
	if (_state == WORLDBRIDGE)
	{
		bridgeMove();
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		setBridge(WINSIZEX / 2, WINSIZEY/2, WINSIZEX / 2, WINSIZEY/ 2 + 200);
	}


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

void worldPlayer::setBridge(int startX, int startY, int EndX, int EndY)
{
	
	_state = WORLDBRIDGE;
	_bridgeStartX = startX;
	_bridgeStartY = startY;
	_bridgeEndX = EndX;
	_bridgeEndY = EndY;
	_bridgeProcInt = 0;
	_speedX = 0;
	_speedY = 0;
}

void worldPlayer::bridgeMove()
{
	_jakeX += _jakeSpeedX;
	_jakeY += _jakeSpeedY;
	_x += _speedX;
	_y += _speedY;

	_finnRC = RectMakeCenter(_x, _y, 50, 50);
	_jakeRC = RectMakeCenter(_jakeX, _jakeY, 50, 50);

	if (_bridgeProcInt == 0)
	{
		if (_jakeX < _bridgeStartX - 3)
		{
			_jakeSpeedX = 3;
		}
		else if (_jakeX > _bridgeStartX + 3)
		{
			_jakeSpeedX = -3;
		}
		else
		{
			_jakeSpeedX = 0;
			_bridgeProcInt++;
		}
		
	}
	
	if (_bridgeProcInt == 1)
	{
		if (_jakeY < _bridgeStartY - 3)
		{
			_jakeSpeedY = 3;
		}
		else if (_jakeY > _bridgeStartY + 3)
		{
			_jakeSpeedY = -3;
		}
		else 
		{
			_jakeSpeedY = 0;
			_bridgeProcInt+= 2;
		}
	}
	if (_bridgeProcInt == 2)
	{
		//力捞农 促府 凯扁 局聪皋捞记 角青
	}

	if (_bridgeProcInt == 3)
	{
		if (_x < _bridgeStartX - 3)
		{
			_speedX = 3;
		}
		else if (_x > _bridgeStartX + 3)
		{
			_speedX = -3;
		}
		else
		{
			_speedX = 0;
			_bridgeProcInt++;
		}
	}
	if (_bridgeProcInt == 4)
	{
		if (_y < _bridgeEndY - 3)
		{
			_speedY = 3;
		}
		else if (_y > _bridgeEndY + 3)
		{
			_speedY = -3;
		}
		else
		{
			_speedY = 0;
			_bridgeProcInt++;
		}
	}
	if (_bridgeProcInt == 5)
	{
		//力捞农 促府立绰 局聪
	}
}

