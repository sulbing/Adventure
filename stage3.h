#pragma once
#include"gameNode.h"
#include"stagePlayer.h"
#include"sceneEffect.h"

class stage3 : public gameNode
{
private:
	stagePlayer* _stageFinn;
	BOOL _isTurn = false;
	int _camX, _camY;
	RECT _leftDoor, _rightDoor;
	sceneEffect* _sceneEffect;

	BOOL _isChange = false;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void pixelCollision(void);
	void stageDoor(void);
	void camMove(void);

public:
	stage3();
	~stage3();
};
