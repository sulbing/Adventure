#pragma once
#include "gameNode.h"
#define FJDISTANCE 50

enum WORLDFINNSTATE
{
	WORLDSTART,
	WORLDIDLE,
	WORLDBRIDGE,
	WORLDEND
};

enum WORLDDIRECTION
{
	DIRECTIONSTART,
	TOP,
	TOPRIGHT,
	RIGHT,
	BOTTOMRIGHT,
	BOTTOM,
	BOTTOMLEFT,
	LEFT,
	TOPLEFT,
	DIRECTIONEND
};

class worldPlayer : public gameNode
{
	

private:

	RECT _finnRC;
	RECT _jakeRC;
	bool _haveBridgeSkill;
	bool _haveClimbSkill;
	WORLDFINNSTATE _state;
	WORLDDIRECTION _finnDirection;
	WORLDDIRECTION _jakeDirection;

	int _bridgeProcInt = 0;

	//��ǥ
	float _x, _y;
	float _speedX, _speedY;
	float _jakeX, _jakeY;
	float _jakeSpeedX, _jakeSpeedY;
	float _jakeAngle;

	float _bridgeStartX, _bridgeStartY;
	float _bridgeEndX, _bridgeEndY;

	
	void keyControl();
	void basicMove();
	
	void bridgeMove();

	void isDirection();

	void animationInit();

	//�Ұ�
	bool _isBridgeOpening = false;
	bool bridgeBool = false;

	bool _isBridgeState = false;




	//�̹��� ����
	image* _finnBasic;
	image* _jakeBasic;
	image* _jakeBridge;

	animation* _finnMotion;
	animation* _jakeMotion;

	//�Ұ�
	

public:

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void setBridge(int startX, int startY, int EndX, int EndY);


	//����
	float getWorldFinnX(void) { return _x; }
	float getWorldFinnY(void) { return _y; }
	RECT getWorldFinnRect(void) { return _finnRC; }
	bool getIsBridgeState(void) { return _isBridgeState; }

	//����
	void setWorldFinnX(float x) { _x = x; }
	void setWorldFinnY(float y) { _y = y; }


	worldPlayer();
	~worldPlayer();
};

