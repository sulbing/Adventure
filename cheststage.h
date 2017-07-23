#pragma once
<<<<<<< HEAD
#include "gameNode.h"
#include "stagePlayer.h"
#include "sceneEffect.h"
#include "item.h"

=======
#include"gameNode.h"
#include"stagePlayer.h"
#include"sceneEffect.h"
#include "UI.h"
>>>>>>> 9ec2cb822d8dff8dc27141c0a21711d338485501

class cheststage : public gameNode
{
private:
	stagePlayer* _stageFinn;
	UI* _UI;
	RECT _leftDoor, _rightDoor;

	RECT _chestRc;
	sceneEffect* _sceneEffect;
	item* _item;

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
	void itemOut(void);

	cheststage();
	~cheststage();
};

