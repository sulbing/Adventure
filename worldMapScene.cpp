#include "stdafx.h"
#include "worldMapScene.h"


worldMapScene::worldMapScene() {}
worldMapScene::~worldMapScene() {}


HRESULT worldMapScene::init(void)
{
	//페이드 인/아웃
	_sceneEffect = new sceneEffect;
	_sceneEffect->init();

	_background = IMAGEMANAGER->findImage("WORLDMAP");
	_mapSizeWidth = _background->getWidth();
	_mapSizeHeight = _background->getHeight();

	//집 앞 좌표
	_x = 1395;
	_y = 820;

	_rc = RectMake(_x, _y, 30, 30);

	_eventRC[STAGE_NYMPH_1] = RectMake(771, 292, 40, 25);
	_eventRC[STAGE_NYMPH_2] = RectMake(1988, 868, 40 ,25);
	_eventRC[STAGE_HOUSE] = RectMake(1385, 717, 60, 100);
	_eventRC[STAGE_1_IN] = RectMake(841, 481, 30, 30);
	_eventRC[STAGE_1_OUT] = RectMake(809, 352, 30, 30);
	_eventRC[STAGE_2_IN] = RectMake(2126, 1694, 30, 30);
	_eventRC[STAGE_2_OUT] = RectMake(2204, 1542, 30, 30);
	_eventRC[STAGE_3_IN] = RectMake(2215, 768, 30, 30);
	_eventRC[STAGE_3_OUT] = RectMake(2184, 608, 30, 30);
	_eventRC[STAGE_CHEST] = RectMake(1067, 323, 50, 50);
	_eventRC[STAGE_MIDBOSS] = RectMake(2286, 1418, 30, 30);
	_eventRC[JAKE_BRIDGE_IN] = RectMake(1801, 1492, 30, 30);
	_eventRC[JAKE_BRIDGE_OUT] = RectMake(1801, 1582, 30, 30);
	_eventRC[JAKE_CLIMB_1] = RectMake(2226, 483, 80, 20);
	_eventRC[JAKE_CLIMB_2] = RectMake(2361, 291, 60, 20);

	_isEvent = false;
	
	return S_OK;
}

void worldMapScene::release(void)
{

}

void worldMapScene::update(void)
{
	_sceneEffect->update();

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _x -= 3;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _x += 3;
	if (KEYMANAGER->isStayKeyDown(VK_UP)) _y -= 3;
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) _y += 3;

	//if (!_sceneEffect->isFadeIN() && KEYMANAGER->isOnceKeyDown(VK_RETURN))
	//{
	//	_sceneEffect->setFadeOUT(true);
	//}
	////씬 전환 끝나면 씬 체인지
	//if (!_sceneEffect->getChangeScene() && !_sceneEffect->isFadeOUT())
	//{
	//	SCENEMANAGER->changeScene("SCENE_SAVE_POINT");
	//}

	_rc = RectMake(_x, _y, 30, 30);

	pixelCollision();
	rectCollision();
}

