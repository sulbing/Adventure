#pragma once
#include"gameNode.h"
#include"stagePlayer.h"
#include"sceneEffect.h"
#include"item.h"
#include <vector>
#include "UI.h"
#include "bigWorm.h"

class bossScene : public gameNode
{
private:

	bigWorm*		_bw;
	UI*				_UI;
	stagePlayer*	_stageFinn;
	BOOL			_isTurn = false;
	int				_camX, _camY;
	RECT			_leftDoor, _rightDoor;
	sceneEffect*	_sceneEffect;

	BOOL			_isChange = false;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void pixelCollision(void);
	void camMove(void);

	void setItem(int x, int y);
	void eatItem(void);

	void attackCollision(void);


public:
	bossScene();
	~bossScene();
};

