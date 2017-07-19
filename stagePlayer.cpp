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
	//�⺻����
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


	//�������ͽ�
	_status_hearts = hearts;
	_status_attack = attack;
	_status_speed = speed;


	//1����ų - ��������
	_isSkill1Fire = false;
	//2����ų - �� �߻�
	_isSkill2Fire = false;
	//3����ų - ����ũ����
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


//������Ʈ�� ���� �Լ���
void stagePlayer::keyControl()
{
	//������ ��������
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (_state == IDLE || _state == JUMP)
		{
			_speedX = MOVESPEED;
			_isRight = true;
			if (_state == IDLE) _state = WALK;
		}
	}

	//���� ��������
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

	//���� ��������
	if (KEYMANAGER->isOnceKeyDown(VK_UP)) _isLookUp = true;
	if (KEYMANAGER->isOnceKeyUp(VK_UP)) _isLookUp = false;

	//�Ʒ��� ��������
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_state == IDLE || _state == WALK || _state == CROUCH)
		{
			_state = CROUCH;
			_speedX = 0;
		}
	}

	
	//d�� ��������

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
	//�⺻���� �����Ӱ� ���õ� �Լ�
	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveTime = elapsedTime * 100;
	_x += _speedX * moveTime;
	_y += _speedY * moveTime;

	//�߷�����
	if (_state == JUMP || _state == JUMPATTACK)
	{
		_speedY += GRAVITY * moveTime;
	}

	_bodyRC = RectMakeCenter(_x, _y, _width, _height);
}


