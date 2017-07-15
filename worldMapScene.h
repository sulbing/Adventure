#pragma once
#include"gameNode.h"

class worldMapScene : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	worldMapScene();
	~worldMapScene();
};

