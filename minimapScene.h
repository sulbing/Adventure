#pragma once
#include "gameNode.h"

class minimapScene : public gameNode
{
private:
	image* _worldMap;
	image* _face;
	float _x, _y;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	minimapScene();
	~minimapScene();
};

