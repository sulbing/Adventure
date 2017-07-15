#pragma once
#include "gameNode.h"

class openingScene : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	openingScene();
	~openingScene();
};

