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
	
	_finnDirection = BOTTOM;
	_jakeDirection = BOTTOM;

	animationInit();

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
		setBridge(WINSIZEX / 2, WINSIZEY/2 + 170 , WINSIZEX / 2, WINSIZEY/ 2 );
	}

	isDirection();
	KEYANIMANAGER->update();
}

void worldPlayer:: render(void)
{
	//Rectangle(getMemDC(), _finnRC.left, _finnRC.top, _finnRC.right, _finnRC.bottom);
	//Rectangle(getMemDC(), _jakeRC.left, _jakeRC.top, _jakeRC.right, _jakeRC.bottom);
	
	if (!_isBridgeOpening)
	{
		_jakeBasic->aniRender(getMemDC(), _jakeX - _jakeBasic->getFrameWidth() / 2, _jakeY - _jakeBasic->getFrameHeight() / 2, _jakeMotion);
	}

	else if (_isBridgeOpening)
	{
		_jakeBridge->aniRender(getMemDC(), _jakeX - _jakeBridge->getFrameWidth() / 2, _jakeY - _jakeBridge->getFrameHeight() / 2, _jakeMotion);
	}
	
	_finnBasic->aniRender(getMemDC(), _x - _finnBasic->getFrameWidth() / 2 , _y - _finnBasic->getFrameHeight() / 2 , _finnMotion);
	

}

void worldPlayer::keyControl(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_speedY = -3;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_speedY = 3;
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
	_y += _speedY;
	_jakeX += _jakeSpeedX;
	_jakeY += _jakeSpeedY;



	if (FJDISTANCE <= getDistance(_x, _y, _jakeX, _jakeY))
	{
		_jakeAngle = getAngle(_jakeX, _jakeY, _x, _y);
		_jakeX = _x - (cosf(_jakeAngle) * (FJDISTANCE));
		_jakeY = _y - (-sinf(_jakeAngle) * (FJDISTANCE));

	}

	if (_speedX != 0 || _speedY != 0)
	{
		_jakeSpeedX = cosf(_jakeAngle) * 3;
		_jakeSpeedY = -sinf(_jakeAngle) * 3;
	}
	else if (_speedX == 0 && _speedY == 0)
	{
		_jakeSpeedX = 0;
		_jakeSpeedY = 0;
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

	if (_bridgeStartY < _bridgeEndY)
	{
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

		else if (_bridgeProcInt == 1)
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
				_bridgeProcInt++;
			}
		}
		else if (_bridgeProcInt == 2)
		{
			_isBridgeOpening = true;
			_jakeMotion = KEYANIMANAGER->findAnimation("toDownBridgeOpen");
			_jakeY = (_bridgeStartY + _bridgeEndY) / 2;



			if (!_jakeMotion->isPlay())
			{
				_jakeMotion->start();
			}


			_bridgeProcInt++;
		}

		if (_bridgeProcInt == 3)
		{
			if (!_jakeMotion->isPlay()) _bridgeProcInt++;
		}

		if (_bridgeProcInt == 4)
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
		if (_bridgeProcInt == 5)
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
		if (_bridgeProcInt == 6)
		{
			_jakeMotion = KEYANIMANAGER->findAnimation("toDownBridgeClose");
			_jakeY = (_bridgeStartY + _bridgeEndY) / 2;



			if (!_jakeMotion->isPlay())
			{
				_jakeMotion->start();
			}

			_bridgeProcInt++;
		}
		if (_bridgeProcInt == 7)
		{
			if (!_jakeMotion->isPlay())
			{
				_jakeY = _bridgeEndY;
				_isBridgeOpening = false;
				_state = WORLDIDLE;
				
			}
		}
	}
	else if (_bridgeStartY > _bridgeEndY)
	{
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

		else if (_bridgeProcInt == 1)
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
				_bridgeProcInt++;
			}
		}
		else if (_bridgeProcInt == 2)
		{
			_isBridgeOpening = true;
			_jakeMotion = KEYANIMANAGER->findAnimation("toUpBridgeOpen");
			_jakeY = (_bridgeStartY + _bridgeEndY) / 2;



			if (!_jakeMotion->isPlay())
			{
				_jakeMotion->start();
			}


			_bridgeProcInt++;
		}

		if (_bridgeProcInt == 3)
		{
			if (!_jakeMotion->isPlay()) _bridgeProcInt++;
		}

		if (_bridgeProcInt == 4)
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
		if (_bridgeProcInt == 5)
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
		if (_bridgeProcInt == 6)
		{
			_jakeMotion = KEYANIMANAGER->findAnimation("toUpBridgeClose");
			_jakeY = (_bridgeStartY + _bridgeEndY) / 2;



			if (!_jakeMotion->isPlay())
			{
				_jakeMotion->start();
			}

			_bridgeProcInt++;
		}
		if (_bridgeProcInt == 7)
		{
			if (!_jakeMotion->isPlay())
			{
				_jakeY = _bridgeEndY;
				_isBridgeOpening = false;
				_state = WORLDIDLE;
			}
		}
	}
	
}

