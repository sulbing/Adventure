#pragma once
#include"gameNode.h"
#include"stagePlayer.h"
#include"enemy.h"
#include "sceneEffect.h"
#include "UI.h"

class nymphStage : public gameNode
{
private:
	UI*				_UI;
	image*			_nymph;
	animation*		 _nymphAni;
	RECT			_leftDoor, _rightDoor;
	RECT			_nymphRC;
	BOOL			_isChange, _isSave;
	stagePlayer*	_stageFinn;
	sceneEffect* _sceneEffect;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void pixelCollision(void);
	void stageDoor(void);

	void save();

	nymphStage();
	~nymphStage();
};