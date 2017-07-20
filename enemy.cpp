#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}
enemy::~enemy()
{
}
HRESULT enemy::init(int type, float x, float y)
{	
	_direction = DIRECTION_RIGHT_STOP;

	_type = type;

	_x = x;
	_y = y;

	_time = -1.5f;

	switch (_type)
	{
	case 0:
		_minion = IMAGEMANAGER->findImage("minion1");
		minion1Init();
		break;
	case 1:
		_minion = IMAGEMANAGER->findImage("minion2");
		minion2Init();
		break;
	}


	_isTurn = true;
	_maxCount = RND->getFromIntTo(RNDNUMLOW, RNDNUMMAX);
	_count = 0;

	return S_OK;
}
void enemy::release()
{

}
void enemy::update(int type)
{
	_type = type;

	switch (_type)
	{
	case 0:
		turn();
		minion1Move();
		break;
	case 1:
		turn();
		minion2Move();
	default:
		break;
	}

	KEYANIMANAGER->update();
	_rc = RectMakeCenter(_x, _y, _minion->getFrameWidth(), _minion->getFrameHeight());
}
void enemy::render()
{
	_minion->aniRender(getMemDC(), _rc.left, _rc.top, _minionAni);
}
void enemy::rightMove1(void* obj)
{
	enemy* mi = (enemy*)obj;

	mi->setDirection(DIRECTION_RIGHT_MOVE);
	switch (mi->getType())
	{
	case 0:
		mi->setMinionAni(KEYANIMANAGER->findAnimation("minion1RightStop"));
		break;
	case 1:
		mi->setMinionAni(KEYANIMANAGER->findAnimation("minion2RightStop"));
		break;
	}
	mi->getMinionAni()->start();
}
void enemy::leftMove1(void* obj)
{
	enemy* mi = (enemy*)obj;

	mi->setDirection(DIRECTION_LEFT_MOVE);
	switch (mi->getType())
	{
	case 0:
		mi->setMinionAni(KEYANIMANAGER->findAnimation("minion1LeftStop"));
		break;
	case 1:
		mi->setMinionAni(KEYANIMANAGER->findAnimation("minion2LeftStop"));
		break;
	}
	mi->getMinionAni()->start();
}
void enemy::rightAttack1(void* obj)
{
	enemy* mi = (enemy*)obj;

	mi->setDirection(DIRECTION_RIGHT_ATTACK);
	switch (mi->getType())
	{
	case 0:
		mi->setMinionAni(KEYANIMANAGER->findAnimation("minion1RightStop"));
		break;
	case 1:
		mi->setMinionAni(KEYANIMANAGER->findAnimation("minion2RightStop"));
		break;
	}
	mi->getMinionAni()->start();
}
void enemy::leftAttack1(void* obj)
{
	enemy* mi = (enemy*)obj;

	mi->setDirection(DIRECTION_LEFT_ATTACK);
	switch (mi->getType())
	{
	case 0 :
		mi->setMinionAni(KEYANIMANAGER->findAnimation("minion1LeftStop"));
		break;
	case 1:
		mi->setMinionAni(KEYANIMANAGER->findAnimation("minion2LeftStop"));
		break;
	}
	mi->getMinionAni()->start();
}
void enemy::rightHit1(void* obj)
{
	enemy* mi = (enemy*)obj;

	mi->setDirection(DIRECTION_RIGHT_HIT);
	switch (mi->getType())
	{
	case 0:
		mi->setMinionAni(KEYANIMANAGER->findAnimation("minion1RightStop"));
		break;
	case 1:
		mi->setMinionAni(KEYANIMANAGER->findAnimation("minion2RightStop"));
		break;
	}
	mi->getMinionAni()->start();
}
void enemy::leftHit1(void* obj)
{
	enemy* mi = (enemy*)obj;

	mi->setDirection(DIRECTION_LEFT_HIT);
	switch (mi->getType())
	{
	case 0:
		mi->setMinionAni(KEYANIMANAGER->findAnimation("minion1LeftStop"));
		break;
	case 1:
		mi->setMinionAni(KEYANIMANAGER->findAnimation("minion2LeftStop"));
		break;
	}
	mi->getMinionAni()->start();
}
void enemy::minion1Move()
{
	_time += 0.1f;
	switch (_isTurn)
	{
	case 0:
		if (_direction != DIRECTION_RIGHT_MOVE)
		{
			_direction = DIRECTION_RIGHT_MOVE;
			_minionAni = KEYANIMANAGER->findAnimation("minion1RightMove");
			_minionAni->start();
		}
		break;
	case 1:
		if (_direction != DIRECTION_LEFT_MOVE)
		{
			_direction = DIRECTION_LEFT_MOVE;
			_minionAni = KEYANIMANAGER->findAnimation("minion1LeftMove");
			_minionAni->start();
		}
		break;
	default:
		break;
	}

	switch (_direction)
	{
	case DIRECTION_RIGHT_STOP: case DIRECTION_LEFT_STOP:
		break;
	case DIRECTION_RIGHT_MOVE:
		_x += MINION1SPEED;
		_y += _time * GRAVITY;
		_rc = RectMakeCenter(_x, _y, _minion->getFrameWidth(), _minion->getFrameHeight());
		break;
	case DIRECTION_LEFT_MOVE:
		_x -= MINION1SPEED;
		_y += _time * GRAVITY;
		_rc = RectMakeCenter(_x, _y, _minion->getFrameWidth(), _minion->getFrameHeight());
		break;
	case DIRECTION_LEFT_DIE: case DIRECTION_RIGHT_HIT:
		_x += MINION1SPEED;
		_rc = RectMakeCenter(_x, _y, _minion->getFrameWidth(), _minion->getFrameHeight());
	case DIRECTION_RIGHT_DIE: case DIRECTION_LEFT_HIT:
		_x -= MINION1SPEED;
		_rc = RectMakeCenter(_x, _y, _minion->getFrameWidth(), _minion->getFrameHeight());
	}
}
void enemy::minion1Init()
{
	_rc = RectMakeCenter(_x, _y, _minion->getFrameWidth(), _minion->getFrameHeight());

	int rightStop[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("minion1RightStop", "minion1", rightStop, 4, 2, true);

	int leftStop[] = { 5,6,7,8 };
	KEYANIMANAGER->addArrayFrameAnimation("minion1LeftStop", "minion1", leftStop, 4, 2, true);

	int arrRightMove[] = { 10,11,12,13,14 };
	KEYANIMANAGER->addArrayFrameAnimation("minion1RightMove", "minion1", arrRightMove, 5, 5, false, rightMove1, this);

	int arrLeftMove[] = { 15,16,17,18,19 };
	KEYANIMANAGER->addArrayFrameAnimation("minion1LeftMove", "minion1", arrLeftMove, 5, 5, false, leftMove1, this);

	int arrRightAttack[] = { 20,21,22 };
	KEYANIMANAGER->addArrayFrameAnimation("minion1RightAttack", "minion1", arrRightAttack, 3, 2, false, rightAttack1, this);

	int arrLeftAttack[] = { 25,26,27 };
	KEYANIMANAGER->addArrayFrameAnimation("minion1LeftAttack", "minion1", arrLeftAttack, 3, 2, false, leftAttack1, this);

	int arrRightHit[] = { 30,31,32,33 };
	KEYANIMANAGER->addArrayFrameAnimation("minion1RightHit", "minion1", arrRightHit, 4, 2, false, rightHit1, this);

	int arrLeftHit[] = { 35,36,37,38 };
	KEYANIMANAGER->addArrayFrameAnimation("minion1LeftHit", "minion1", arrLeftHit, 4, 2, false, leftHit1, this);

	int arrRightDie[] = { 30, 31 };
	KEYANIMANAGER->addArrayFrameAnimation("minion1RightDie", "minion1", arrRightDie, 2, 1, true);

	int arrLefttDie[] = { 35, 36 };
	KEYANIMANAGER->addArrayFrameAnimation("minion1LeftDie", "minion1", arrRightDie, 2, 1, true);

	_minionAni = KEYANIMANAGER->findAnimation("minion1RightStop");
}
void enemy::turn()
{
	_count++;
	if (_count == _maxCount)
	{
		_count = 0;
		_maxCount = RND->getFromIntTo(RNDNUMLOW, RNDNUMMAX);
		if (_isTurn) _isTurn = false;
		else _isTurn = true;
	}
}
void enemy::minion2Init()
{
	_rc = RectMakeCenter(_x, _y, _minion->getFrameWidth(), _minion->getFrameHeight());

	int rightStop[] = { 0,1,2,3,4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("minion2RightStop", "minion2", rightStop, 8, 10, true);

	int leftStop[] = { 10,11,12,13,14,15,16,17 };
	KEYANIMANAGER->addArrayFrameAnimation("minion2LeftStop", "minion2", leftStop, 8, 10, true);

	int arrRightMove[] = { 20,21,22,23,24,25,26,27,28,29 };
	KEYANIMANAGER->addArrayFrameAnimation("minion2RightMove", "minion2", arrRightMove, 10, 10, false, rightMove1, this);

	int arrLeftMove[] = { 30,31,32,33,34,35,36,37,38,39 };
	KEYANIMANAGER->addArrayFrameAnimation("minion2LeftMove", "minion2", arrLeftMove, 10, 10, false, leftMove1, this);

	int arrRightAttack[] = { 60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79 };
	KEYANIMANAGER->addArrayFrameAnimation("minion2RightAttack", "minion2", arrRightAttack, 20, 20, false, rightAttack1, this);

	int arrLeftAttack[] = { 80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99 };
	KEYANIMANAGER->addArrayFrameAnimation("minion2LeftAttack", "minion2", arrLeftAttack, 20, 20, false, leftAttack1, this);

	int arrRightHit[] = { 45,46,47,48,49 };
	KEYANIMANAGER->addArrayFrameAnimation("minion2RightHit", "minion2", arrRightHit, 5, 6, false, rightHit1, this);

	int arrLeftHit[] = { 55,56,57,58,59 };
	KEYANIMANAGER->addArrayFrameAnimation("minion2LeftHit", "minion2", arrLeftHit, 5, 6, false, leftHit1, this);

	int arrRightDie[] = { 45, 46 };
	KEYANIMANAGER->addArrayFrameAnimation("minion2RightDie", "minion2", arrRightDie, 2, 1, true);

	int arrLefttDie[] = { 55,56 };
	KEYANIMANAGER->addArrayFrameAnimation("minion2LeftDie", "minion2", arrRightDie, 2, 1, true);

	_minionAni = KEYANIMANAGER->findAnimation("minion2RightMove");
	_minionAni->start();
}
void enemy::minion2Move()
{
	switch (_isTurn)
	{
	case 0:
		if (_direction != DIRECTION_RIGHT_MOVE)
		{
			_direction = DIRECTION_RIGHT_MOVE;
			_minionAni = KEYANIMANAGER->findAnimation("minion2RightMove");
			_minionAni->start();
		}
		break;
	case 1:
		if (_direction != DIRECTION_LEFT_MOVE)
		{
			_direction = DIRECTION_LEFT_MOVE;
			_minionAni = KEYANIMANAGER->findAnimation("minion2LeftMove");
			_minionAni->start();
		}
		break;
	default:
		break;
	}
	switch (_direction)
	{
	case DIRECTION_RIGHT_STOP: case DIRECTION_LEFT_STOP:
		break;
	case DIRECTION_RIGHT_MOVE:
		_x += MINION1SPEED;
		_rc = RectMakeCenter(_x, _y, _minion->getFrameWidth(), _minion->getFrameHeight());
		break;
	case DIRECTION_LEFT_MOVE:
		_x -= MINION1SPEED;
		_rc = RectMakeCenter(_x, _y, _minion->getFrameWidth(), _minion->getFrameHeight());
		break;
	case DIRECTION_LEFT_DIE: case DIRECTION_RIGHT_HIT:
		_x += MINION1SPEED;
		_rc = RectMakeCenter(_x, _y, _minion->getFrameWidth(), _minion->getFrameHeight());
	case DIRECTION_RIGHT_DIE: case DIRECTION_LEFT_HIT:
		_x -= MINION1SPEED;
		_rc = RectMakeCenter(_x, _y, _minion->getFrameWidth(), _minion->getFrameHeight());
	}
}