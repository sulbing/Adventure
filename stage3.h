#pragma once
#include"gameNode.h"
#include"stagePlayer.h"
#include"sceneEffect.h"
#include "UI.h"
#include "item.h"
#include "littleWorm.h"

class stage3 : public gameNode
{
private:
	typedef vector<item*> vstageItem;
	typedef vector<item*>::iterator vistageItem;

	std::vector<littleWorm*> _vLittleWorm;

	vstageItem _vstageItem;
	vistageItem _vistageItem;

	UI* _UI;
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

	void setItem(void);
	void eatItem(void);

	void addEnemy();

public:
	stage3();
	~stage3();
};

