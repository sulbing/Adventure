#pragma once
#include "gameNode.h"
#include "openingScene.h"
#include "worldMapScene.h"
#include "nymphStage.h"
#include "inventoryScene.h"
#include "statusScene.h"
#include "stage1.h"
#include "minimapScene.h"


class mainGame : public gameNode
{
private:

public:
	virtual HRESULT init(void);		
	virtual void release(void);		
	virtual void update(void);		
	virtual void render(void);

	void addImage();


	mainGame();
	~mainGame();
};

