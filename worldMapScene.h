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

	int _x,  _y;			//캐릭터 x, y
	RECT _rc;				//캐릭터 RECT

	//	STAGE_NYMPH_1,		  //왼쪽 연못
	//	STAGE_NYMPH_2,		  //오른쪽 연못
	//	STAGE_HOUSE,		  //집 앞
	//	STAGE_1_LEFT,		  //왼쪽 계단 아래
	//	STAGE_1_RIGHT,		  //왼쪽 계단 위
	//	STAGE_2_LEFT,		  //오른쪽 아래 계단 아래
	//	STAGE_2_RIGHT,		  //오른쪽 아래 계단 위
	//	STAGE_3_LEFT,		  //오른쪽 위 계단 아래
	//	STAGE_3_RIGHT,		  //오른쪽 위 계단 위
	//	STAGE_CHEST,		  //왼쪽 숲
	//	STAGE_MIDBOSS,		  //오른쪽 아래 숲
	//	JAKE_BRIDGE_IN,		  //다리 위
	//	JAKE_BRIDGE_OUT,	  //다리 아래
	//	JAKE_CLIMB_1,		  //아래 올라가기
	//	JAKE_CLIMB_2,		  //위 올라가기
	//	RECTCOLLISION_END

	//									님프1	님프2	하우스	1왼		1오		2왼		2오		3왼		3오		보물		중보스	다리위	다리아래	올라가기1	올라가기2
	float _playerX[RECTCOLLISION_END] = { 844,	2009,	1417,	855,	876,	2100,	2268,	2233,	1027,	1032,	2310,	1817,	1817,	2257,	2392 };
	float _playerY[RECTCOLLISION_END] = { 304,	920,	857,	541,	367,	1709,	1558,	832,	358,	355,	1493,	1472,	1646,	518,	315 };

	//_playerX[STAGE_NYMPH_1], _playerY[STAGE_NYMPH_1]

	int _probeTop;
	int _probeBottom;
	int _probeLeft;
	int _probeRight;


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