void worldPlayer :: isDirection (void)
{
	//巧 规氢 魄沥
	if (_speedX > 0)
	{
		if (_speedY > 0)
		{
			_finnDirection = BOTTOMRIGHT;
			_finnMotion = KEYANIMANAGER->findAnimation("worldFinnBottomRightMove");
			if (!_finnMotion->isPlay())_finnMotion->start();

		}
		else if (_speedY < 0)
		{
			_finnDirection = TOPRIGHT;
			_finnMotion = KEYANIMANAGER->findAnimation("worldFinnTopRightMove");
			if (!_finnMotion->isPlay())_finnMotion->start();
		}
		
		else if (_speedY == 0)
		{
			_finnDirection = RIGHT;
			_finnMotion = KEYANIMANAGER->findAnimation("worldFinnRightMove");
			if (!_finnMotion->isPlay())_finnMotion->start();
		}
	}

	else if (_speedX < 0)
	{
		if (_speedY > 0)
		{
			_finnDirection = BOTTOMLEFT;
			_finnMotion = KEYANIMANAGER->findAnimation("worldFinnBottomLeftMove");
			if (!_finnMotion->isPlay())_finnMotion->start();
		}
		else if (_speedY < 0)
		{
			_finnDirection = TOPLEFT;
			_finnMotion = KEYANIMANAGER->findAnimation("worldFinnTopLeftMove");
			if (!_finnMotion->isPlay())_finnMotion->start();
		}
		else if (_speedY == 0)
		{
			_finnDirection = LEFT;
			_finnMotion = KEYANIMANAGER->findAnimation("worldFinnLeftMove");
			if (!_finnMotion->isPlay())_finnMotion->start();
		}
	}

	else if (_speedX == 0)
	{
		if (_speedY > 0)
		{
			_finnDirection = BOTTOM;
			_finnMotion = KEYANIMANAGER->findAnimation("worldFinnBottomMove");
			if (!_finnMotion->isPlay())_finnMotion->start();
		}
		else if (_speedY < 0)
		{
			_finnDirection = TOP;
			_finnMotion = KEYANIMANAGER->findAnimation("worldFinnTopMove");
			if (!_finnMotion->isPlay())_finnMotion->start();
		}
		else if (_speedY == 0)
		{
			if (_finnDirection == TOP)
			{
				_finnMotion = KEYANIMANAGER->findAnimation("worldFinnTop");
			}
			else if (_finnDirection == TOPRIGHT)
			{
				_finnMotion = KEYANIMANAGER->findAnimation("worldFinnTopRight");
			}
			else if (_finnDirection == RIGHT)
			{
				_finnMotion = KEYANIMANAGER->findAnimation("worldFinnRight");
			}
			else if (_finnDirection == BOTTOMRIGHT)
			{
				_finnMotion = KEYANIMANAGER->findAnimation("worldFinnBottomRight");
			}
			else if (_finnDirection == BOTTOM)
			{
				_finnMotion = KEYANIMANAGER->findAnimation("worldFinnBottom");
			}
			else if (_finnDirection == BOTTOMLEFT)
			{
				_finnMotion = KEYANIMANAGER->findAnimation("worldFinnBottomLeft");
			}
			else if (_finnDirection == LEFT)
			{
				_finnMotion = KEYANIMANAGER->findAnimation("worldFinnLeft");
			}
			else if (_finnDirection == TOPLEFT)
			{
				_finnMotion = KEYANIMANAGER->findAnimation("worldFinnTopLeft");
			}

		}
	}



	//力捞农 规氢 魄沥
	if (!_isBridgeOpening)
	{
		if (_jakeSpeedX > 1)
		{
			if (_jakeSpeedY > 1)
			{
				_jakeDirection = BOTTOMRIGHT;
				_jakeMotion = KEYANIMANAGER->findAnimation("worldFinnBottomRightMove");
				if (!_jakeMotion->isPlay())_jakeMotion->start();

			}
			else if (_jakeSpeedY < -1)
			{
				_jakeDirection = TOPRIGHT;
				_jakeMotion = KEYANIMANAGER->findAnimation("worldFinnTopRightMove");
				if (!_jakeMotion->isPlay())_jakeMotion->start();
			}

			else if (_jakeSpeedY <= 1 && _jakeSpeedY >= -1)
			{
				_jakeDirection = RIGHT;
				_jakeMotion = KEYANIMANAGER->findAnimation("worldFinnRightMove");
				if (!_jakeMotion->isPlay())_jakeMotion->start();
			}
		}

		else if (_jakeSpeedX <  -1)
		{
			if (_jakeSpeedY > 1)
			{
				_jakeDirection = BOTTOMLEFT;
				_jakeMotion = KEYANIMANAGER->findAnimation("worldFinnBottomLeftMove");
				if (!_jakeMotion->isPlay())_jakeMotion->start();
			}
			else if (_jakeSpeedY < -1)
			{
				_jakeDirection = TOPLEFT;
				_jakeMotion = KEYANIMANAGER->findAnimation("worldFinnTopLeftMove");
				if (!_jakeMotion->isPlay())_jakeMotion->start();
			}
			else if (_jakeSpeedY <= 1 && _jakeSpeedY >= -1)
			{
				_jakeDirection = LEFT;
				_jakeMotion = KEYANIMANAGER->findAnimation("worldFinnLeftMove");
				if (!_jakeMotion->isPlay())_jakeMotion->start();
			}
		}
		else if (_jakeSpeedX <= 1 && _jakeSpeedX >= -1)
		{
		if (_jakeSpeedY > 1)
		{
		_jakeDirection = BOTTOM;
		_jakeMotion = KEYANIMANAGER->findAnimation("worldFinnBottomMove");
		if (!_jakeMotion->isPlay())_jakeMotion->start();
		}
		else if (_jakeSpeedY < -1)
		{
		_jakeDirection = TOP;
		_jakeMotion = KEYANIMANAGER->findAnimation("worldFinnTopMove");
		if (!_jakeMotion->isPlay())_jakeMotion->start();
		}
		else if (_jakeSpeedY <= 1 && _jakeSpeedY >= -1)
		{
		if (_jakeDirection == TOP)
		{
		_jakeMotion = KEYANIMANAGER->findAnimation("worldFinnTop");
		}
		else if (_jakeDirection == TOPRIGHT)
		{
		_jakeMotion = KEYANIMANAGER->findAnimation("worldFinnTopRight");
		}
		else if (_jakeDirection == RIGHT)
		{
		_jakeMotion = KEYANIMANAGER->findAnimation("worldFinnRight");
		}
		else if (_jakeDirection == BOTTOMRIGHT)
		{
		_jakeMotion = KEYANIMANAGER->findAnimation("worldFinnBottomRight");
		}
		else if (_jakeDirection == BOTTOM)
		{
		_jakeMotion = KEYANIMANAGER->findAnimation("worldFinnBottom");
		}
		else if (_jakeDirection == BOTTOMLEFT)
		{
		_jakeMotion = KEYANIMANAGER->findAnimation("worldFinnBottomLeft");
		}
		else if (_jakeDirection == LEFT)
		{
		_jakeMotion = KEYANIMANAGER->findAnimation("worldFinnLeft");
		}
		else if (_jakeDirection == TOPLEFT)
		{
		_jakeMotion = KEYANIMANAGER->findAnimation("worldFinnTopLeft");
		}

		}
	}
	



	
	}
}

