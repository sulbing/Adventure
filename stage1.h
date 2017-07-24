#pragma once
#include"gameNode.h"
#include"stagePlayer.h"
#include"sceneEffect.h"
#include"item.h"
#include <vector>
#include "UI.h"
#include "littleWorm.h"

class stage1 : public gameNode
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
	void addEnemy();
	void setItem(void);

	void eatItem(void);

public:
	stage1();
	~stage1();
};

