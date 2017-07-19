#pragma once
#include"gameNode.h"

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
	image* _background;
	int _mapSizeWidth;
	int _mapSizeHeight;

	RECT _rc;

	int _x, _y;				//Ä³¸¯ÅÍ x, y
	DIRECTION _direction;
	RECT _rcSour[4];

	//int _probe

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

