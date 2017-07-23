#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}
enemy::~enemy()
{

}
HRESULT enemy::init(int type, float x, float y, stagePlayer* z)
{
	_sp = z;

	_direction = DIRECTION_RIGHT_MOVE;
	_maxCount = RND->getFromIntTo(RNDNUMLOW, RNDNUMMAX);
	_count = 0;
	_time = -1.5f;
	_isTurn = true;	
	_x = x, _y = y;
	_type = type;

	switch (_type)
	{
	case 0:
		_image = IMAGEMANAGER->findImage("minion1");
		initAni1();
		break;
	case 1:
		_image = IMAGEMANAGER->findImage("minion2");
		initAni2();
		break;
	case 2:
		_image = IMAGEMANAGER->findImage("minion3");
		initAni3();
		break;
	}

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	_minionAni = KEYANIMANAGER->findAnimation("RightMove");
	_minionAni->start();
	
	return S_OK;
}
void enemy::release()
{

}
void enemy::update()
{
	//방향전환 카운터
	_count++;	
	_time += 0.1f;

	if (_count == _maxCount)
	{
		_count = 0;
		_maxCount = RND->getFromIntTo(RNDNUMLOW, RNDNUMMAX);
		if (_isTurn) _isTurn = false;
		else _isTurn = true;
	}

	switch (_type)
	{
	case 0:
		initAniMove1();
		break;
	case 1:
		initAniMove2();
		break;
	case 2:
		initAniMove3();
		break;
	default:
		break;
	}

	KEYANIMANAGER->update();
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}
void enemy::render()
{
	_image->aniRender(getMemDC(), _rc.left, _rc.top, _minionAni);
}
void enemy::rightAttack(void* obj)	
{
	enemy* mi = (enemy*)obj;

	mi->setDirection(DIRECTION_RIGHT_MOVE);
	switch (mi->getType())
	{
	case 0:
		mi->setMinionAni(KEYANIMANAGER->findAnimation("RightMove"));
		mi->getMinionAni()->start();
		break;
	case 1:
		mi->setMinionAni(KEYANIMANAGER->findAnimation("RightMove"));
		mi->getMinionAni()->start();
		break;
	}
}
void enemy::leftAttack(void* obj)	
{
	enemy* mi = (enemy*)obj;

	mi->setDirection(DIRECTION_LEFT_MOVE);
	switch (mi->getType())
	{
	case 0:
		mi->setMinionAni(KEYANIMANAGER->findAnimation("LeftMove"));
		mi->getMinionAni()->start();
		break;
	case 1:
		mi->setMinionAni(KEYANIMANAGER->findAnimation("LeftMove"));
		mi->getMinionAni()->start();
		break;
	}
}
void enemy::rightHit(void* obj)		
{
	enemy* mi = (enemy*)obj;

	mi->setDirection(DIRECTION_RIGHT_MOVE);
	switch (mi->getType())
	{
	case 0:
		mi->setMinionAni(KEYANIMANAGER->findAnimation("RightMove"));
		break;
	case 1:
		mi->setMinionAni(KEYANIMANAGER->findAnimation("RightMove"));
		break;
	}
	mi->getMinionAni()->start();
}
void enemy::leftHit(void* obj)		
{
	enemy* mi = (enemy*)obj;

	mi->setDirection(DIRECTION_LEFT_MOVE);
	switch (mi->getType())
	{
	case 0:
		mi->setMinionAni(KEYANIMANAGER->findAnimation("LeftMove"));
		break;
	case 1:
		mi->setMinionAni(KEYANIMANAGER->findAnimation("LeftMove"));
		break;
	}
	mi->getMinionAni()->start();
}

