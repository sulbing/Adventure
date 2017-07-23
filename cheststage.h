#pragma once
#include "gameNode.h"
#include "stagePlayer.h"
#include "sceneEffect.h"
#include "item.h"
<<<<<<< HEAD
#include"gameNode.h"
#include"stagePlayer.h"
#include"sceneEffect.h"
=======
>>>>>>> af3c4e9e9a084b85c2a1d74cb05de85cdd2811fb
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

