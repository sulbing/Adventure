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

//enum RECTCOLLISION
//{
//	STAGE_NYMPH_1,
//	STAGE_NYMPH_2,
//	STAGE_HOUSE,
//	STAGE_1_IN,
//	STAGE_1_OUT,
//	STAGE_2_IN,
//	STAGE_2_OUT,
//	STAGE_3_IN,
//	STAGE_3_OUT,
//	STAGE_CHEST,
//	STAGE_MIDBOSS,
//	JAKE_BRIDGE_IN,
//	JAKE_BRIDGE_OUT,
//	JAKE_CLIMB_1,
//	JAKE_CLIMB_2,
//	RECTCOLLISION_END
//};

class worldMapScene : public gameNode
{
private:
	sceneEffect* _sceneEffect;

	image* _background;
	int _mapSizeWidth;
	int _mapSizeHeight;

	int _x = 1395;
	int _y = 820;				//캐릭터 x, y
	RECT _rc;				//캐릭터 RECT

	float _playerX[RECTCOLLISION_END] = { 840, 10, 10, 10, 10, 10 };
	float _playerY[RECTCOLLISION_END] = { 519, 10, 10, 10, 10, 10 };

	//_playerX[STAGE_NYMPH_1], _playerY[STAGE_NYMPH_1]

	int _probeTop;
	int _probeBottom;
	int _probeLeft;
	int _probeRight;

	bool _isEvent;

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

