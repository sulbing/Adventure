#include "stdafx.h"
#include "littleWorm.h"


littleWorm::littleWorm(){}
littleWorm::~littleWorm(){}
HRESULT littleWorm::init(float x, float y, stagePlayer* z, int moveLength)
{
	_x = x, _y = y;
	_sp = z;

	_HP = 5;

	_count = 0;

	_image = IMAGEMANAGER->findImage("liileWorm");
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	_frameX = 0, _frameY = 0;
	_isRight = false;

	_direction = DIRECTION_MOVE;

	_moveRc = { (int)_x - moveLength / 2, _rc.top- _image->getFrameHeight()/2, (int)_x + moveLength / 2, _rc.bottom };

	frameManiger();

	return S_OK;
}
void littleWorm::release()
{

}
void littleWorm::update()
{
	frameManiger();
	countupdate();
	if(_direction != DIRECTION_HIT) move();
	else if (_direction == DIRECTION_HIT) Hitmove();
}
void littleWorm::render()
{
	//Rectangle(getMemDC(), _moveRc.left, _moveRc.top, _moveRc.right, _moveRc.bottom);
	_image->frameRender(getMemDC(), _x - _image->getFrameWidth()/2 - _sp->getCamX(), _rc.bottom - _image->getFrameHeight(), _frameX, _frameY);
}
void littleWorm::frameManiger()
{
	switch (_direction)
	{
	case DIRECTION_MOVE:
	{
		if (_isRight)
		{
			_frameY = 2;
		}
		else
		{
			_frameY = 3;
		}
	}
	break;
	case DIRECTION_ATTACK:
	{
		if (_isRight)
		{
			_frameY = 6;
		}
		else
		{
			_frameY = 7;
		}
	}
	break;
	case DIRECTION_HIT:
	{
		if (_isRight)
		{
			_frameY = 4;
		}
		else
		{
			_frameY = 5;
		}
	}
	break;
	}

	switch (_frameY)
	{
	case 0: case 1:
		_frameNum = 8;
	break;
	case 2: case 3:
		_frameNum = 10;
		break;
	case 4: case 5:
		_frameNum = 5;
		break;
	case 6: case 7:
		_frameNum = 18;
	break;
	default:
		break;
	}
}

void littleWorm::move()
{
	RECT rcTemp;
	
	if (_direction == DIRECTION_ATTACK)
	{
		_rc = RectMakeCenter(_x, _y - 10, _image->getFrameWidth() * 5 / 4, _image->getFrameHeight() + 20);
	}
	else
	{
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	}

	if (!IntersectRect(&rcTemp, &_moveRc, &_sp->getBodyRC()))
	{
		if (_direction == DIRECTION_ATTACK)
		{
			if (_isRight && _frameX == 17)
			{
				_frameX = 0;
				_direction = DIRECTION_MOVE;
			}
			else if (!_isRight && _frameX == 0)
			{
				_direction = DIRECTION_MOVE;
			}
		}
		else if(_direction == DIRECTION_MOVE)
		{
			if (_isRight)
			{
				_x += SPEED;
				if (_rc.right > _moveRc.right)
				{
					_x = _moveRc.right - _image->getFrameWidth();
					_isRight = false;
				}
			}
			else
			{
				_x -= SPEED;
				if (_rc.left < _moveRc.left)
				{
					_x = _moveRc.left + _image->getFrameWidth();
					_isRight = true;
				}
			}
		}
	}
	else
	{
		if (getDistance(_x, _y, _sp->getX(), _sp->getY()) < ATTACKRANGE && _direction != DIRECTION_ATTACK)
		{
			_direction = DIRECTION_ATTACK;
			if (_isRight)_frameX = 0;
			else _frameX = 17;
			
		}
		else if(getDistance(_x, _y, _sp->getX(), _sp->getY()) >= ATTACKRANGE)
		{
			if (_direction == DIRECTION_ATTACK)
			{
				if (_isRight && _frameX == 17)
				{
					_frameX = 0;
					_direction = DIRECTION_MOVE;
				}
				else if (!_isRight && _frameX == 0)
				{
					_direction = DIRECTION_MOVE;
				}
			}
			if (_direction == DIRECTION_MOVE)
			{
				if (_sp->getBodyRC().left > _rc.left)
				{
					_x += SPEED;
					_isRight = true;
					if (_rc.right > _moveRc.right)
					{
						_x = _moveRc.right - _image->getFrameWidth();
						_isRight = false;
					}
				}
				else if (_sp->getBodyRC().left < _rc.left)
				{
					_x -= SPEED;
					_isRight = false;
					if (_rc.left < _moveRc.left)
					{
						_x = _moveRc.left + _image->getFrameWidth();
						_isRight = true;
					}
				}
			}
		}
	}
}
void littleWorm::countupdate()
{
	_count++;
	if (_count > 4)
	{
		_count = 0;
		if (_isRight)
		{
			_frameX++;
			if (_frameX > _frameNum - 1)
			{
				_frameX = 0;
			}
		}
		else
		{
			_frameX--;
			if (_frameX < 0)
			{
				_frameX = _frameNum - 1;
			}
		}
	}
}

void littleWorm::setHit()
{
	_direction = DIRECTION_HIT;
	(_sp->getBodyRC().left < _rc.left) ? (_isRight = false, _frameX = 4) : (_isRight = true, _frameX = 0);
}

void littleWorm::Hitmove()
{
	if (_isRight)
	{
		_x -= SPEED/3;
		if (_frameX == 4)
		{
			_direction = DIRECTION_MOVE;
		}
	}
	else
	{
		_x += SPEED / 3;
		if (_frameX == 0)
		{
			_direction = DIRECTION_MOVE;
		}
	}
}