#pragma once
#include "gameNode.h"
#include "stagePlayer.h"

#define SPEED 5
#define COUNTMAX 70
#define	COUNTMINI 10
#define ATTACKRANGE 70

class stagePlayer;

enum WORMDIRECTION
{
	DIRECTION_MOVE,
	DIRECTION_ATTACK,
	DIRECTION_HIT,
	DIRECTION_END,
};

class littleWorm : public gameNode
{
private:
	image*			_image;
	RECT			_rc, _moveRc;
	stagePlayer*	_sp;
	WORMDIRECTION	_direction;

	float			_x, _y;
	
	int				_frameX, _frameY;
	int				_frameNum;

	bool			_isRight;
	int				_count;

public:
	HRESULT init(float x, float y, stagePlayer* z, int moveLength);
	void release();
	void update();
	void render();

	//ÇÔ½½¶÷
	void frameManiger();
	void move();
	void Hitmove();
	void countupdate();

	//GET & SET
	RECT getRect() { return _rc; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	float getX(void) { return _x; }
	float getY(void) { return _y; }
	int getState() { return (int)_direction; }
	void setHit();


	littleWorm();
	~littleWorm();
};