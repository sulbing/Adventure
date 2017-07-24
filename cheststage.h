#pragma once
#include "gameNode.h"
#include "stagePlayer.h"
#include "sceneEffect.h"
#include "item.h"
#include"gameNode.h"
#include"stagePlayer.h"
#include"sceneEffect.h"
#include "UI.h"

class cheststage : public gameNode
{
private:
	stagePlayer* _stageFinn;
	UI* _UI;
	RECT _leftDoor, _rightDoor;

	RECT _chestRc;
	sceneEffect* _sceneEffect;
	item* _item;
	int _itemNum;
	BOOL _chestOpen = false;
	BOOL _isChange = false;
	BOOL _isChest;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void pixelCollision(void);
	void stageDoor(void);
	void chestOpen(void);
	void eatItem(void);

	cheststage();
	~cheststage();
};

