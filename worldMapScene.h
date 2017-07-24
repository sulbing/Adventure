#pragma once
#include "gameNode.h"
#include "sceneEffect.h"
#include "UI.h"
#include "worldPlayer.h"

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
	UI* _UI;
	worldPlayer* _worldPlayer;

	image* _background;
	int _mapSizeWidth;
	int _mapSizeHeight;

	int _x,  _y;			//ĳ���� x, y
	RECT _rc;				//ĳ���� RECT

	//									����1	����2	�Ͽ콺	1��		1��		2��		2��		3��		3��		����		�ߺ���	�ٸ���	�ٸ��Ʒ�	�ö󰡱�1	�ö󰡱�2
	float _playerX[RECTCOLLISION_END] = { 944,	2109,	1517,	955,	976,	2200,	2368,	2333,	2300,	1132,	2410,	1917,	1917,	2357,	2492, 2495};
	float _playerY[RECTCOLLISION_END] = { 404,	1020,	957,	641,	467,	1809,	1658,	932,	679,	455,	1593,	1572,	1746,	618,	415, 239};

	int _probeTop;
	int _probeBottom;
	int _probeLeft;
	int _probeRight;

	bool _isChange;

	DIRECTION _direction;
	RECT _rcSour[4];

	RECT _eventRC[RECTCOLLISION_END];

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	DIRECTION getDirection(int x, int y);

	void pixelCollision();
	void rectCollision();

	worldMapScene();
	~worldMapScene();
};

