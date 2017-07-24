#pragma once
#include "gameNode.h"
#include "stagePlayer.h"

#define MINION1SPEED 2.5f
#define RNDNUMMAX 50
#define RNDNUMLOW 10
#define GRAVITY 5
#define HITPUSH 5

enum MINIONDIRECTION
{
	DIRECTION_RIGHT_MOVE,
	DIRECTION_LEFT_MOVE,
	DIRECTION_RIGHT_ATTACK,
	DIRECTION_LEFT_ATTACK,
	DIRECTION_RIGHT_HIT,
	DIRECTION_LEFT_HIT,
	DIRECTION_RIGHT_DIE,
	DIRECTION_LEFT_DIE,
};

enum BOSSDIRECTION
{
	BOSSDIRECTION_RIGHT_STAND,
	BOSSDIRECTION_LEFT_STAND,
	BOSSDIRECTION_RIGHT_MOVE,
	BOSSDIRECTION_LEFT_MOVE,
	BOSSDIRECTION_RIGHT_ATTACK,
	BOSSDIRECTION_LEFT_ATTACK,
	BOSSDIRECTION_RIGHT_ATTACK2,
	BOSSDIRECTION_LEFT_ATTACK2,
	BOSSDIRECTION_RIGHT_HIT,
	BOSSDIRECTION_LEFT_HIT,
	BOSSDIRECTION_RIGHT_DIE,
	BOSSDIRECTION_LEFT_DIE,
};

class stagePlayer;

class enemy : public gameNode
{
private:
	MINIONDIRECTION	_direction;
	BOSSDIRECTION	_direction2;

	stagePlayer*	_sp;
	image*			_image;
	animation*		_minionAni;
	RECT			_rc;
	RECT			_hitBox;

	bool			_isTurn;
	bool			_bossTrun;
	int				_count;
	int				_maxCount;
	int				_type;
	float			_time;
	float			_x, _y;
	float			_currentHP;
	float			_maxHP;
	float			_minionATK;
	float			_bossATK;

public:
	HRESULT init(int type, float x, float y, stagePlayer* z);
	void release();
	void update();
	void render();

	static void rightAttack(void* obj);
	static void leftAttack(void* obj);
	static void rightHit(void* obj);
	static void leftHit(void* obj);

	static void rightAttackB1(void* obj);
	static void leftAttackB1(void* obj);
	static void rightAttackB2(void* obj);
	static void leftAttackB2(void* obj);
	static void rightHitB(void* obj);
	static void leftHitB(void* obj);

	void initAni1();
	void initAni2();
	void initAni3();
	void initAni4();
	void initAniMove1();
	void initAniMove2();
	void initAniMove3();
	void initAniMove4();

	MINIONDIRECTION getDirection(void) { return _direction; }
	void setDirection(MINIONDIRECTION direction) { _direction = direction; }

	BOSSDIRECTION getDirection2(void) { return _direction2; }
	void setDirection2(BOSSDIRECTION direction2) { _direction2 = direction2; }

	animation* getMinionAni(void) { return _minionAni; }
	void setMinionAni(animation* ani) { _minionAni = ani; }

	//get & set
	int getType() { return _type; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	float getX(void) { return _x; }
	float getY(void) { return _y; }
	RECT getRect(void) { return _rc; }
	int getState() { return (int)_direction; }
	RECT getHitBox() { return _hitBox; }

	void changeHit();

	enemy();
	~enemy();
};
