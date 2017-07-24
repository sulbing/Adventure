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
	_isAttack = false;



	deadComplete = false;

	//스테이터스
	_status_hearts = hearts;
	_status_attack = attack;
	_status_speed = speed;


	//1번스킬 - 빨간고추
	_isSkill1Fire = false;
	//2번스킬 - 벌 발사
	_isSkill2Fire = false;
	//3번스킬 - 점프 쎄게
	_isSkill3Fire = false;

	//애니메이션 관련 초기화
	animaitionInit();
	
	//스킬관련 초기화
	skillInit();
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
	skillUpdate();
	statusControl();
}

void stagePlayer::render(void)
{
	//플레이어 몸통 랜더
	//Rectangle(getMemDC(), _bodyRC.left - _camX, _bodyRC.top, _bodyRC.right - _camX, _bodyRC.bottom);

	//스킬렉트 랜더
	/*for (int i = DEFAULT; i < SKILLEND; i++)
	{
		if (_skill[i]._isFire == true)
		{
			Rectangle(getMemDC(), _skill[i]._hitBox.left - _camX, _skill[i]._hitBox.top, _skill[i]._hitBox.right - _camX, _skill[i]._hitBox.bottom);
		}
	}*/



	if (_isSkill1Fire)
	{
		_fireImage->aniRender(getMemDC(), _skill[FIREATTACK]._hitBox.left - _camX, _skill[FIREATTACK]._hitBox.top, _fireAnimation);
	}

	if (_isSkill2Fire)
	{
		if (_beeDirection)
		{
			_beeAnimation = KEYANIMANAGER->findAnimation("beeRight");
		}
		else if (!_beeDirection)
		{
			_beeAnimation = KEYANIMANAGER->findAnimation("beeLeft");
		}
		_beeWingImage->aniRender(getMemDC(), _skill[BEEATTACK]._hitBox.left - _camX, _skill[BEEATTACK]._hitBox.top, _beeAnimation);
	}

	if (_isSkill3Fire)
	{
		if (_isRight)
		{
			_wingAnimation = KEYANIMANAGER->findAnimation("wingRight");
		}
		else if (_beeDirection)
		{
			_wingAnimation = KEYANIMANAGER->findAnimation("wingLeft");
		}
		_beeWingImage->aniRender(getMemDC(), _x - _beeWingImage->getFrameWidth() / 2 - _camX, _y - _attackImage->getFrameHeight() / 2 - 18, _wingAnimation);
	}

	//애니 랜더

	if (_isHit)
	{
		if (hitCount % 6 != 0)
		{
			if (_isAttack)
			{
				_attackImage->aniRender(getMemDC(), _x - _attackImage->getFrameWidth() / 2 - _camX, _y - _attackImage->getFrameHeight() / 2 - 8, _playerMotion);
			}
			else _basicImage->aniRender(getMemDC(), _x - _basicImage->getFrameWidth() / 2 - _camX, _y - _basicImage->getFrameHeight() / 2 - 8, _playerMotion);
		}
		
	}
	else if (!_isHit)
	{
		if (_isAttack)
		{
			_attackImage->aniRender(getMemDC(), _x - _attackImage->getFrameWidth() / 2 - _camX, _y - _attackImage->getFrameHeight() / 2 - 8, _playerMotion);
		}
		else _basicImage->aniRender(getMemDC(), _x - _basicImage->getFrameWidth() / 2 - _camX, _y - _basicImage->getFrameHeight() / 2 - 8, _playerMotion);
	}
}
	


