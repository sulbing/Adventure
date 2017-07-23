#pragma once
#include"gameNode.h"
#include"stagePlayer.h"
#include"enemy.h"
#include "sceneEffect.h"
#include "worldPlayer.h"


class nymphStage : public gameNode
{
private:
	image*			_nymph;
	animation*		 _nymphAni;
	RECT			_leftDoor, _rightDoor;
	BOOL			_isChange;
	stagePlayer*	_stageFinn;
	//enemy*			_mi1;
	sceneEffect* _sceneEffect;

	worldPlayer* _test;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void pixelCollision(void);
	void stageDoor(void);

	nymphStage();
	~nymphStage();
};