void worldMapScene::render(void)
{	
	int x, y;
	DIRECTION direction;
	RECT rcSour[4];
	//LEFT_TOP, MIDDLE_TOP
	//LEFT_MIDDLE, MIDDLE_MIDDLE

	x = _x - (WINSIZEX / 2);
	y = _y - (WINSIZEY / 2);

	//루프렌더처럼 나머지 연산으로 보정
	x = x % _mapSizeWidth;
	y = y % _mapSizeHeight;

	//이미지가 화면사이즈밖으로 나갔을떄 보정
	if (x <= -WINSIZEX) x += _mapSizeWidth;
	if (y <= -WINSIZEY) y += _mapSizeHeight;

	direction = getDirection(x, y);

	if (direction == DIRECTION_RIGHT_MIDDLE)
	{
		x -= _mapSizeWidth;
		direction = DIRECTION_LEFT_MIDDLE;
	}

	if (direction == DIRECTION_MIDDLE_BOTTOM)
	{
		y -= _mapSizeHeight;
		direction = DIRECTION_MIDDLE_TOP;
	}

	if (direction == DIRECTION_RIGHT_TOP)
	{
		x -= _mapSizeWidth;
		direction = DIRECTION_LEFT_TOP;
	}

	if (direction == DIRECTION_LEFT_BOTTOM)
	{
		y -= _mapSizeHeight;
		direction = DIRECTION_LEFT_TOP;
	}

	if (direction == DIRECTION_RIGHT_BOTTOM)
	{
		x -= _mapSizeWidth;
		y -= _mapSizeHeight;

		direction = DIRECTION_LEFT_TOP;
	}

	switch (direction)
	{
	case DIRECTION_LEFT_TOP:
		rcSour[0] = RectMake(_mapSizeWidth + x, _mapSizeHeight + y, _mapSizeWidth, _mapSizeHeight);
		rcSour[1] = RectMake(0, _mapSizeHeight + y, WINSIZEX + x, _mapSizeHeight);
		rcSour[2] = RectMake(_mapSizeWidth + x, 0, _mapSizeWidth, WINSIZEY + y);
		rcSour[3] = RectMake(0, 0, WINSIZEX + x, WINSIZEY + y);

		_background->render(getMemDC(), 0, 0, rcSour[0].left, rcSour[0].top,
			rcSour[0].right - rcSour[0].left,
			rcSour[0].bottom - rcSour[0].top);

		_background->render(getMemDC(), -x, 0, rcSour[1].left, rcSour[1].top,
			rcSour[1].right - rcSour[1].left,
			rcSour[1].bottom - rcSour[1].top);

		_background->render(getMemDC(), 0, -y, rcSour[2].left, rcSour[2].top,
			rcSour[2].right - rcSour[2].left,
			rcSour[2].bottom - rcSour[2].top);

		_background->render(getMemDC(), -x, -y, rcSour[3].left, rcSour[3].top,
			rcSour[3].right - rcSour[3].left,
			rcSour[3].bottom - rcSour[3].top);


		break;

	case DIRECTION_MIDDLE_TOP:
		rcSour[0] = RectMake(x, _mapSizeHeight + y, x + WINSIZEX, _mapSizeHeight);
		rcSour[1] = RectMake(x, 0, WINSIZEX + x, WINSIZEY + y);


		_background->render(getMemDC(), 0, 0, rcSour[0].left, rcSour[0].top,
			rcSour[0].right - rcSour[0].left,
			rcSour[0].bottom - rcSour[0].top);

		_background->render(getMemDC(), 0, -y, rcSour[1].left, rcSour[1].top,
			rcSour[1].right - rcSour[1].left,
			rcSour[1].bottom - rcSour[1].top);

		break;

	case DIRECTION_LEFT_MIDDLE:
		rcSour[0] = RectMake(_mapSizeWidth + x, y, _mapSizeWidth, _mapSizeHeight + y);
		rcSour[1] = RectMake(0, y, WINSIZEX + x, WINSIZEY + y);

		_background->render(getMemDC(), 0, 0, rcSour[0].left, rcSour[0].top,
			rcSour[0].right - rcSour[0].left,
			rcSour[0].bottom - rcSour[0].top);

		_background->render(getMemDC(), -x, 0, rcSour[1].left, rcSour[1].top,
			rcSour[1].right - rcSour[1].left,
			rcSour[1].bottom - rcSour[1].top);
		break;

	case DIRECTION_MIDDLE_MIDDLE:
		rcSour[0] = RectMake(x, y, x + WINSIZEX, y + WINSIZEY);

		_background->render(getMemDC(), 0, 0, rcSour[0].left, rcSour[0].top,
			rcSour[0].right - rcSour[0].left,
			rcSour[0].bottom - rcSour[0].top);
	
		break;
	}

	IMAGEMANAGER->findImage("WORLDMAP_PIXEL_COLLISION")->render(getMemDC(), 0, 0);

	RectangleMake(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, 30, 30);
	
	Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);

	_sceneEffect->render();

}

