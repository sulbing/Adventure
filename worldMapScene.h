#pragma once
#include "gameNode.h"
#include "sceneEffect.h"
#include "UI.h"

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

	image* _background;
	int _mapSizeWidth;
	int _mapSizeHeight;

	int _x,  _y;			//ĳ���� x, y
	RECT _rc;				//ĳ���� RECT

	//	STAGE_NYMPH_1,		  //���� ����
	//	STAGE_NYMPH_2,		  //������ ����
	//	STAGE_HOUSE,		  //�� ��
	//	STAGE_1_LEFT,		  //���� ��� �Ʒ�
	//	STAGE_1_RIGHT,		  //���� ��� ��
	//	STAGE_2_LEFT,		  //������ �Ʒ� ��� �Ʒ�
	//	STAGE_2_RIGHT,		  //������ �Ʒ� ��� ��
	//	STAGE_3_LEFT,		  //������ �� ��� �Ʒ�
	//	STAGE_3_RIGHT,		  //������ �� ��� ��
	//	STAGE_CHEST,		  //���� ��
	//	STAGE_MIDBOSS,		  //������ �Ʒ� ��
	//	JAKE_BRIDGE_IN,		  //�ٸ� ��
	//	JAKE_BRIDGE_OUT,	  //�ٸ� �Ʒ�
	//	JAKE_CLIMB_1,		  //�Ʒ� �ö󰡱�
	//	JAKE_CLIMB_2,		  //�� �ö󰡱�
	//	RECTCOLLISION_END

	//									����1	����2	�Ͽ콺	1��		1��		2��		2��		3��		3��		����		�ߺ���	�ٸ���	�ٸ��Ʒ�	�ö󰡱�1	�ö󰡱�2
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

