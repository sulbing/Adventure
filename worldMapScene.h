#pragma once
#include "gameNode.h"
#include "sceneEffect.h"

enum DIRECTION
{
	DIRECTION_LEFT_TOP,
	DIRECTION_MIDDLE_TOP,
	DIRECTION_RIGHT_TOP,
	DIRECTION_LEFT_MIDDLE,
	DIRECTION_MIDDLE_MIDDLE,
	DIRECTION_RIGHT_MIDDLE,
	DIRECTION_LEFT_BOTTOM,
	DIRECTION_MIDDLE_BOTTOM,
	DIRECTION_RIGHT_BOTTOM
};

class worldMapScene : public gameNode
{
private:
	sceneEffect* _sceneEffect;

	image* _background;
	int _mapSizeWidth;
	int _mapSizeHeight;

	int _x, _y;				//캐릭터 x, y
	RECT _rc;				//캐릭터 RECT

	int _probeTop;
	int _probeBottom;
	int _probeLeft;
	int _probeRight;


	DIRECTION _direction;
	RECT _rcSour[4];

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	DIRECTION getDirection(int x, int y);

	void pixelCollision();

	worldMapScene();
	~worldMapScene();
};