void worldPlayer::animationInit()
{
	_finnBasic = IMAGEMANAGER->addFrameImage("巧海捞流", "playerImage/巧_岿靛.bmp", 0, 0, 512, 540, 8, 9, true, RGB(255, 0, 255));
	_jakeBasic = IMAGEMANAGER->addFrameImage("力捞农海捞流", "playerImage/力捞农_岿靛.bmp", 0, 0, 512, 540, 8, 9, true, RGB(255, 0, 255));
	_jakeBridge = IMAGEMANAGER->addFrameImage("力捞农促府", "playerImage/力捞农_促府.bmp", 0, 0, 1024, 260, 16, 2, true, RGB(255, 0, 255));

	int top[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("worldFinnTop", "巧海捞流", top, 1, 15, true);
	KEYANIMANAGER->addArrayFrameAnimation("worldJakeTop", "力捞农海捞流", top, 1, 15, true);

	int topRight[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("worldFinnTopRight", "巧海捞流", topRight, 1, 15, true);
	KEYANIMANAGER->addArrayFrameAnimation("worldJakeTopRight", "力捞农海捞流", topRight, 1, 15, true);

	int right[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("worldFinnRight", "巧海捞流", right, 1, 15, true);
	KEYANIMANAGER->addArrayFrameAnimation("worldJakeRight", "力捞农海捞流", right, 1, 15, true);

	int bottomRight[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("worldFinnBottomRight", "巧海捞流", bottomRight, 1, 15, true);
	KEYANIMANAGER->addArrayFrameAnimation("worldJakeBottomRight", "力捞农海捞流", bottomRight, 1, 15, true);

	int bottom[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("worldFinnBottom", "巧海捞流", bottom, 1, 15, true);
	KEYANIMANAGER->addArrayFrameAnimation("worldJakeBottom", "力捞农海捞流", bottom, 1, 15, true);

	int bottomLeft[] = { 7 };
	KEYANIMANAGER->addArrayFrameAnimation("worldFinnBottomLeft", "巧海捞流", bottomLeft, 1, 15, true);
	KEYANIMANAGER->addArrayFrameAnimation("worldJakeBottomLeft", "力捞农海捞流", bottomLeft, 1, 15, true);

	int left[] = { 6 };
	KEYANIMANAGER->addArrayFrameAnimation("worldFinnLeft", "巧海捞流", left, 1, 15, true);
	KEYANIMANAGER->addArrayFrameAnimation("worldJakeLeft", "力捞农海捞流", left, 1, 15, true);
	
	int topLeft[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation("worldFinnTopLeft", "巧海捞流", topLeft, 1, 15, true); 
	KEYANIMANAGER->addArrayFrameAnimation("worldJakeTopLeft", "力捞农海捞流", topLeft, 1, 15, true);

	int topMove[] = { 40,41,42,43,44,45 };
	KEYANIMANAGER->addArrayFrameAnimation("worldFinnTopMove", "巧海捞流", topMove, 6, 8, true);
	KEYANIMANAGER->addArrayFrameAnimation("worldJakeTopMove", "力捞农海捞流", topMove, 6, 8, true);

	int topRightMove[] = { 32,33,34,35,36,37 };
	KEYANIMANAGER->addArrayFrameAnimation("worldFinnTopRightMove", "巧海捞流", topRightMove, 6, 8, true);
	KEYANIMANAGER->addArrayFrameAnimation("worldJakeTopRightMove", "力捞农海捞流", topRightMove, 6, 8, true);

	int rightMove[] = { 24,25,26,27,28,29 };
	KEYANIMANAGER->addArrayFrameAnimation("worldFinnRightMove", "巧海捞流", rightMove, 6, 8, true);
	KEYANIMANAGER->addArrayFrameAnimation("worldJakeRightMove", "力捞农海捞流", rightMove, 6, 8, true);

	int bottomRightMove[] = { 16,17,18,19,20,21 };
	KEYANIMANAGER->addArrayFrameAnimation("worldFinnBottomRightMove", "巧海捞流", bottomRightMove, 6, 8, true);
	KEYANIMANAGER->addArrayFrameAnimation("worldJakeBottomRightMove", "力捞农海捞流", bottomRightMove, 6, 8, true);

	int bottomMove[] = { 8,9,10,11,12,13 };
	KEYANIMANAGER->addArrayFrameAnimation("worldFinnBottomMove", "巧海捞流", bottomMove, 6, 8, true);
	KEYANIMANAGER->addArrayFrameAnimation("worldJakeBottomMove", "力捞农海捞流", bottomMove, 6, 8, true);

	int bottomLeftMove[] = { 64,65,66,67,68,69 };
	int bottomLeftMoveJake[] = { 66,67,68,69,70,71 };
	KEYANIMANAGER->addArrayFrameAnimation("worldFinnBottomLeftMove", "巧海捞流", bottomLeftMove, 6, 8, true);
	KEYANIMANAGER->addArrayFrameAnimation("worldJakeBottomLeftMove", "力捞农海捞流", bottomLeftMove, 6, 8, true);

	int leftMove[] = { 56,57,58,59,60,61 };
	int leftMoveJake[] = { 58,59,60,61,62,63 };
	KEYANIMANAGER->addArrayFrameAnimation("worldFinnLeftMove", "巧海捞流", leftMove, 6, 8, true);
	KEYANIMANAGER->addArrayFrameAnimation("worldJakeLeftMove", "力捞农海捞流", leftMoveJake, 6, 8, true);

	int topLeftMove[] = { 48,49,50,51,52,53 };
	int topLeftMoveJake[] = { 50,51,52,53,54,55,56 };
	KEYANIMANAGER->addArrayFrameAnimation("worldFinnTopLeftMove", "巧海捞流", topLeftMove, 6, 8, true);
	KEYANIMANAGER->addArrayFrameAnimation("worldJakeTopLeftMove", "力捞农海捞流", topLeftMoveJake, 6, 8, true);
	
	int toDownBridgeOpen[] = { 0,1,2,3,4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("toDownBridgeOpen", "力捞农促府", toDownBridgeOpen, 8, 8, false);

	int toDownBridgeClose[] = { 8,9,10,11,12,13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("toDownBridgeClose", "力捞农促府", toDownBridgeClose, 8, 8, false);

	int toUpBridgeOpen[] = { 16,17,18,19,20,21,22,23 };
	KEYANIMANAGER->addArrayFrameAnimation("toUpBridgeOpen", "力捞农促府", toUpBridgeOpen, 8, 8, false);

	int toUpBridgeClose[] = { 24,25,26,27,28,29,30,31 };
	KEYANIMANAGER->addArrayFrameAnimation("toUpBridgeClose", "力捞农促府", toUpBridgeClose, 8, 8, false);

	_finnMotion = KEYANIMANAGER->findAnimation("worldFinnBottom");
	_jakeMotion = KEYANIMANAGER->findAnimation("worldJakeBottom");




}