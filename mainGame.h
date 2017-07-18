#pragma once
#include "gameNode.h"
#include "openingScene.h"
#include "worldMapScene.h"
#include "nymphStage.h"


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

