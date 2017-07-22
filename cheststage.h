#pragma once
#include"gameNode.h"
#include"stagePlayer.h"
#include"sceneEffect.h"


class cheststage : public gameNode
{
private:
	stagePlayer* _stageFinn;
	RECT _leftDoor, _rightDoor;
	sceneEffect* _sceneEffect;

	BOOL _isChange = false;

public:
	cheststage();
	~cheststage();
};