//업데이트에 들어가는 함수들
void stagePlayer::keyControl()
{
	//오른쪽 눌럿을때
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_state == IDLE || _state == JUMP || _state == WALK || _state == JUMPATTACK)
		{
			_speedX = MOVESPEED + DATABASE->getStatusSpeed();
			if(_state != JUMPATTACK)_isRight = true;
			
			if (_state == IDLE) _state = WALK;
		}
	}

	//왼쪽 눌렀을때
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_state == IDLE || _state == JUMP || _state == WALK || _state == JUMPATTACK)
		{
			_speedX = - MOVESPEED - DATABASE->getStatusSpeed();
			if (_state != JUMPATTACK) _isRight = false;
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
			if (!_isSkill3Fire)_speedY -= JUMPPOWER;
			else if (_isSkill3Fire)_speedY -= 1.5 * JUMPPOWER;
		}

		if (_state == CROUCH)
		{
			skillFire(TATTACK, _x, _y, _isRight);
			_state = TACKLE;
			tackleKnockBackBool = false;

		}
		
	}

	//f를 눌렀을때

	/*if (KEYMANAGER->isOnceKeyDown('F'))
	{
		init(2, 0, 0, 8, 0, WINSIZEY * 3 / 4, true);
	}*/

	//r을 눌렀을때
	/*if (KEYMANAGER->isOnceKeyDown('R'))
	{
		_state = HIT;
	}*/

	//q를 눌렀을때
	/*if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		tackleKnockBackBool = true;
	}*/


	//a를 눌렀을때
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (_state == IDLE || _state == WALK)
		{
			if (_isLookUp)
			{
				skillFire(ATTACK3, _x, _y, _isRight);
				_state = FINNATTACK3;
			}
			else
			{
				skillFire(ATTACK1, _x, _y, _isRight);
				_state = FINNATTACK1;
			}
			
			
		}

		else if (_state == FINNATTACK1)
		{
			skillFire(ATTACK2, _x, _y, _isRight);
			_state = FINNATTACK2;
		}

		else if (_state == FINNATTACK2)
		{
			skillFire(ATTACK3, _x, _y, _isRight);
			_state = FINNATTACK3;
		}

		else if (_state == JUMP)
		{
			skillFire(JATTACK, _x, _y, _isRight);
			_state = JUMPATTACK;
		}
		
		else if (_state == CROUCH)
		{
			skillFire(CATTACK, _x, _y, _isRight);
			_state = CROUCHATTACK;
		}
		
		

	}

	//s를 눌렀을때
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (_state == IDLE || _state == WALK)
		{
			skillFire(LATTACK, _x, _y, _isRight);
			_state = JAKEATTACK;
		}
		
	}

	//w를 눌렀을때
	/*if (KEYMANAGER->isOnceKeyDown('W'))
	{
		_state = DEAD;
	}*/
	

	//// i를 눌렀을때
	//if (KEYMANAGER->isOnceKeyDown('I'))
	//{
	//	_isSkill3Fire = true;
	//	
	//}

	//// o를 눌렀을때
	//if (KEYMANAGER->isOnceKeyDown('O'))
	//{
	//	_isSkill1Fire = true;

	//}

	//// p를 눌렀을때
	//if (KEYMANAGER->isOnceKeyDown('P'))
	//{
	//	_isSkill2Fire = true;

	//}


	


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

	else if (_state == WALK)
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
		_speedY = 0;
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

	if (_state == DEAD)
	{
		_speedX = 0;
		aniInput("stageLeftDead", "stageRightDead");
		if (!_playerMotion->isPlay())
		{
			if (!deadBool)
			{
				_playerMotion->start();
				deadBool = true;
				SOUNDMANAGER->play("죽을때", 1.0f);
			}
			else if (deadBool)
			{
				//deadBool = false;
				deadComplete = true;
				_isHit = false;
			}
		}
	}
	
	if (_state == FINNATTACK1)
	{
		_isAttack = true;
		aniInput("stageLeftFinnAttack1", "stageRightFinnAttack1");
		_speedX = 0;

		if (!_playerMotion->isPlay())
		{
			if (!finnAttack1Bool)
			{
				finnAttack1Bool = true;
				_playerMotion->start();
			}
			else if (finnAttack1Bool)
			{
				_state = IDLE;
				aniInput("stageLeftIdle", "stageRightIdle");
				_isAttack = false;
				finnAttack1Bool = false;
				
			}
		}
		
		
	}

	if (_state == FINNATTACK2)
	{
		_isAttack = true;
		aniInput("stageLeftFinnAttack2", "stageRightFinnAttack2");
		_speedX = 0;

		if (!_playerMotion->isPlay())
		{
			if (!finnAttack2Bool)
			{
				finnAttack2Bool = true;
				_playerMotion->start();
			}
			else if (finnAttack2Bool)
			{
				_state = IDLE;
				aniInput("stageLeftIdle", "stageRightIdle");
				_isAttack = false;
				finnAttack2Bool = false;
				
			}
		}
		
	}
	
	if (_state == FINNATTACK3)
	{
		_isAttack = true;
		aniInput("stageLeftFinnAttack3", "stageRightFinnAttack3");
		_speedX = 0;

		if (!_playerMotion->isPlay())
		{
			if (!finnAttack3Bool)
			{
				finnAttack3Bool = true;
				_playerMotion->start();
			}
			else if (finnAttack3Bool)
			{
				_state = IDLE;
				aniInput("stageLeftIdle", "stageRightIdle");
				_isAttack = false;
				finnAttack3Bool = false;

			}
		}

	}

	if (_state == JUMPATTACK)
		{
			_isAttack = true;
			aniInput("stageLeftJumpAttack", "stageRightJumpAttack");

			if (!_playerMotion->isPlay())
			{
				if (!jumpAttackBool)
				{
					jumpAttackBool = true;
					_playerMotion->start();
				}
				else if (jumpAttackBool)
				{
					_state = JUMP;
					if (_speedY <= 0)
					{
						aniInput("stageLeftUpJump", "stageRightUpJump");
					}
					else if (_speedY > 0)
					{
						aniInput("stageLeftDownJump", "stageRightDownJump");
					}
					
					_isAttack = false;
					jumpAttackBool = false;

				}
			}

	}

	if (_state == CROUCHATTACK)
	{
		_isAttack = true;
		aniInput("stageLeftCrouchAttack", "stageRightCrouchAttack");
		_speedX = 0;

		float _crouchY = _y + 20;
		float _crouchHeight = 40;
		_bodyRC = RectMakeCenter(_x, _crouchY, _width, _crouchHeight);

		if (!_playerMotion->isPlay())
		{
			if (!crouchAttackBool)
			{
				crouchAttackBool = true;
				_playerMotion->start();
			}
			else if (crouchAttackBool)
			{

				_state = CROUCH;
				aniInput("stageLeftCrouch", "stageRightCrouch");
				_isAttack = false;
				crouchAttackBool = false;
				
			}
			
		}

	}

	if (_state == TACKLE)
	{
		_isAttack = true;
		aniInput("stageLeftTackle", "stageRightTackle");
		if (!tackleKnockBackBool)_speedX = 2 * ((_isRight * 2) - 1);
		else _speedX = 1 - (_isRight * 2);
		

		float _crouchY = _y + 20;
		float _crouchHeight = 40;
		_bodyRC = RectMakeCenter(_x, _crouchY, _width, _crouchHeight);

		if (!_playerMotion->isPlay())
		{
			if (!tackleBool)
			{
				tackleBool = true;
				_playerMotion->start();
			}
			else if (tackleBool)
			{
				_state = CROUCH;
				aniInput("stageLeftCrouch", "stageRightCrouch");
				_isAttack = false;
				tackleBool = false;

			}

		}

	}

	if (_state == JAKEATTACK)
	{
		_isAttack = true;
		aniInput("stageLeftJakeAttack", "stageRightJakeAttack");
		_speedX = 0;

		float elapsedTime = TIMEMANAGER->getElapsedTime();
		float moveTime = elapsedTime * 100;
		jakeAttackInt += moveTime;

		if (jakeAttackInt == 5 )
		{
			_skill[LATTACK]._skillX += 20 * (2 * (_isRight)-1);
			_skill[LATTACK]._skillWidth += 40 * (2 * (_isRight)-1);
		}

		if (jakeAttackInt == 10)
		{
			_skill[LATTACK]._skillX += 30 * (2 * (_isRight)-1);
			_skill[LATTACK]._skillWidth += 60 * (2 * (_isRight)-1);
		}

		if (jakeAttackInt == 15)
		{
			_skill[LATTACK]._skillX += 20 * (2 * (_isRight)-1);
			_skill[LATTACK]._skillWidth += 40 * (2 * (_isRight)-1);
		}

		if (jakeAttackInt == 20)
		{
			_skill[LATTACK]._skillX += 10 * (2 * (_isRight)-1);
			_skill[LATTACK]._skillWidth += 20 * (2 * (_isRight)-1);
		}
		if (jakeAttackInt == 25)
		{
			_skill[LATTACK]._skillX += 15 * (2 * (_isRight)-1);
			_skill[LATTACK]._skillWidth += 30 * (2 * (_isRight)-1);
		}
		if (jakeAttackInt == 30)
		{
			_skill[LATTACK]._skillX -= 15 * (2 * (_isRight)-1);
			_skill[LATTACK]._skillWidth -= 30 * (2 * (_isRight)-1);
		}
		if (jakeAttackInt == 35)
		{
			_skill[LATTACK]._skillX -= 15 * (2 * (_isRight)-1);
			_skill[LATTACK]._skillWidth -= 30 * (2 * (_isRight)-1);
		}
		if (jakeAttackInt == 40)
		{
			_skill[LATTACK]._skillX -= 25 * (2 * (_isRight)-1);
			_skill[LATTACK]._skillWidth -= 50 * (2 * (_isRight)-1);
		}


		if (!_playerMotion->isPlay())
		{
			if (!jakeAttackBool)
			{
				jakeAttackBool = true;
				_playerMotion->pause();
				_playerMotion->start();
			}
			else if (jakeAttackBool)
			{
				_state = IDLE;
				aniInput("stageLeftIdle", "stageRightIdle");
				_isAttack = false;
				jakeAttackBool = false;

			}
		}
	}

	if (_state != CROUCH && _state != CROUCHATTACK && _state != TACKLE)
	{
		crouchInt = 0;
	}

	if (_state != JUMP && _state != JUMPATTACK)
	{
		downJumpLeftInt = 0;
		downJumpRightInt = 0;
	}

	if (_state != FINNATTACK1 && _state != FINNATTACK2 && _state !=FINNATTACK3 && _state !=  CROUCHATTACK && _state != JUMPATTACK && _state != CROUCHATTACK && _state != TACKLE && _state != JAKEATTACK)
	{
		_isAttack = false;
	}

	if (_state != FINNATTACK1)
	{
		finnAttack1Bool = false;
		_skill[ATTACK1]._isFire = false;
	}
	if (_state != FINNATTACK2)
	{
		finnAttack2Bool = false;
		_skill[ATTACK2]._isFire = false;
	}
	if (_state != FINNATTACK3)
	{
		finnAttack3Bool = false;
		_skill[ATTACK3]._isFire = false;
	}
	if (_state != JUMPATTACK)
	{
		jumpAttackBool = false;
		_skill[JATTACK]._isFire = false;
	}
	if (_state != CROUCHATTACK)
	{
		crouchAttackBool = false;
		_skill[CATTACK]._isFire = false;
	}
	if (_state != TACKLE)
	{
		tackleBool = false;
		_skill[TATTACK]._isFire = false;
	}
	if (_state != JAKEATTACK)
	{
		jakeAttackInt = 0;
		jakeAttackBool = false;
		_skill[LATTACK]._isFire = false;
		
	}

	//스킬1을 썻을때 (하바네로)
	if (_isSkill1Fire)
	{
		if (_skill[FIREATTACK]._isFire)
		{
			_skill[FIREATTACK]._skillX += 10 * ((2 * _fireDirection) - 1);
			_skill[FIREATTACK]._skillY = _fireY;
		}


		if (fireInt == 0)
		{
			skillFire(FIREATTACK, _x, _y, _isRight);
			fireInt++;
		}
		if (fireInt >= 1)
		{
			fireInt++;
		}
		if (fireInt > 200)
		{
			fireInt = 0;
			fireCount++;
		}
		if (fireCount == 6)
		{
			_isSkill1Fire = false;
			_skill[FIREATTACK]._isFire = false;
			fireInt = 0;
			fireCount = 0;
		}
	}

	//스킬2를 썻을때 (벌)
	if (_isSkill2Fire)
	{
		/*if (!beeBool)
		{
		skillFire(BEEATTACK, _x, _y, _isRight);
		beeBool = true;
		}

		_skill[BEEATTACK]._skillX += 12 * sinf(theta + PI);
		_skill[BEEATTACK]._skillY += 3 * cosf(theta);
		theta += 0.1f;*/

		if (_skill[BEEATTACK]._isFire)
		{
			_skill[BEEATTACK]._skillX = _skill[BEEATTACK]._skillX + 5 * ((2 * _beeDirection) - 1) - 20 * sinf(theta);
			_skill[BEEATTACK]._skillY = _beeY + 70 * cosf(theta);
			theta += 0.2;
		}


		if (beeInt == 0)
		{
			skillFire(BEEATTACK, _x, _y, _isRight);
			beeInt++;
		}
		if (beeInt >= 1)
		{
			beeInt++;
		}
		if (beeInt > 200)
		{
			beeInt = 0;
			beeCount++;
		}
		if (beeCount == 6)
		{
			_isSkill2Fire = false;
			_skill[BEEATTACK]._isFire = false;
			beeInt = 0;
			beeCount = 0;
		}

	}

	//스킬3 점프를썻을때
	if (_isSkill3Fire)
	{
		_skill3Count++;
		if (_skill3Count > 600)
		{
			_skill3Count = 0;
			_isSkill3Fire = false;
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

	//스킬도 따라 움직여야지
	for (int i = DEFAULT; i < SKILLEND; i++)
	{
		if (!_skill[i]._isFire) continue;
		_skill[i]._skillX += _speedX * moveTime;
		_skill[i]._skillY += _speedY * moveTime;
	}
	
	

	//중력적용
	if (_state == JUMP || _state == JUMPATTACK)
	{
		_speedY += GRAVITY * moveTime;
	}

	if (_state == HIT && _speedY != 0)
	{
		_speedY += GRAVITY * moveTime;
	}

	//렉트크기 재조정
	if (_state != CROUCH && _state != CROUCHATTACK && _state != TACKLE)
	{
		_bodyRC = RectMakeCenter(_x, _y, _width, _height);
	}
	
}
void stagePlayer::skillUpdate()
{
	_skill[ATTACK1]._damage = 1 + DATABASE->getStatusAttack();
	_skill[ATTACK2]._damage = 2 + DATABASE->getStatusAttack();
	_skill[ATTACK3]._damage = 1 + DATABASE->getStatusAttack();
	_skill[LATTACK]._damage = 1 + DATABASE->getStatusAttack();
	_skill[JATTACK]._damage = 2 + DATABASE->getStatusAttack();
	_skill[CATTACK]._damage = 1 + DATABASE->getStatusAttack();
	_skill[TATTACK]._damage = 1 + DATABASE->getStatusAttack();
	_skill[BEEATTACK]._damage = 2;
	_skill[FIREATTACK]._damage = 3;

	for (int i = DEFAULT; i < SKILLEND; i++)
	{
		_skill[i]._hitBox = RectMakeCenter(_skill[i]._skillX, _skill[i]._skillY, _skill[i]._skillWidth, _skill[i]._skillHeight);
	}
}
void stagePlayer::statusControl()
{
	_status_hearts = DATABASE->getStatusHearts();
	_maxHP = 8 + 4 * _status_hearts;
	if (DATABASE->getuseItem())
	{
		_currentHP = DATABASE->getStatusCureentHP();
		DATABASE->imuseItemend();
	}
	if (_currentHP >= _maxHP)
	{
		_maxHP = _currentHP;
	}

	DATABASE->setStatusCurrentHP(_currentHP);
	_status_attack = DATABASE->getStatusAttack();
	_status_speed = DATABASE->getStatusSpeed();
	

	

	if (_currentHP <= 0)
	{
		_state = DEAD;
	}

	if (DATABASE->getEffect(0))
	{
		_isSkill1Fire = true;
		DATABASE->effectOff(0, false);
	}

	if (DATABASE->getEffect(1))
	{
		_isSkill2Fire = true;
		DATABASE->effectOff(1, false);
	}

	if (DATABASE->getEffect(2))
	{
		_isSkill3Fire = true;
		DATABASE->effectOff(2, false);
	}
}

// 초기화에 들어가는 함수들

void stagePlayer::animaitionInit()
{
	_basicImage = IMAGEMANAGER->addFrameImage("스테이지기본모션", "playerImage/핀_스테이지_기본모션.bmp", 0, 0, 2000, 1792, 10, 14, true, RGB(255, 0, 255));
	_attackImage = IMAGEMANAGER->addFrameImage("스테이지공격모션", "playerImage/핀_스테이지_공격.bmp", 0, 0, 3000, 1280, 10, 10, true, RGB(255, 0, 255));
	_fireImage = IMAGEMANAGER->addFrameImage("하바네로", "playerImage/FINN_HABANERO.bmp", 0, 0, 72, 24, 3, 1, true, RGB(255, 0, 255));
	_beeWingImage = IMAGEMANAGER->addFrameImage("벌과날개", "playerImage/벌과날개.bmp", 0, 0, 60, 50, 2, 2, true, RGB(255, 0, 255));

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

	int rightCrouch[] = {35,36,37,38 };
	KEYANIMANAGER->addArrayFrameAnimation("stageRightCrouch", "스테이지기본모션", rightCrouch, 4, 15, false);

	int leftCrouch[] = { 104,103,102,101 };
	KEYANIMANAGER->addArrayFrameAnimation("stageLeftCrouch", "스테이지기본모션", leftCrouch, 4, 15, false);

	int rightHit[] = { 41,42,43,44 };
	KEYANIMANAGER->addArrayFrameAnimation("stageRightHit", "스테이지기본모션", rightHit, 4, 15, false);

	int leftHit[] = { 118,117,116,115 };
	KEYANIMANAGER->addArrayFrameAnimation("stageLeftHit", "스테이지기본모션", leftHit, 4, 15, false);

	int rightDead[] = { 46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66 };
	KEYANIMANAGER->addArrayFrameAnimation("stageRightDead", "스테이지기본모션", rightDead, 21, 15, false);

	int leftDead[] = { 113,112,111,110,129,128,127,126,125,124,123,122,121,120,139,138,137,136,135,134,133 };
	KEYANIMANAGER->addArrayFrameAnimation("stageLeftDead", "스테이지기본모션", leftDead, 21, 15, false);

	int rightFinnAttack1[] = { 0,1,2 };
	KEYANIMANAGER->addArrayFrameAnimation("stageRightFinnAttack1", "스테이지공격모션", rightFinnAttack1, 3, 15, false);

	int leftFinnAttack1[] = { 59,58,57 };
	KEYANIMANAGER->addArrayFrameAnimation("stageLeftFinnAttack1", "스테이지공격모션", leftFinnAttack1, 3, 15, false);

	int rightFinnAttack2[] = { 3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("stageRightFinnAttack2", "스테이지공격모션", rightFinnAttack2, 3, 15, false);

	int leftFinnAttack2[] = { 56,55,54 };
	KEYANIMANAGER->addArrayFrameAnimation("stageLeftFinnAttack2", "스테이지공격모션", leftFinnAttack2, 3, 15, false);

	int rightFinnAttack3[] = { 6,7,8,9 };
	KEYANIMANAGER->addArrayFrameAnimation("stageRightFinnAttack3", "스테이지공격모션", rightFinnAttack3, 4, 15, false);

	int leftFinnAttack3[] = { 53,52,51,50 };
	KEYANIMANAGER->addArrayFrameAnimation("stageLeftFinnAttack3", "스테이지공격모션", leftFinnAttack3, 4, 15, false);

	int rightJumpAttack[] = { 11,12,13,14,15,16 };
	KEYANIMANAGER->addArrayFrameAnimation("stageRightJumpAttack", "스테이지공격모션", rightJumpAttack, 6, 15, false);

	int leftJumpAttack[] = { 68,67,66,65,64,63 };
	KEYANIMANAGER->addArrayFrameAnimation("stageLeftJumpAttack", "스테이지공격모션", leftJumpAttack, 6, 15, false);

	int rightCrouchAttack[] = { 18,19,20,21,22,23 };
	KEYANIMANAGER->addArrayFrameAnimation("stageRightCrouchAttack", "스테이지공격모션", rightCrouchAttack, 6, 15, false);

	int leftCrouchAttack[] = { 61,60,79,78,77,76 };
	KEYANIMANAGER->addArrayFrameAnimation("stageLeftCrouchAttack", "스테이지공격모션", leftCrouchAttack, 6, 15, false);

	int rightTackle[] = { 25,26,27,28,29,30,31 };
	KEYANIMANAGER->addArrayFrameAnimation("stageRightTackle", "스테이지공격모션", rightTackle, 7, 15, false);

	int leftTackle[] = { 74,73,72,71,70,89,88 };
	KEYANIMANAGER->addArrayFrameAnimation("stageLeftTackle", "스테이지공격모션", leftTackle, 7, 15, false);

	int rightJakeAttack[] = { 33,34,35,36,37,38,39,40,41,42,43,44 };
	KEYANIMANAGER->addArrayFrameAnimation("stageRightJakeAttack", "스테이지공격모션", rightJakeAttack, 12, 15, false);

	int leftJakeAttack[] = { 86,85,84,83,82,81,80,99,98,97,96,95 };
	KEYANIMANAGER->addArrayFrameAnimation("stageLeftJakeAttack", "스테이지공격모션", leftJakeAttack, 12, 15, false);

	int fireAttack[] = { 0,1,2 };
	KEYANIMANAGER->addArrayFrameAnimation("habaneroAttack", "하바네로", fireAttack, 3, 15, true);

	_fireAnimation = KEYANIMANAGER->findAnimation("habaneroAttack");
	_fireAnimation->start();

	int beeRight[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("beeRight", "벌과날개", beeRight, 1, 15, false);

	int beeLeft[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("beeLeft", "벌과날개", beeLeft, 1, 15, false);

	int wingRight[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("wingRight", "벌과날개", wingRight, 1, 15, false);

	int wingLeft[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("wingLeft", "벌과날개", wingLeft, 1, 15, false);

	




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
void stagePlayer::skillInit()
{
	/*_skill[ATTACK1]._damage = 1 +DATABASE->getStatusAttack();
	_skill[ATTACK2]._damage = 2 + DATABASE->getStatusAttack();;
	_skill[ATTACK3]._damage = 1 + DATABASE->getStatusAttack();;
	_skill[LATTACK]._damage = DATABASE->getStatusAttack();;
	_skill[JATTACK]._damage = 2 + DATABASE->getStatusAttack();;
	_skill[CATTACK]._damage = 1 + DATABASE->getStatusAttack();;
	_skill[TATTACK]._damage = DATABASE->getStatusAttack();;
	_skill[BEEATTACK]._damage = 10;
	_skill[FIREATTACK]._damage = 5;*/

	for (int i = DEFAULT; i < SKILLEND; i++)
	{
		_skill[i]._skillX = 0;
		_skill[i]._skillY = 0;
		_skill[i]._skillWidth = 0;
		_skill[i]._skillHeight = 0;
		_skill[i]._isFire = false;
	}
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



void stagePlayer :: skillFire(SKILLNAME skillName, int x, int y, bool isRight)
{
	_skill[skillName]._isFire = true;

	if (skillName == ATTACK1 || skillName == ATTACK2)
	{
		_skill[skillName]._skillX = (x + 35 * (2 * (isRight)-1));
		_skill[skillName]._skillY = y - 10;
		_skill[skillName]._skillWidth = 30;
		_skill[skillName]._skillHeight = 10;
	}
	else if (skillName == ATTACK3)
	{
		_skill[skillName]._skillX = (x + 30 * (2 * (isRight)-1));
		_skill[skillName]._skillY = y - 30;
		_skill[skillName]._skillWidth = 10;
		_skill[skillName]._skillHeight = 40;
	}

	else if (skillName == CATTACK)
	{
		_skill[skillName]._skillX = (x + 40 * (2 * (isRight)-1));
		_skill[skillName]._skillY = y + 25;
		_skill[skillName]._skillWidth = 40;
		_skill[skillName]._skillHeight = 10;
	}

	else if (skillName == JATTACK)
	{
		_skill[skillName]._skillX = (x + 40 * (2 * (isRight)-1));
		_skill[skillName]._skillY = y - 10;
		_skill[skillName]._skillWidth = 50;
		_skill[skillName]._skillHeight = 10;
	}

	else if (skillName == TATTACK)
	{
		_skill[skillName]._skillX = (x + 40 * (2 * (isRight)-1));
		_skill[skillName]._skillY = y + 25;
		_skill[skillName]._skillWidth = 45;
		_skill[skillName]._skillHeight = 10;
	}

	else if (skillName == LATTACK)
	{
		_skill[skillName]._skillX = x;
		_skill[skillName]._skillY = y - 20;
		_skill[skillName]._skillWidth = 0;
		_skill[skillName]._skillHeight = 20;
		jakeAttackInt = 0;
	}

	else if (skillName == BEEATTACK)
	{
		_skill[skillName]._skillX = x;
		_skill[skillName]._skillY = y - 60;
		_beeY = y - 60;
		_skill[skillName]._skillWidth = 20;
		_skill[skillName]._skillHeight = 20;
		_beeDirection = _isRight;
	}

	else if (skillName == FIREATTACK)
	{
		_skill[skillName]._skillX = x + 40 * (2 * (isRight)-1);
		_skill[skillName]._skillY = _bodyRC.top + 20;
		_fireY = _bodyRC.top + 20;
		_skill[skillName]._skillWidth = 24;
		_skill[skillName]._skillHeight = 24;
		_fireDirection = _isRight;
	}
}

