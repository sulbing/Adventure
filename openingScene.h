#pragma once
#include "gameNode.h"
#include "sceneEffect.h"

class openingScene : public gameNode
{
private:
	sceneEffect* _sceneEffect;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	openingScene();
	~openingScene();
};

