#pragma once
#include "gameNode.h"
#include "stagePlayer.h"

#define SPEED 2
#define BULLETSPEED 4
#define COUNTMAX 70
#define	COUNTMINI 10
#define ATTACKRANGE 100
#define BULLETRANGE 250

class stagePlayer;
class Bullet;

enum BWORMDIRECTION
{
	BDIRECTION_IDLE,
	BDIRECTION_MOVE,
	BDIRECTION_ATTACK,
	BDIRECTION_HIT,
	BDIRECTION_END,
};

class bigWorm : public gameNode
{
private:
	image*			_image;
	RECT			_rc, _moveRc;
	stagePlayer*	_sp;
	BWORMDIRECTION	_direction;
	std::vector<Bullet*> _vBullet;

	float			_x, _y;

	int				_frameX, _frameY;
	int				_frameNum;

	bool			_isRight;
	int				_count;
	int				_bulletDelay;

	int				_HP;

public:
	HRESULT init(float x, float y, stagePlayer* z, int moveLength);
	void release();
	void update();
	void render();

	//�Խ���
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
	void delHP(int Num) { _HP -= Num; }
	int getHP(void) { return _HP; }

	void makeBullet(float x, float y, float angle);

	std::vector<Bullet*> getVector(void) { return _vBullet; }

	void eraseBullet(int Num) { _vBullet.erase(_vBullet.begin() + Num); }

	bigWorm();
	~bigWorm();
};

class Bullet : public gameNode
{
private :
	float _x, _y;
	float _StartX, _StartY;
	image* _bullet;
	RECT _rc;
	int _frameX;
	float _angle;
	int _count;

public:
	HRESULT init(float x, float y, float angle);
	void release();
	void update();
	void render();

	float getX() { return _x; }
	float getY() { return _y; }
	float getStartX() { return _StartX; }
	float getStartY() { return _StartY; }

	RECT getRect() { return _rc; }

	Bullet();
	~Bullet();
};