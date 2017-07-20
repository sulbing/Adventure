#include "stdafx.h"
#include "minion1.h"


minion1::minion1()
{
}
minion1::~minion1()
{

}
HRESULT minion1::init(int type, float x, float y)
{
	_minion1 = IMAGEMANAGER->findImage("minion1");
	
	_direction = DIRECTION_RIGHT_STOP;

	_type = type;

	_x = x;
	_y = y;

	_time = -1.5f;

	switch (_type)
	{
	case 0:
		_minion1 = IMAGEMANAGER->findImage("minion1");
		break;
	}

	_rc = RectMakeCenter(_x, _y, _minion1->getFrameWidth(), _minion1->getFrameHeight());

	int rightStop[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("minion1RightStop", "minion1", rightStop, 4, 2, true);

	int leftStop[] = { 5,6,7,8 };
	KEYANIMANAGER->addArrayFrameAnimation("minion1LeftStop", "minion1", leftStop, 4, 2, true);

	int arrRightMove[] = { 10,11,12,13,14 };
	KEYANIMANAGER->addArrayFrameAnimation("minion1RightMove", "minion1", arrRightMove, 5, 5, false, rightMove, this);

	int arrLeftMove[] = { 15,16,17,18,19 };
	KEYANIMANAGER->addArrayFrameAnimation("minion1LeftMove", "minion1", arrLeftMove, 5, 5, false, leftMove, this);

	int arrRightAttack[] = { 20,21,22 };
	KEYANIMANAGER->addArrayFrameAnimation("minion1RightAttack", "minion1", arrRightAttack, 3, 2, false, rightAttack, this);

	int arrLeftAttack[] = { 25,26,27 };
	KEYANIMANAGER->addArrayFrameAnimation("minion1LeftAttack", "minion1", arrLeftAttack, 3, 2, false, leftAttack, this);

	int arrRightHit[] = { 30,31,32,33 };
	KEYANIMANAGER->addArrayFrameAnimation("minion1RightHit", "minion1", arrRightHit, 4, 2, false, rightHit, this);

	int arrLeftHit[] = { 35,36,37,38 };
	KEYANIMANAGER->addArrayFrameAnimation("minion1LeftHit", "minion1", arrLeftHit, 4, 2, false, leftHit, this);

	int arrRightDie[] = { 30, 31};
	KEYANIMANAGER->addArrayFrameAnimation("minion1RightDie", "minion1", arrRightDie, 2, 1, true);

	int arrLefttDie[] = { 35, 36 };
	KEYANIMANAGER->addArrayFrameAnimation("minion1LeftDie", "minion1", arrRightDie, 2, 1, true);

	_minionAni = KEYANIMANAGER->findAnimation("minion1RightStop");

	_isTurn = true;
	_maxCount = RND->getFromIntTo(RNDNUMLOW, RNDNUMMAX);
	_count = 0;

	return S_OK;
}
void minion1::release()
{

}
void minion1::update()
{
	_count++;
	if (_count == _maxCount)
	{
		_count = 0;
		_maxCount = RND->getFromIntTo(RNDNUMLOW,RNDNUMMAX);
		if (_isTurn) _isTurn = false;
		else _isTurn = true;
	}



	move0();

	KEYANIMANAGER->update();
	_rc = RectMakeCenter(_x, _y, _minion1->getFrameWidth(), _minion1->getFrameHeight());
}
void minion1::render()
{
	_minion1->aniRender(getMemDC(), _rc.left, _rc.top, _minionAni);
}
void minion1::rightMove(void* obj)
{
	minion1* k = (minion1*)obj;

	k->setDirection(DIRECTION_RIGHT_MOVE);
	k->setMinionAni(KEYANIMANAGER->findAnimation("minion1RightStop"));
	k->getMinionAni()->start();
}
void minion1::leftMove(void* obj)
{
	minion1* k = (minion1*)obj;

	k->setDirection(DIRECTION_LEFT_MOVE);
	k->setMinionAni(KEYANIMANAGER->findAnimation("minion1LeftStop"));
	k->getMinionAni()->start();
}
void minion1::rightAttack(void* obj)
{
	minion1* k = (minion1*)obj;

	k->setDirection(DIRECTION_RIGHT_ATTACK);
	k->setMinionAni(KEYANIMANAGER->findAnimation("minion1RightStop"));
	k->getMinionAni()->start();
}
void minion1::leftAttack(void* obj)
{
	minion1* k = (minion1*)obj;

	k->setDirection(DIRECTION_LEFT_ATTACK);
	k->setMinionAni(KEYANIMANAGER->findAnimation("minion1LeftStop"));
	k->getMinionAni()->start();
}
void minion1::rightHit(void* obj)
{
	minion1* k = (minion1*)obj;

	k->setDirection(DIRECTION_RIGHT_HIT);
	k->setMinionAni(KEYANIMANAGER->findAnimation("minion1RightStop"));
	k->getMinionAni()->start();
}
void minion1::leftHit(void* obj)
{
	minion1* k = (minion1*)obj;

	k->setDirection(DIRECTION_LEFT_HIT);
	k->setMinionAni(KEYANIMANAGER->findAnimation("minion1LeftStop"));
	k->getMinionAni()->start();
}
void minion1::move0()
{
	_time += 0.1f;
	switch (_isTurn)
	{
	case 0:
		_direction = DIRECTION_RIGHT_MOVE;
		_minionAni = KEYANIMANAGER->findAnimation("minion1RightMove");
		_minionAni->start();
		break;
	case 1:
		_direction = DIRECTION_LEFT_MOVE;
		_minionAni = KEYANIMANAGER->findAnimation("minion1LeftMove");
		_minionAni->start();
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
		_rc = RectMakeCenter(_x, _y, _minion1->getFrameWidth(), _minion1->getFrameHeight());
		break;
	case DIRECTION_LEFT_MOVE:
		_x -= MINION1SPEED;
		_y += _time * GRAVITY;
		_rc = RectMakeCenter(_x, _y, _minion1->getFrameWidth(), _minion1->getFrameHeight());
		break;
	case DIRECTION_LEFT_DIE: case DIRECTION_RIGHT_HIT:
		_x += MINION1SPEED;
		_rc = RectMakeCenter(_x, _y, _minion1->getFrameWidth(), _minion1->getFrameHeight());
	case DIRECTION_RIGHT_DIE: case DIRECTION_LEFT_HIT:
		_x -= MINION1SPEED;
		_rc = RectMakeCenter(_x, _y, _minion1->getFrameWidth(), _minion1->getFrameHeight());
	}
}