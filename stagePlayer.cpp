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
	_startX = x;
	_startY = y;
	_width = 40;
	_height = 80;
	_bodyRC = RectMakeCenter(_x, _y, _width, _height);
	_speedX = 0;
	_speedY = 0;
	_jumpPower = JUMPPOWER;
	_gravity = GRAVITY;
	_isRight = isRight;
	_state = INTRO;
	_isLookUp = false;
	_isHit = false;


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

	//애니메이션 관련 초기화
	animaitionInit();

	return S_OK;
}

void stagePlayer::release(void)
{

}

void stagePlayer::update(void)
{
	stateControl();
	keyControl();
	basicMove();
	KEYANIMANAGER->update();
}

void stagePlayer::render(void)
{
	Rectangle(getMemDC(), _bodyRC.left, _bodyRC.top, _bodyRC.right, _bodyRC.bottom);

	//애니 랜더
	if (_isHit)
	{
		if (hitCount % 6 != 0)
		{
			_basicImage->aniRender(getMemDC(), _x - _basicImage->getFrameWidth() / 2, _y - _basicImage->getFrameHeight() / 2, _playerMotion);
		}
		
	}
	if (!_isHit)
	{
		_basicImage->aniRender(getMemDC(), _x - _basicImage->getFrameWidth() / 2, _y - _basicImage->getFrameHeight() / 2, _playerMotion);
	}
}
	


