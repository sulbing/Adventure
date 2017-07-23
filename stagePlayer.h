#pragma once
#include "gameNode.h"
#define JUMPPOWER 8
#define GRAVITY 0.2
#define MOVESPEED 5
#define INTRODISTANCE 100

enum PLAYERSTATE
{
	IDLE,
	WALK,
	JUMP,
	CROUCH,
	CROUCHATTACK,
	TACKLE,
	FINNATTACK1,
	FINNATTACK2,
	FINNATTACK3,
	JAKEATTACK,
	JUMPATTACK,
	HIT,
	DEAD,
	INTRO,
	OUTRO,
	STATEEND
};

//스킬관련
struct TAGSKILL
{
	int _damage;
	RECT _hitBox;
	bool _isFire;
	float _skillWidth;
	float _skillHeight;
	float _skillX, _skillY;
};

enum SKILLNAME
{
	DEFAULT,
	ATTACK1, //1타공격
	ATTACK2, //2타공격
	ATTACK3, //3타공격
	LATTACK, // 긴공격 - 제이크 공격
	JATTACK, // 점프공격
	CATTACK, // 앉아공격
	TATTACK, // 태클
	BEEATTACK, // 벌 공격
	FIREATTACK, // 하바네로 공격
	SKILLEND
};
class stagePlayer : public gameNode
{
private:
	//기본정보
	int _maxHP;
	int _currentHP;
	float _x, _y;
	float _width, _height;
	float _startX, _startY;
	RECT _bodyRC;
	float _speedX, _speedY;
	float _jumpPower, _gravity;
	bool _isRight;
	bool _isLookUp;
	bool _isHit;
	bool _isAttack;
	PLAYERSTATE _state;

	image* _basicImage;
	image* _attackImage;

	animation* _playerMotion;

	//스테이터스
	int _status_hearts;
	int _status_attack;
	int _status_speed;



	//1번스킬 - 빨간고추
	bool _isSkill1Fire;
	//2번스킬 - 벌 발사
	bool _isSkill2Fire;
	//3번스킬 - 제이크방패
	bool _isSkill3Fire;



	//업데이트에 들어갈 함수
	void keyControl();
	void stateControl();
	void basicMove();
	void skillUpdate();

	//초기화에 들어갈 함수
	void animaitionInit();
	void skillInit();

	//애니메이션관련 함수
	void aniInput(std::string leftKey, std::string rightKey);



	//애니메이션 재생 관련 변수
	int downJumpLeftInt = 0;
	int downJumpRightInt = 0;
	int crouchInt = 0;
	int hitInt = 0;
	int hitCount = 0;
	bool finnAttack1Bool = false;
	bool finnAttack2Bool = false;
	bool finnAttack3Bool = false;
	bool jumpAttackBool = false;
	bool crouchAttackBool = false;
	bool tackleBool = false;
	bool jakeAttackBool = false;
	int jakeAttackInt = 0;
	bool tackleKnockBackBool = false;
	bool deadBool = false;
	bool beeBool = false;

	//스킬관련 변수
	TAGSKILL _skill[SKILLEND];
	void skillFire(SKILLNAME skillName, int x, int y, bool isRight);
	float theta = 0;

	//카메라 좌표 추가
	int _camX, _camY;


public:
	//게임노드함수
	virtual HRESULT init(int hearts, int attack, int speed, int currentHP, float x, float y, bool isRight);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);



	//게터
	int getCurrentHP() { return _currentHP; }
	int getMaxHP() { return _maxHP; }
	RECT getBodyRC() { return _bodyRC; }
	float getX() { return _x; }
	float getY() { return _y; }
	float getSpeedX() { return _speedX; }
	float getSpeedY() { return _speedY; }
	float getWidth() { return _width; }
	float getHeight() { return _height; }
	int getStatus_hearts(){ return _status_hearts; }
	int getStatus_attack() { return _status_attack; }
	int getStatus_speed() { return _status_speed; }
	float getJumpPower() { return _jumpPower; }
	float getGravity() { return _gravity; }
	int getState() { return _state; }
	bool getIsRight() { return _isRight; }
	bool getIsHit() { return _isHit; }
	RECT getSkillHitBox(int skillName) { return _skill[skillName]._hitBox; }

	//세터
	void setCurrentHP(int HP) { _currentHP = HP; }
	void setMaxHP(int HP) { _maxHP = HP; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	void setWidth(float width) { _width = width; }
	void setHeight(float height) { _height = height; }
	void setSpeedX(float speedX) { _speedX = speedX; }
	void setSpeedY(float speedY) { _speedY = speedY; }
	void setStatus_hearts(int hearts) { _status_hearts = hearts; }
	void setStatus_attack(int attack) { _status_attack = attack; }
	void setStatus_speed(int speed) { _status_speed = speed; }
	void setJumpPower(float jumpPower) { _jumpPower = jumpPower; }
	void setGravity(float gravity) { _gravity = gravity; }
	void setState(PLAYERSTATE state) { _state = state; }
	void setCamX(int x) { _camX = x; }
	

	//태클넉백함수
	void tackleKnockBack() { tackleKnockBackBool = true; }

	stagePlayer();
	~stagePlayer();
};

