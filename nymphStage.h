#pragma once
#include"gameNode.h"
#include"stagePlayer.h"
#include"enemy.h"
#include "sceneEffect.h"
<<<<<<< HEAD
#include "worldPlayer.h"

=======
#include "UI.h"
>>>>>>> b4334222aff9758127bffa73803b0e7852231351

class nymphStage : public gameNode
{
private:
	UI*				_UI;
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