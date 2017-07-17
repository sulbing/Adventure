#pragma once
#include"gameNode.h"

class worldMapScene : public gameNode
{
private:
	float _cameraX;
	float _cameraY;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	worldMapScene();
	~worldMapScene();
};