//초기화에 들어가는 함수
void enemy::initAni1()
{
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	int arrRightMove[] = { 10,11,12,13,14 };
	KEYANIMANAGER->addArrayFrameAnimation("RightMove", "minion1", arrRightMove, 5, 5, true);

	int arrLeftMove[] = { 15,16,17,18,19 };
	KEYANIMANAGER->addArrayFrameAnimation("LeftMove", "minion1", arrLeftMove, 5, 5, true);

	int arrRightAttack[] = { 20,21,22 };
	KEYANIMANAGER->addArrayFrameAnimation("RightAttack", "minion1", arrRightAttack, 3, 2, false, rightAttack, this);

	int arrLeftAttack[] = { 25,26,27 };
	KEYANIMANAGER->addArrayFrameAnimation("LeftAttack", "minion1", arrLeftAttack, 3, 2, false, leftAttack, this);

	int arrRightHit[] = { 30,31,32,33 };
	KEYANIMANAGER->addArrayFrameAnimation("RightHit", "minion1", arrRightHit, 4, 2, false, rightHit, this);

	int arrLeftHit[] = { 35,36,37,38 };
	KEYANIMANAGER->addArrayFrameAnimation("LeftHit", "minion1", arrLeftHit, 4, 2, false, leftHit, this);

	int arrRightDie[] = { 30, 31 };
	KEYANIMANAGER->addArrayFrameAnimation("RightDie", "minion1", arrRightDie, 2, 1, true);

	int arrLefttDie[] = { 35, 36 };
	KEYANIMANAGER->addArrayFrameAnimation("LeftDie", "minion1", arrRightDie, 2, 1, true);
}
void enemy::initAni2()
{
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	int arrRightMove[] = { 20,21,22,23,24,25,26,27,28,29 };
	KEYANIMANAGER->addArrayFrameAnimation("RightMove", "minion2", arrRightMove, 10, 10, true);

	int arrLeftMove[] = { 30,31,32,33,34,35,36,37,38,39 };
	KEYANIMANAGER->addArrayFrameAnimation("LeftMove", "minion2", arrLeftMove, 10, 10, true);

	int arrRightAttack[] = { 60,61,62,63,64,65,66,67,68,70,71,72,73,74,75,76,77,78 };
	KEYANIMANAGER->addArrayFrameAnimation("RightAttack", "minion2", arrRightAttack, 18, 5, false, rightAttack, this);

	int arrLeftAttack[] = { 88,87,86,85,84,83,82,81,80,98,97,96,95,94,93,92,91,90 };
	KEYANIMANAGER->addArrayFrameAnimation("LeftAttack", "minion2", arrLeftAttack, 18, 5, false, leftAttack, this);

	int arrRightHit[] = { 45,46,47,48,49 };
	KEYANIMANAGER->addArrayFrameAnimation("RightHit", "minion2", arrRightHit, 5, 6, false, rightHit, this);

	int arrLeftHit[] = { 54,53,52,51,50 };
	KEYANIMANAGER->addArrayFrameAnimation("LeftHit", "minion2", arrLeftHit, 5, 6, false, leftHit, this);

	int arrRightDie[] = { 45, 46 };
	KEYANIMANAGER->addArrayFrameAnimation("RightDie", "minion2", arrRightDie, 2, 1, true);

	int arrLefttDie[] = { 54,53 };
	KEYANIMANAGER->addArrayFrameAnimation("LeftDie", "minion2", arrRightDie, 2, 1, true);
}
void enemy::initAni3()
{
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	int arrRightMove[] = { 0,1,2,3,4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("RightMove", "minion3", arrRightMove, 8, 6, true);

	int arrLeftMove[] = { 10,11,12,13,14,15,16,17 };
	KEYANIMANAGER->addArrayFrameAnimation("LeftMove", "minion3", arrLeftMove, 8, 6, true);

	int arrRightAttack[] = { 20,21,22,23,24,25,26,27,28,29 };
	KEYANIMANAGER->addArrayFrameAnimation("RightAttack", "minion3", arrRightAttack, 10, 6, false, rightAttack, this);

	int arrLeftAttack[] = { 30,31,32,33,34,35,36,37,38,39 };
	KEYANIMANAGER->addArrayFrameAnimation("LeftAttack", "minion3", arrLeftAttack, 10, 6, false, leftAttack, this);


	int arrRightHit[] = { 40,41,42,43,44 };
	KEYANIMANAGER->addArrayFrameAnimation("RightHit", "minion3", arrRightHit, 5, 4, false, rightHit, this);

	int arrLeftHit[] = { 50,51,52,53,54 };
	KEYANIMANAGER->addArrayFrameAnimation("LeftHit", "minion3", arrLeftHit, 5, 4, false, leftHit, this);

	int arrRightDie[] = { 45,46,47 };
	KEYANIMANAGER->addArrayFrameAnimation("RightDie", "minion3", arrRightDie, 3, 1, true);

	int arrLefttDie[] = { 55,56,57 };
	KEYANIMANAGER->addArrayFrameAnimation("LeftDie", "minion3", arrRightDie, 3, 1, true);
}
//업데이트에 들어가는 함수
void enemy::initAniMove1()
{
	switch (_isTurn)
	{
	case 0:
		if (_direction != DIRECTION_RIGHT_MOVE)
		{
			_direction = DIRECTION_RIGHT_MOVE;
			_minionAni = KEYANIMANAGER->findAnimation("RightMove");
			_minionAni->start();
		}
		break;
	case 1:
		if (_direction != DIRECTION_LEFT_MOVE)
		{
			_direction = DIRECTION_LEFT_MOVE;
			_minionAni = KEYANIMANAGER->findAnimation("LeftMove");
			_minionAni->start();
		}
		break;
	default:
		break;
	}

	switch (_direction)
	{
	case DIRECTION_RIGHT_MOVE:
		_x += MINION1SPEED;
		_y += _time * GRAVITY;
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	case DIRECTION_LEFT_MOVE:
		_x -= MINION1SPEED;
		_y += _time * GRAVITY;
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	case DIRECTION_LEFT_DIE: case DIRECTION_RIGHT_HIT:
		_x += MINION1SPEED;
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	case DIRECTION_RIGHT_DIE: case DIRECTION_LEFT_HIT:
		_x -= MINION1SPEED;
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	}
}
void enemy::initAniMove2()
{
	//개인필요함수
	RECT	_temp;
	RECT	_hitBox;

	_hitBox = { _rc.left - 10, _rc.top - 20, _rc.right + 10, _rc.bottom };

	//애니 재생시 ~ 
	switch (_direction)
	{
	case DIRECTION_RIGHT_MOVE:
		_x += MINION1SPEED;
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		_hitBox = { _rc.left - 10, _rc.top - 20, _rc.right + 10, _rc.bottom };
		break;
	case DIRECTION_LEFT_MOVE:
		_x -= MINION1SPEED;
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		_hitBox = { _rc.left - 10, _rc.top - 20, _rc.right + 10, _rc.bottom };
		break;
	case DIRECTION_LEFT_DIE: case DIRECTION_RIGHT_HIT:
		_x -= HITPUSH;
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	case DIRECTION_RIGHT_DIE: case DIRECTION_LEFT_HIT:
		_x += HITPUSH;
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	case DIRECTION_LEFT_ATTACK: case DIRECTION_RIGHT_ATTACK:
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	}	
	//공격실행
	if (IntersectRect(&_temp, &_hitBox, &_sp->getBodyRC()) && _direction != DIRECTION_LEFT_ATTACK 
		&& _direction != DIRECTION_RIGHT_ATTACK)
	{
		if (_direction == DIRECTION_LEFT_MOVE)
		{
			_direction = DIRECTION_LEFT_ATTACK;
			_minionAni = KEYANIMANAGER->findAnimation("LeftAttack");
			_minionAni->start();
		}
		if (_direction == DIRECTION_RIGHT_MOVE)
		{
			_direction = DIRECTION_RIGHT_ATTACK;
			_minionAni = KEYANIMANAGER->findAnimation("RightAttack");
			_minionAni->start();
		}
		return;
	}
	//히트다히트
	//else if (IntersectRect(&_temp, &_rc, &_sp->getSkillHitBox(LATTACK)) && _direction != DIRECTION_LEFT_HIT  
	//	&&_direction != DIRECTION_RIGHT_HIT)
	//{
	//	if (_direction == DIRECTION_RIGHT_MOVE)
	//	{
	//		_direction = DIRECTION_RIGHT_HIT;
	//		_minionAni = KEYANIMANAGER->findAnimation("RightHit");
	//		_minionAni->start();
	//	}
	//	if (_direction == DIRECTION_LEFT_MOVE)
	//	{
	//		_direction = DIRECTION_LEFT_HIT;
	//		_minionAni = KEYANIMANAGER->findAnimation("LeftHit");
	//		_minionAni->start();
	//	}
	//	return;
	//}
	else
	{
		//랜덤방향전환
		if (_sp->getBodyRC().left > _rc.left && _direction != DIRECTION_RIGHT_ATTACK && _direction != DIRECTION_LEFT_ATTACK 
			&& _direction != DIRECTION_RIGHT_MOVE && _direction != DIRECTION_RIGHT_HIT && _direction != DIRECTION_LEFT_HIT)
		{
			_direction = DIRECTION_RIGHT_MOVE;
			_minionAni = KEYANIMANAGER->findAnimation("RightMove");
			_minionAni->start();
		}

		else if (_sp->getBodyRC().left <= _rc.left && _direction != DIRECTION_LEFT_ATTACK && _direction != DIRECTION_RIGHT_ATTACK 
			&& _direction != DIRECTION_LEFT_MOVE && _direction != DIRECTION_LEFT_HIT && _direction != DIRECTION_RIGHT_HIT)
		{
			_direction = DIRECTION_LEFT_MOVE;
			_minionAni = KEYANIMANAGER->findAnimation("LeftMove");
			_minionAni->start();
		}
	}
}
void enemy::initAniMove3()
{
	//개인필요함수
	RECT	_temp;
	RECT	_hitBox;

	_hitBox = { _rc.left - 10, _rc.top - 20, _rc.right + 10, _rc.bottom };

	//애니 재생시 ~ 
	switch (_direction)
	{
	case DIRECTION_RIGHT_MOVE:
		_x += MINION1SPEED;
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		_hitBox = { _rc.left - 10, _rc.top - 20, _rc.right + 10, _rc.bottom };
		break;
	case DIRECTION_LEFT_MOVE:
		_x -= MINION1SPEED;
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		_hitBox = { _rc.left - 10, _rc.top - 20, _rc.right + 10, _rc.bottom };
		break;
	case DIRECTION_LEFT_DIE: case DIRECTION_RIGHT_HIT:
		_x -= HITPUSH;
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	case DIRECTION_RIGHT_DIE: case DIRECTION_LEFT_HIT:
		_x += HITPUSH;
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	case DIRECTION_LEFT_ATTACK: case DIRECTION_RIGHT_ATTACK:
		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	}
	//공격실행
	if (IntersectRect(&_temp, &_hitBox, &_sp->getBodyRC()) && _direction != DIRECTION_LEFT_ATTACK
		&& _direction != DIRECTION_RIGHT_ATTACK)
	{
		if (_direction == DIRECTION_LEFT_MOVE)
		{
			_direction = DIRECTION_LEFT_ATTACK;
			_minionAni = KEYANIMANAGER->findAnimation("LeftAttack");
			_minionAni->start();
		}
		if (_direction == DIRECTION_RIGHT_MOVE)
		{
			_direction = DIRECTION_RIGHT_ATTACK;
			_minionAni = KEYANIMANAGER->findAnimation("RightAttack");
			_minionAni->start();
		}
		return;
	}
	//히트다히트
	//else if (IntersectRect(&_temp, &_rc, &_sp->getSkillHitBox(LATTACK)) && _direction != DIRECTION_LEFT_HIT
	//	&&_direction != DIRECTION_RIGHT_HIT)
	//{
	//	if (_direction == DIRECTION_RIGHT_MOVE)
	//	{
	//		_direction = DIRECTION_RIGHT_HIT;
	//		_minionAni = KEYANIMANAGER->findAnimation("RightHit");
	//		_minionAni->start();
	//	}
	//	if (_direction == DIRECTION_LEFT_MOVE)
	//	{
	//		_direction = DIRECTION_LEFT_HIT;
	//		_minionAni = KEYANIMANAGER->findAnimation("LeftHit");
	//		_minionAni->start();
	//	}
	//	return;
	//}
	else
	{
		//랜덤방향전환
		if (_sp->getBodyRC().left > _rc.left && _direction != DIRECTION_RIGHT_ATTACK && _direction != DIRECTION_LEFT_ATTACK
			&& _direction != DIRECTION_RIGHT_MOVE && _direction != DIRECTION_RIGHT_HIT && _direction != DIRECTION_LEFT_HIT)
		{
			_direction = DIRECTION_RIGHT_MOVE;
			_minionAni = KEYANIMANAGER->findAnimation("RightMove");
			_minionAni->start();
		}

		else if (_sp->getBodyRC().left <= _rc.left && _direction != DIRECTION_LEFT_ATTACK && _direction != DIRECTION_RIGHT_ATTACK
			&& _direction != DIRECTION_LEFT_MOVE && _direction != DIRECTION_LEFT_HIT && _direction != DIRECTION_RIGHT_HIT)
		{
			_direction = DIRECTION_LEFT_MOVE;
			_minionAni = KEYANIMANAGER->findAnimation("LeftMove");
			_minionAni->start();
		}
	}
}