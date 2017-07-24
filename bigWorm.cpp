#include "stdafx.h"
#include "bigWorm.h"


bigWorm::bigWorm() {}
bigWorm::~bigWorm() {}

Bullet::Bullet() {}
Bullet::~Bullet() {}

HRESULT bigWorm::init(float x, float y, stagePlayer* z, int moveLength)
{
	_x = x, _y = y;
	_sp = z;

	_bulletDelay = 0;
	_count = 0;

	_HP = 40;

	_image = IMAGEMANAGER->findImage("bigWorm");
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	_frameX = 0, _frameY = 0;
	_isRight = false;

	_direction = BDIRECTION_MOVE;

	_moveRc = { (int)_x - moveLength / 2, _rc.top - _image->getFrameHeight() / 2, (int)_x + moveLength / 2, _rc.bottom };

	frameManiger();

	return S_OK;
}
void bigWorm::release()
{

}
void bigWorm::update()
{
	frameManiger();
	countupdate();
	if (_direction != BDIRECTION_HIT) move();
	else if (_direction == BDIRECTION_HIT) Hitmove();
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (getDistance(_vBullet[i]->getX(), _vBullet[i]->getY(), _vBullet[i]->getStartX(), _vBullet[i]->getStartY()) > BULLETRANGE)
		{
			_vBullet.erase(_vBullet.begin() + i);
			break;
		}

		_vBullet[i]->update();
	}

}
void bigWorm::render()
{
	//Rectangle(getMemDC(), _moveRc.left, _moveRc.top, _moveRc.right, _moveRc.bottom);
	_image->frameRender(getMemDC(), _x - _image->getFrameWidth() / 2, _rc.bottom - _image->getFrameHeight(), _frameX, _frameY);
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i]->render();
	}
}
void bigWorm::frameManiger()
{
	switch (_direction)
	{
	case BDIRECTION_IDLE:
	{
		if (_isRight)
		{
			_frameY = 0;
		}
		else
		{
			_frameY = 1;
		}
	}
	case BDIRECTION_MOVE:
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
	case BDIRECTION_ATTACK:
	{
		if (_isRight)
		{
			_frameY = 10;
		}
		else
		{
			_frameY = 11;
		}
	}
	break;
	case BDIRECTION_HIT:
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
		_frameNum = 8;
		break;
	case 4: case 5:
		_frameNum = 4;
		break;
	case 10: case 11:
		_frameNum = 10;
		break;
	default:
		break;
	}
}

void bigWorm::move()
{
	RECT rcTemp;
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth() - 40, _image->getFrameHeight());
	if (_direction == BDIRECTION_ATTACK)
	{
		_bulletDelay++;
		if (_bulletDelay == 30) makeBullet(_x + cosf(getAngle(_x, _y, _sp->getX(), _sp->getY())) * 10,
			_y - sinf(getAngle(_x, _y, _sp->getX(), _sp->getY())) * 10, getAngle(_x, _y, _sp->getX(), _sp->getY()));
		if (_bulletDelay > 30) _bulletDelay = 0;
	}
	if (!IntersectRect(&rcTemp, &_moveRc, &_sp->getBodyRC()))
	{
		if (_direction == BDIRECTION_ATTACK)
		{
			if (_isRight && _frameX == 9)
			{
				_frameX = 0;
				_direction = BDIRECTION_MOVE;
			}
			else if (!_isRight && _frameX == 0)
			{
				_direction = BDIRECTION_MOVE;
			}
		}
		else if (_direction == BDIRECTION_MOVE)
		{
			if (_isRight)
			{
				_x += SPEED;
				if (_rc.right > _moveRc.right)
				{
					_isRight = false;
				}
			}
			else
			{
				_x -= SPEED;
				if (_rc.left < _moveRc.left)
				{
					_isRight = true;
				}
			}
		}
	}
	else
	{
		if (getDistance(_x, _y, _sp->getX(), _sp->getY()) < BULLETRANGE && _direction != BDIRECTION_ATTACK)
		{
			_direction = BDIRECTION_ATTACK;
			if (_isRight)_frameX = 0;
			else _frameX = 9;

		}
		else if (getDistance(_x, _y, _sp->getX(), _sp->getY()) >= BULLETRANGE)
		{
			if (_direction == BDIRECTION_ATTACK)
			{
				if (_isRight && _frameX == 8)
				{
					_frameX = 0;
					_direction = BDIRECTION_MOVE;
				}
				else if (!_isRight && _frameX == 0)
				{
					_direction = BDIRECTION_MOVE;
				}
			}
			if (_direction == BDIRECTION_MOVE)
			{
				if (_sp->getX() > _x)
				{
					_x += SPEED;
					_isRight = true;
					if (_rc.right > _moveRc.right)
					{
						_x = _moveRc.right - _image->getFrameWidth();
						_isRight = false;
					}
				}
				else if (_sp->getX() <= _x)
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
void bigWorm::countupdate()
{
	_count++;
	if (_count > 6)
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

void bigWorm::setHit()
{
	_direction = BDIRECTION_HIT;
	(_sp->getX() < _x) ? (_isRight = false, _frameX = 4) : (_isRight = true, _frameX = 0);
}

void bigWorm::Hitmove()
{
	if (_isRight)
	{
		_x -= SPEED / 3;
		if (_frameX == 4)
		{
			_direction = BDIRECTION_MOVE;
		}
	}
	else
	{
		_x += SPEED / 3;
		if (_frameX == 0)
		{
			_direction = BDIRECTION_MOVE;
		}
	}
}


void bigWorm::makeBullet(float x, float y, float angle)
{
	Bullet* _bullet;
	_bullet = new Bullet;
	_bullet->init(x, y, angle);
	_vBullet.push_back(_bullet);
}

HRESULT Bullet::init(float x, float y, float angle)
{
	_bullet = IMAGEMANAGER->findImage("bullet");
	_x = x;
	_y = y;
	_StartX = x;
	_StartY = y;
	_angle = angle;
	_frameX = 0;
	_count = 0;

	return S_OK;
}

void Bullet::release()
{

}

void Bullet::update()
{
	_rc = RectMakeCenter(_x, _y, _bullet->getFrameWidth(), _bullet->getFrameHeight());

	_x += cosf(_angle) * BULLETSPEED;
	_y -= sinf(_angle) * BULLETSPEED;

	_count++;
	if (_count == 6)
	{
		_count = 0;
		_frameX++;
		if (_frameX > _bullet->getMaxFrameX()) _frameX = 0;
	}
}

void Bullet::render()
{
	_bullet->frameRender(getMemDC(), _rc.left, _rc.top, _frameX, 0);
}