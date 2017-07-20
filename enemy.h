#pragma once
#include "gameNode.h"

#define MINION1SPEED 2.5f
#define RNDNUMMAX 50
#define RNDNUMLOW 10
#define GRAVITY 5

enum MINIONDIRECTION
{
	DIRECTION_RIGHT_STOP,
	DIRECTION_LEFT_STOP,
	DIRECTION_RIGHT_MOVE,
	DIRECTION_LEFT_MOVE,
	DIRECTION_RIGHT_ATTACK,
	DIRECTION_LEFT_ATTACK,
	DIRECTION_RIGHT_HIT,
	DIRECTION_LEFT_HIT,
	DIRECTION_RIGHT_DIE,
	DIRECTION_LEFT_DIE,
};

class enemy : public gameNode
{
private:
	MINIONDIRECTION	_direction;

	//Åä³¢
	image*		_minion;
	RECT		_rc;

	bool		_isTurn;

	//°ø¿ë
	animation*	_minionAni;
	int			_count;
	int			_maxCount;

	int			_type;

	float		_time;
	float		_x, _y;


public:
	HRESULT init(int type, float x, float y);
	void release();
	void update(int type);
	void render();

	static void rightMove1(void* obj);
	static void leftMove1(void* obj);
	static void rightAttack1(void* obj);
	static void leftAttack1(void* obj);
	static void rightHit1(void* obj);
	static void leftHit1(void* obj);

	//Åä³¢
	void minion1Init();
	void minion1Move();

	//Áö··ÀÌ
	void minion2Init();
	void minion2Move();

	MINIONDIRECTION getDirection(void) { return _direction; }
	void setDirection(MINIONDIRECTION direction) { _direction = direction; }

	animation* getMinionAni(void) { return _minionAni; }
	void setMinionAni(animation* ani) { _minionAni = ani; }

	int getType(void) { return _type; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	float getX(void) { return _x; }
	float getY(void) { return _y; }
	RECT getRect(void) { return _rc; }

	int getState() { return (int)_direction; }

	void jumpSet(float y) { _time = -1.5f; _y = y; }
	void turn();

	enemy();
	~enemy();
};