//업데이트에 들어가는 함수들
void stagePlayer::keyControl()
{
	//오른쪽 눌럿을때
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (_state == IDLE || _state == JUMP || _state == WALK) 
		{
			_speedX = MOVESPEED;
			_isRight = true;
			if (_state == IDLE) _state = WALK;
		}
	}

	//왼쪽 눌렀을때
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (_state == IDLE || _state == JUMP || _state == WALK)
		{
			_speedX = - MOVESPEED;
			_isRight = false;
			if (_state == IDLE) _state = WALK;
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
		
		if (_state == IDLE || _state == WALK)
		{
			_state = JUMP;
			_speedY -= JUMPPOWER;
		}
		
	}

	//f를 눌렀을때

	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		init(2, 0, 0, 8, 0, WINSIZEY * 3 / 4, true);
	}

	//r을 눌렀을때
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		_state = HIT;
	}

}
void stagePlayer::stateControl()
{
	if (_state == IDLE)
	{
		aniInput("stageLeftIdle", "stageRightIdle");

		if (!_playerMotion->isPlay())
		{
			_playerMotion->start();
		}
		_speedX = 0;
		_speedY = 0;
	}

	if (_state == WALK)
	{
		aniInput("stageLeftWalk", "stageRightWalk");
		if (!_playerMotion->isPlay())
		{
			_playerMotion->start();
		}
		if (!KEYMANAGER->isStayKeyDown(VK_RIGHT) && !KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_state = IDLE;
			_speedX = 0;
		}
	}

	

	if (_state == CROUCH)
	{
		aniInput("stageLeftCrouch", "stageRightCrouch");
		if (!_playerMotion->isPlay())
		{
			if (crouchInt == 0)
			{
				_playerMotion->start();
				crouchInt++;
			}
			
		}
		if (!KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_state = IDLE;
		}
		_speedX = 0;
		_speedY = 0;

		float _crouchY = _y + 20;
		float _crouchHeight = 40;
		_bodyRC = RectMakeCenter(_x, _crouchY, _width, _crouchHeight);
	}

	if (_state != CROUCH && _state != CROUCHATTACK && _state != TACKLE)
	{
		crouchInt = 0;
	}
	

	if (_state == JUMP)
	{
		if (_speedY <= 0)
		{
			aniInput("stageLeftUpJump", "stageRightUpJump");
			if (!_playerMotion->isPlay())
			{
				_playerMotion->start();
			}
		}
		else if (_speedY > 0)
		{
			aniInput("stageLeftDownJump", "stageRightDownJump");
			if (!_playerMotion->isPlay())
			{
				if (_isRight && downJumpRightInt == 0)
				{
					_playerMotion->start();
					downJumpRightInt++;
				}
				else if (!_isRight && downJumpLeftInt == 0)
				{
					_playerMotion->start();
					downJumpLeftInt++;
				}

			}
		}
	}

	if (_state != JUMP && _state != JUMPATTACK)
	{
		downJumpLeftInt = 0;
		downJumpRightInt = 0;
	}

	if (_state == HIT)
	{
		_isHit = true;
		aniInput("stageLeftHit", "stageRightHit");
		if (!_playerMotion->isPlay())
		{
			if (hitInt == 0)
			{
				_playerMotion->start();
				hitInt++;
			}
			else
			{
				_state = IDLE;
				hitInt = 0;
			}
			
		}

		//_speedY = 0;
		_speedX = 2 * (1 - (_isRight * 2));
	}

	if (_isHit)
	{
		hitCount++;
		if (hitCount >= 200)
		{
			_isHit = false;
			hitCount = 0;
		}
	}

	if (_state == INTRO)
	{
		aniInput("stageLeftWalk", "stageRightWalk");
		if (!_playerMotion->isPlay())
		{
			_playerMotion->start();
		}

		if (_isRight)
		{
			_speedX = MOVESPEED;
			if (_startX + INTRODISTANCE <= _x)
			{
				_state = IDLE;
			}
		}

		if (!_isRight)
		{
			_speedX = -MOVESPEED;
			if (_startX - INTRODISTANCE >= _x)
			{
				_state = IDLE;
			}
		}
		
	}


	if (_state == OUTRO)
	{
		aniInput("stageLeftWalk", "stageRightWalk");
		if (!_playerMotion->isPlay())
		{
			_playerMotion->start();
		}

		if (_isRight)
		{
			_speedX = MOVESPEED;
			if (_startX + INTRODISTANCE <= _x)
			{
				_state = IDLE;
			}
		}

		if (!_isRight)
		{
			_speedX = -MOVESPEED;
			if (_startX - INTRODISTANCE >= _x)
			{
				_state = IDLE;
			}
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

	if (_state == HIT && _speedY != 0)
	{
		_speedY += GRAVITY * moveTime;
	}

	if (_state != CROUCH)
	{
		_bodyRC = RectMakeCenter(_x, _y, _width, _height);
	}
	
}


// 초기화에 들어가는 함수들

void stagePlayer::animaitionInit()
{
	_basicImage = IMAGEMANAGER->addFrameImage("스테이지기본모션", "playerImage/핀_스테이지_기본모션.bmp", 0, 0, 2000, 1792, 10, 14, true, RGB(255, 0, 255));


	int rightIDLE[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
	KEYANIMANAGER->addArrayFrameAnimation("stageRightIdle", "스테이지기본모션", rightIDLE, 12, 15, true);

	int leftIDLE[] = { 79,78,77,76,75,74,73,72,71,70,89,88 };
	KEYANIMANAGER->addArrayFrameAnimation("stageLeftIdle", "스테이지기본모션", leftIDLE, 12, 15, true);

	int rightWALK[] = { 13,14,15,16,17,18,19,20,21,22,23,24 };
	KEYANIMANAGER->addArrayFrameAnimation("stageRightWalk", "스테이지기본모션", rightWALK, 12, 15, true);

	int leftWALK[] = { 86,85,84,83,82,81,80,99,98,97,96,95 };
	KEYANIMANAGER->addArrayFrameAnimation("stageLeftWalk", "스테이지기본모션", leftWALK, 12, 15, true);

	int rightUpJump[] = { 26,27,28,29 };
	KEYANIMANAGER->addArrayFrameAnimation("stageRightUpJump", "스테이지기본모션", rightUpJump, 4, 15, true);

	int rightDownJump[] = { 30,31,32 };
	KEYANIMANAGER->addArrayFrameAnimation("stageRightDownJump", "스테이지기본모션", rightDownJump, 3, 15, false);

	int leftUpJump[] = { 93,92,91,90 };
	KEYANIMANAGER->addArrayFrameAnimation("stageLeftUpJump", "스테이지기본모션", leftUpJump, 4, 15, true);

	int leftDownJump[] = { 109,108,107 };
	KEYANIMANAGER->addArrayFrameAnimation("stageLeftDownJump", "스테이지기본모션", leftDownJump, 3, 15, false);

	int rightCrouch[] = {34, 35,36,37,38 };
	KEYANIMANAGER->addArrayFrameAnimation("stageRightCrouch", "스테이지기본모션", rightCrouch, 4, 15, false);

	int leftCrouch[] = { 105,104,103,102,101 };
	KEYANIMANAGER->addArrayFrameAnimation("stageLeftCrouch", "스테이지기본모션", leftCrouch, 4, 15, false);

	int rightHit[] = { 41,42,43,44 };
	KEYANIMANAGER->addArrayFrameAnimation("stageRightHit", "스테이지기본모션", rightHit, 4, 15, false);

	int leftHit[] = { 118,117,116,115 };
	KEYANIMANAGER->addArrayFrameAnimation("stageLeftHit", "스테이지기본모션", leftHit, 4, 15, false);





	//초기화상태에 따라 방향 바꿔줄것 - 수정필요
	if (_isRight)
	{
		_playerMotion = KEYANIMANAGER->findAnimation("stageRightIdle");
	}
	else if (!_isRight)
	{
		_playerMotion = KEYANIMANAGER->findAnimation("stageLeftIdle");
	}
	_playerMotion->start();



	//메계변수 초기화
	downJumpLeftInt = 0;
	downJumpRightInt = 0;
	crouchInt = 0;
	hitInt = 0;
}




void stagePlayer::aniInput(std::string leftKey, std::string rightKey)
{
	if (_isRight)
	{
		_playerMotion = KEYANIMANAGER->findAnimation(rightKey);
	}
	else if (!_isRight)
	{
		_playerMotion = KEYANIMANAGER->findAnimation(leftKey);
	}
}

