#pragma once
#include"gameNode.h"
#include"stagePlayer.h"

class stage1 : public gameNode
{
private:
	stagePlayer* _stageFinn;
	BOOL _isTurn = false;
	int _camX, _camY;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void pixelCollision(void);
	void camMove(void);

public:
	stage1();
	~stage1();
};

