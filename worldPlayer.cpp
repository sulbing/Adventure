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
	_jakeX = 0;
	_jakeY = 0;
	_jakeRenderX = WINSIZEX / 2;
	_jakeRenderY = WINSIZEY / 2 - 10;
	_jakeSpeedX = 0;
	_jakeSpeedY = 0;
	
	_finnDirection = BOTTOM;
	_jakeDirection = BOTTOM;

	animationInit();

	_finnRC = RectMakeCenter(_x, _y, 40, 20);

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
		_isBridgeState = true;
	}

	if (_state != WORLDBRIDGE)
	{
		_isBridgeState = false;
	}


	if (_state == WORLDLONGLEG)
	{
		longLegMove();
		_isLongLegState = true;
	}

	if (_state != WORLDLONGLEG)
	{
		_isLongLegState = false;
	}


	_finnRC = RectMakeCenter(_x, _y, 30, 20);
	
	isDirection();
}

void worldPlayer:: render(void)
{
	/*Rectangle(getMemDC(), _finnRC.left, _finnRC.top, _finnRC.right, _finnRC.bottom);
	Rectangle(getMemDC(), _jakeRC.left, _jakeRC.top, _jakeRC.right, _jakeRC.bottom);*/
	
	if (!_isBridgeOpening && !_isLongLegOpening)
	{
		_jakeBasic->aniRender(getMemDC(), _jakeRenderX - _jakeBasic->getFrameWidth() / 2, _jakeRenderY - _jakeBasic->getFrameHeight() / 2, _jakeMotion);
	}

	if (_isBridgeOpening)
	{
		_jakeBridge->aniRender(getMemDC(), _jakeRenderX - _jakeBridge->getFrameWidth() / 2, _jakeRenderY - _jakeBridge->getFrameHeight() / 2, _jakeMotion);
	}
	
	if (_isLongLegOpening)
	{
		_jakeLongLeg->aniRender(getMemDC(), _jakeRenderX - _jakeLongLeg->getFrameWidth() / 2, _jakeRenderY - _jakeLongLeg->getFrameHeight() / 2, _jakeMotion);
	}

	_finnBasic->aniRender(getMemDC(), WINSIZEX / 2 - _finnBasic->getFrameWidth() / 2, WINSIZEY / 2 - _finnBasic->getFrameHeight() / 2, _finnMotion);
	
	
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
	_jakeRenderX = WINSIZEX / 2 + (_jakeX - _x);
	_jakeRenderY = WINSIZEY / 2 + (_jakeY - _y);



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
	
	
	_finnRC = RectMakeCenter(_x, _y, 30, 20);
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

void worldPlayer::setLongLeg(int startX, int startY, int EndX, int EndY)
{
	_state = WORLDLONGLEG;
	_longLegStartX = startX;
	_longLegStartY = startY;
	_longLegEndX = EndX;
	_longLegEndY = EndY;
	_longLegProcInt = 0;
	_speedX = 0;
	_speedY = 0;
}

void worldPlayer::bridgeMove()
{
	_jakeX += _jakeSpeedX;
	_jakeY += _jakeSpeedY;
	_x += _speedX;
	_y += _speedY;
	_jakeRenderX = WINSIZEX / 2 + (_jakeX - _x);
	_jakeRenderY = WINSIZEY / 2 + (_jakeY - _y);


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
			if (_y < _bridgeEndY + 37)
			{
				_speedY = 3;
			}
			else if (_y > _bridgeEndY + 43)
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
			if (_y < _bridgeEndY - 63)
			{
				_speedY = 3;
			}
			else if (_y > _bridgeEndY - 57)
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

void worldPlayer::longLegMove()
{
	_jakeX += _jakeSpeedX;
	_jakeY += _jakeSpeedY;
	_x += _speedX;
	_y += _speedY;
	_jakeRenderX = WINSIZEX / 2 + (_jakeX - _x);
	_jakeRenderY = WINSIZEY / 2 + (_jakeY - _y);


	_finnRC = RectMakeCenter(_x, _y, 50, 50);
	_jakeRC = RectMakeCenter(_jakeX, _jakeY, 50, 50);

		//力捞农 x 捞悼

	if (_longLegProcInt == 0)
	{
		if (_jakeX < _longLegStartX - 3)
		{
			_jakeSpeedX = 3;
		}
		else if (_jakeX > _longLegStartX + 3)
		{
			_jakeSpeedX = -3;
		}
		else
		{
			_jakeSpeedX = 0;
			_longLegProcInt++;
		}

	}

	else if (_longLegProcInt == 1)
	{
		if (_jakeY < _longLegStartY - 3)
		{
			_jakeSpeedY = 3;
		}
		else if (_jakeY > _longLegStartY + 3)
		{
			_jakeSpeedY = -3;
		}
		else
		{
			_jakeSpeedY = 0;
			_longLegProcInt++;
		}
	}
		
		//力捞农 促府 饭叼
		if (_longLegProcInt == 2)
		{
			_isLongLegOpening = true;
			_jakeMotion = KEYANIMANAGER->findAnimation("toUpLongLegDownReady");
			_jakeY = (_longLegStartY + _longLegEndY) / 2;



			if (!_jakeMotion->isPlay())
			{
				_jakeMotion->start();
				
			}

			_longLegProcInt++;
			
		}
		if (_longLegProcInt == 3)
		{
			if (!_jakeMotion->isPlay())
			{
				_longLegProcInt++;
			}
		}

		//巧 x 捞悼
		if (_longLegProcInt == 4)
		{
			if (_x < _longLegStartX - 3)
			{
				_speedX = 3;
			}
			else if (_x > _longLegStartX + 3)
			{
				_speedX = -3;
			}
			else
			{
				_speedX = 0;
				_longLegProcInt++;
			}
		}

		//巧 y 捞悼
		if (_longLegProcInt == 5)
		{
			if (_y < _longLegStartY - 3)
			{
				_speedY = 3;
			}
			else if (_y > _longLegStartY + 3)
			{
				_speedY = -3;
			}
			else
			{
				_speedY = 0;
				_longLegProcInt++;
			}
		}


		//力捞农 促府乔扁 俊聪皋捞记 角青
		if (_longLegProcInt == 6)
		{
			_jakeMotion = KEYANIMANAGER->findAnimation("toUpLongLegOpen");
			

			if (!_jakeMotion->isPlay())
			{
				_jakeMotion->start();
				_longLegProcInt++;
			}
		}

		//力捞农 促府乔扁 局聪皋捞记 角青吝!
		if (_longLegProcInt == 7)
		{
			if (!_jakeMotion->isPlay())
			{
				_longLegProcInt++;
			}
		}

		//巧 y 绵 捞悼

		if (_longLegProcInt == 8)
		{
			if (_y < _longLegEndY - 53)
			{
				_y = 3;
			}
			else if (_y > _longLegEndY - 47)
			{
				_speedY = -3;
			}
			else
			{
				_speedY = 0;
				_longLegProcInt++;
			}
		}


		//力捞农 促府立扁 局聪皋捞记 角青!~
		if (_longLegProcInt == 9)
		{
			_jakeMotion = KEYANIMANAGER->findAnimation("toUpLongLegClose");


			if (!_jakeMotion->isPlay())
			{
				_jakeMotion->start();
				_longLegProcInt++;
			}
		}

		if (_longLegProcInt == 10)
		{
			if (!_jakeMotion->isPlay())
			{
				_longLegProcInt++;
			}
		}

		if (_longLegProcInt == 11)
		{

			_jakeY = _longLegEndY;
			_isLongLegOpening = false;
			_state = WORLDIDLE;
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
	if (!_isBridgeOpening && !_isLongLegOpening)
	{
		if (_jakeSpeedX > 1)
		{
			if (_jakeSpeedY > 1)
			{
				_jakeDirection = BOTTOMRIGHT;
				_jakeMotion = KEYANIMANAGER->findAnimation("worldJakeBottomRightMove");
				if (!_jakeMotion->isPlay())_jakeMotion->start();

			}
			else if (_jakeSpeedY < -1)
			{
				_jakeDirection = TOPRIGHT;
				_jakeMotion = KEYANIMANAGER->findAnimation("worldJakeTopRightMove");
				if (!_jakeMotion->isPlay())_jakeMotion->start();
			}

			else if (_jakeSpeedY <= 1 && _jakeSpeedY >= -1)
			{
				_jakeDirection = RIGHT;
				_jakeMotion = KEYANIMANAGER->findAnimation("worldJakeRightMove");
				if (!_jakeMotion->isPlay())_jakeMotion->start();
			}
		}

		else if (_jakeSpeedX <  -1)
		{
			if (_jakeSpeedY > 1)
			{
				_jakeDirection = BOTTOMLEFT;
				_jakeMotion = KEYANIMANAGER->findAnimation("worldJakeBottomLeftMove");
				if (!_jakeMotion->isPlay())_jakeMotion->start();
			}
			else if (_jakeSpeedY < -1)
			{
				_jakeDirection = TOPLEFT;
				_jakeMotion = KEYANIMANAGER->findAnimation("worldJakeTopLeftMove");
				if (!_jakeMotion->isPlay())_jakeMotion->start();
			}
			else if (_jakeSpeedY <= 1 && _jakeSpeedY >= -1)
			{
				_jakeDirection = LEFT;
				_jakeMotion = KEYANIMANAGER->findAnimation("worldJakeLeftMove");
				if (!_jakeMotion->isPlay())_jakeMotion->start();
			}
		}
		else if (_jakeSpeedX <= 1 && _jakeSpeedX >= -1)
		{
		if (_jakeSpeedY > 1)
		{
		_jakeDirection = BOTTOM;
		_jakeMotion = KEYANIMANAGER->findAnimation("worldJakeBottomMove");
		if (!_jakeMotion->isPlay())_jakeMotion->start();
		}
		else if (_jakeSpeedY < -1)
		{
		_jakeDirection = TOP;
		_jakeMotion = KEYANIMANAGER->findAnimation("worldJakeTopMove");
		if (!_jakeMotion->isPlay())_jakeMotion->start();
		}
		else if (_jakeSpeedY <= 1 && _jakeSpeedY >= -1)
		{
		if (_jakeDirection == TOP)
		{
		_jakeMotion = KEYANIMANAGER->findAnimation("worldJakeTop");
		}
		else if (_jakeDirection == TOPRIGHT)
		{
		_jakeMotion = KEYANIMANAGER->findAnimation("worldJakeTopRight");
		}
		else if (_jakeDirection == RIGHT)
		{
		_jakeMotion = KEYANIMANAGER->findAnimation("worldJakeRight");
		}
		else if (_jakeDirection == BOTTOMRIGHT)
		{
		_jakeMotion = KEYANIMANAGER->findAnimation("worldJakeBottomRight");
		}
		else if (_jakeDirection == BOTTOM)
		{
		_jakeMotion = KEYANIMANAGER->findAnimation("worldJakeBottom");
		}
		else if (_jakeDirection == BOTTOMLEFT)
		{
		_jakeMotion = KEYANIMANAGER->findAnimation("worldJakeBottomLeft");
		}
		else if (_jakeDirection == LEFT)
		{
		_jakeMotion = KEYANIMANAGER->findAnimation("worldJakeLeft");
		}
		else if (_jakeDirection == TOPLEFT)
		{
		_jakeMotion = KEYANIMANAGER->findAnimation("worldJakeTopLeft");
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
	_jakeLongLeg = IMAGEMANAGER->addFrameImage("力捞农氛促府", "playerImage/力捞农_氛促府.bmp", 0, 0, 1408, 120, 22, 1, true, RGB(255, 0, 255));

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
	KEYANIMANAGER->addArrayFrameAnimation("worldJakeBottomLeftMove", "力捞农海捞流", bottomLeftMoveJake, 6, 8, true);

	int leftMove[] = { 56,57,58,59,60,61 };
	int leftMoveJake[] = { 58,59,60,61,62,63 };
	KEYANIMANAGER->addArrayFrameAnimation("worldFinnLeftMove", "巧海捞流", leftMove, 6, 8, true);
	KEYANIMANAGER->addArrayFrameAnimation("worldJakeLeftMove", "力捞农海捞流", leftMoveJake, 6, 8, true);

	int topLeftMove[] = { 48,49,50,51,52,53 };
	int topLeftMoveJake[] = { 50,51,52,53,54,55 };
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


	int toUpLongLegDownReady[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("toUpLongLegDownReady", "力捞农氛促府", toUpLongLegDownReady, 4, 8, false);

	int toUpLongLegOpen[] = { 4,5,6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("toUpLongLegOpen", "力捞农氛促府", toUpLongLegOpen, 8, 8, false);

	int toUpLongLegClose[] = { 12,13,14,15,16,17, 18, 19, 20, 21};
	KEYANIMANAGER->addArrayFrameAnimation("toUpLongLegClose", "力捞农氛促府", toUpLongLegClose, 7, 8, false);

	_finnMotion = KEYANIMANAGER->findAnimation("worldFinnBottom");
	_jakeMotion = KEYANIMANAGER->findAnimation("worldJakeBottom");




}