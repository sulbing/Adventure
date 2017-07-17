#pragma once
#include "gameNode.h"
#define JUMPPOWER 10
#define GRAVITY 0.2
#define MOVESPEED 5

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
	STATEEND
};

class stagePlayer : public gameNode
{
private:
	//�⺻����
	int _maxHP;
	int _currentHP;
	float _x, _y;
	float _width, _height;
	RECT _bodyRC;
	float _speedX, _speedY;
	float _jumpPower, _gravity;
	bool _isRight;
	bool _isLookUp;
	PLAYERSTATE _state;
	

	//�������ͽ�
	int _status_hearts;
	int _status_attack;
	int _status_speed;



	//1����ų - ��������
	bool _isSkill1Fire;
	//2����ų - �� �߻�
	bool _isSkill2Fire;
	//3����ų - ����ũ����
	bool _isSkill3Fire;



	//������Ʈ�� �� �Լ�
	void keyControl();
	void stateControl();
	void basicMove();


public:
	//���ӳ���Լ�
	virtual HRESULT init(int hearts, int attack, int speed, int currentHP, float x, float y, bool isRight);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);



	//����
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

	//����
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

	stagePlayer();
	~stagePlayer();
};

