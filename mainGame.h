#pragma once
#include "gameNode.h"
#include "openingScene.h"
#include "worldMapScene.h"
#include "nymphStage.h"
#include "statusScene.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"
#include "cheststage.h"
#include "minimapScene.h"
#include "inventoryScene.h"
#include "darkForest.h"
#include "bossScene.h"

class inventoryScene;


class mainGame : public gameNode
{
private:

public:
	virtual HRESULT init(void);		
	virtual void release(void);		
	virtual void update(void);		
	virtual void render(void);

	void addImage();
	void addSound();


	mainGame();
	~mainGame();
};

