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

class worldPlayer : public gameNode
{
	

private:

	RECT _finnRC;
	RECT _jakeRC;
	bool _haveBridgeSkill;
	bool _haveClimbSkill;
	WORLDFINNSTATE _state;

	int _bridgeProcInt = 0;

	//ÁÂÇ¥
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

public:

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void setBridge(int startX, int startY, int EndX, int EndY);

	worldPlayer();
	~worldPlayer();
};