DIRECTION worldMapScene::getDirection(int x, int y)
{
	int direction = 0;

	if (0 < x && x + WINSIZEX <= _mapSizeWidth)
	{
		//DIRECTION_MIDDLE_TOP
		direction++;
	}
	if (x + WINSIZEX >= _mapSizeWidth)
	{
		//DIRECTION_RIGHT_TOP
		direction += 2;
	}
	if (0 < y && y + WINSIZEY <= _mapSizeHeight)
	{
		//DIRECTION_LEFT_MIDDLE
		direction += 3;
	}
	if (y + WINSIZEY >= _mapSizeHeight)
	{
		//DIRECTION_LEFT_BOTTOM
		direction += 6;
	}

	return (DIRECTION)direction;
}

void worldMapScene::pixelCollision()
{
	_probeTop = _rc.top;
	_probeBottom = _rc.bottom;
	_probeLeft = _rc.left;
	_probeRight = _rc.right;


	//TOP
	for (int i = _probeTop; i > _probeTop - 5; --i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("WORLDMAP_PIXEL_COLLISION")->getMemDC(), _x + ((_rc.right - _rc.left) / 2), i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 0 && b == 255))
		{
			_y = i + 3;
			break;
		}
	}


	//BOTTOM
	for (int i = _probeBottom; i < _probeBottom + 5; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("WORLDMAP_PIXEL_COLLISION")->getMemDC(), _x + ((_rc.right - _rc.left) / 2), i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 0 && b == 255))
		{
			_y = i - (_rc.bottom - _rc.top) - 3;
			break;
		}
	}

	//LEFT
	for (int i = _probeLeft; i > _probeLeft - 5; --i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("WORLDMAP_PIXEL_COLLISION")->getMemDC(), i, _y + ((_rc.bottom - _rc.top) / 2));

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 0 && b == 255))
		{
			_x = i + 3;
			break;
		}
	}

	//RIGHT
	for (int i = _probeRight; i < _probeRight + 5; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("WORLDMAP_PIXEL_COLLISION")->getMemDC(), i, _y + ((_rc.bottom - _rc.top) / 2));

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 0 && b == 255))
		{
			_x = i - (_rc.right - _rc.left) - 3;
			break;
		}
	}

}


void worldMapScene::rectCollision()
{
	for (int i = 0; i < RECTCOLLISION_END; i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_rc, &(_eventRC[i])))
		{
			_isEvent = true;

			switch (i)
			{
			case STAGE_NYMPH_1:	case STAGE_NYMPH_2:	case STAGE_HOUSE:
			{
				if (!_sceneEffect->isFadeIN() && KEYMANAGER->isOnceKeyDown(VK_RETURN))
				{
					_sceneEffect->setFadeOUT(true);
					_isEvent = false;
				}
				//씬 전환 끝나면 씬 체인지
				if (!_sceneEffect->getChangeScene() && !_sceneEffect->isFadeOUT())
				{
					SCENEMANAGER->changeScene("SCENE_SAVE_POINT");
				}

			}
				break;
			case STAGE_1_IN:
				break;
			case STAGE_1_OUT:
				break;
			case STAGE_2_IN:
				break;
			case STAGE_2_OUT:
				break;
			case STAGE_3_IN:
				break;
			case STAGE_3_OUT:
				break;
			case STAGE_CHEST:
				break;
			case STAGE_MIDBOSS:
				break;
			case JAKE_BRIDGE_IN:
				break;
			case JAKE_BRIDGE_OUT:
				break;
			case JAKE_CLIMB_1:
				break;
			case JAKE_CLIMB_2:
				break;
			case RECTCOLLISION_END:
				break;
			default:
				break;
			}
		}
	}
}
