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

class minion1 : public gameNode
{
private:
	MINIONDIRECTION	_direction;

	image*		_minion1;
	RECT		_rc;
	animation*	_minionAni;

	bool		_isTurn;
	float		_x, _y;
	int			_count;
	int			_maxCount;

	int			_type;

	float		_time;



public:
	HRESULT init(int type, float x, float y);
	void release();
	void update();
	void render();

	static void rightMove(void* obj);
	static void leftMove(void* obj);
	static void rightAttack(void* obj);
	static void leftAttack(void* obj);
	static void rightHit(void* obj);
	static void leftHit(void* obj);

	void move0();

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

	void jumpSet(float y) { _time = -1.5f; _y = y; }

	minion1();
	~minion1();
};

