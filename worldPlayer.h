#pragma once
#include "gameNode.h"
#define FJDISTANCE 50

class worldPlayer : public gameNode
{
	

private:
	RECT _finnRC;
	RECT _jakeRC;
	bool _haveBridgeSkill;
	bool _haveClimbSkill;


	//ÁÂÇ¥
	float _x, _y;
	float _speedX, _speedY;
	float _jakeX, _jakeY;
	float _jakeAngle;

	
	void keyControl();
	void basicMove();

public:

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);


	worldPlayer();
	~worldPlayer();
};

