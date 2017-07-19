#include "stdafx.h"
#include "stagePlayer.h"


stagePlayer::stagePlayer()
{
}
stagePlayer::~stagePlayer()
{
}

HRESULT stagePlayer::init(int hearts, int attack, int speed, int currentHP, float x, float y, bool isRight)
{
	//기본정보
	_maxHP = 4 * (hearts + 2);
	_currentHP = currentHP;
	if (_currentHP > _maxHP)
	{
		_currentHP = _maxHP;
	}
	_x = x;
	_y = y;
	_width = 40;
	_height = 40;
	_bodyRC = RectMakeCenter(_x, _y, _width, _height);
	_speedX = 0;
	_speedY = 0;
	_jumpPower = JUMPPOWER;
	_gravity = GRAVITY;
	_isRight = isRight;
	_state = IDLE;
	_isLookUp = false;


	//스테이터스
	_status_hearts = hearts;
	_status_attack = attack;
	_status_speed = speed;


	//1번스킬 - 빨간고추
	_isSkill1Fire = false;
	//2번스킬 - 벌 발사
	_isSkill2Fire = false;
	//3번스킬 - 제이크방패
	_isSkill3Fire = false;

	return S_OK;
}

void stagePlayer::release(void)
{

}

void stagePlayer::update(void)
{
	keyControl();
	stateControl();
	basicMove();

}

void stagePlayer::render(void)
{
	Rectangle(getMemDC(), _bodyRC.left, _bodyRC.top, _bodyRC.right, _bodyRC.bottom);
}


//업데이트에 들어가는 함수들
void stagePlayer::keyControl()
{
	//오른쪽 눌럿을때
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (_state == IDLE || _state == JUMP)
		{
			_speedX = MOVESPEED;
			_isRight = true;
			if (_state == IDLE) _state = WALK;
		}
	}

	//왼쪽 눌렀을때
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (_state == IDLE || _state == JUMP)
		{
			_speedX = - MOVESPEED;
			_isRight = false;
			if (_state == IDLE) _state = WALK;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && (KEYMANAGER->isOnceKeyDown(VK_LEFT)))
	{
		if (_state == WALK)
		{
			_speedX = 0;
		}
	}

	//위를 눌렀을때
	if (KEYMANAGER->isOnceKeyDown(VK_UP)) _isLookUp = true;
	if (KEYMANAGER->isOnceKeyUp(VK_UP)) _isLookUp = false;

	//아래를 눌렀을때
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_state == IDLE || _state == WALK || _state == CROUCH)
		{
			_state = CROUCH;
			_speedX = 0;
		}
	}

	
	//d를 눌렀을때

	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_state = JUMP;
		_speedY -= JUMPPOWER;
	}

}
void stagePlayer::stateControl()
{
	if (_state == WALK)
	{
		if (!KEYMANAGER->isStayKeyDown(VK_RIGHT) && !KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_state = IDLE;
			_speedX = 0;
		}
	}
	if (_state == CROUCH)
	{
		if (!KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_state = IDLE;
		}
	}
}
void stagePlayer::basicMove()
{
	//기본적인 움직임과 관련된 함수
	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveTime = elapsedTime * 100;
	_x += _speedX * moveTime;
	_y += _speedY * moveTime;

	//중력적용
	if (_state == JUMP || _state == JUMPATTACK)
	{
		_speedY += GRAVITY * moveTime;
	}

	_bodyRC = RectMakeCenter(_x, _y, _width, _height);
}


