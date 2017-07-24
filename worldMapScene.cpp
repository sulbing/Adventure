#include "stdafx.h"
#include "worldMapScene.h"


worldMapScene::worldMapScene() {}
worldMapScene::~worldMapScene() {}


HRESULT worldMapScene::init(void)
{
	_worldPlayer = new worldPlayer;
	_worldPlayer->init();
	
	_UI = new UI;
	_UI->init();

	//페이드 인/아웃
	_sceneEffect = new sceneEffect;
	_sceneEffect->init();

	_background = IMAGEMANAGER->findImage("WORLDMAP");
	_mapSizeWidth = _background->getWidth();
	_mapSizeHeight = _background->getHeight();

	//집 앞 좌표
	_worldPlayer->setWorldFinnX(_playerX[DATABASE->getWorldPosition()]);
	_worldPlayer->setWorldFinnY(_playerY[DATABASE->getWorldPosition()]);

	_rc = _worldPlayer->getWorldFinnRect();

	_eventRC[STAGE_NYMPH_1] = RectMake(871, 392, 40, 25);
	_eventRC[STAGE_NYMPH_2] = RectMake(2088, 968, 40 ,25);
	_eventRC[STAGE_HOUSE] = RectMake(1485, 817, 60, 100);
	_eventRC[STAGE_1_LEFT] = RectMake(941, 581, 30, 30);
	_eventRC[STAGE_1_RIGHT] = RectMake(909, 452, 30, 30);
	_eventRC[STAGE_2_LEFT] = RectMake(2226, 1794, 30, 30);
	_eventRC[STAGE_2_RIGHT] = RectMake(2304, 1642, 30, 30);
	_eventRC[STAGE_3_LEFT] = RectMake(2315, 868, 30, 30);
	_eventRC[STAGE_3_RIGHT] = RectMake(2284, 708, 30, 30);
	_eventRC[STAGE_CHEST] = RectMake(1167, 423, 50, 50);
	_eventRC[STAGE_MIDBOSS] = RectMake(2386, 1518, 30, 30);
	_eventRC[JAKE_BRIDGE_IN] = RectMake(1901, 1592, 30, 20);
	_eventRC[JAKE_BRIDGE_OUT] = RectMake(1901, 1675, 30, 20);
	_eventRC[JAKE_CLIMB_1] = RectMake(2326, 583, 80, 20);
	_eventRC[JAKE_CLIMB_2] = RectMake(2461, 391, 60, 20);

	_isChange = false;

	SOUNDMANAGER->play("월드", 0.3f);
	
	return S_OK;
}

void worldMapScene::release(void)
{

}

void worldMapScene::update(void)
{
	_sceneEffect->update();
	if (!_isChange) _worldPlayer->update();

	_x = _worldPlayer->getWorldFinnX();
	_y = _worldPlayer->getWorldFinnY();

	_rc = _worldPlayer->getWorldFinnRect();

	if (!_worldPlayer->getIsBridgeState() && !_worldPlayer->getIsLongLegState())
	{
		pixelCollision();
		rectCollision();
	}

	_UI->update();
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

	//IMAGEMANAGER->findImage("WORLDMAP_PIXEL_COLLISION")->render(getMemDC(), 0, 0);

	//RectangleMakeCenter(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, 30, 30);
	
	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);

	_worldPlayer->render();

	_UI->render();

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
			_worldPlayer->setWorldFinnY((i + 3) + (_rc.bottom - _rc.top) / 2);
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
			_worldPlayer->setWorldFinnY(i - 3 - (_rc.bottom - _rc.top) / 2);
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
			_worldPlayer->setWorldFinnX(i + 3 + (_rc.right - _rc.left) / 2);
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
			_worldPlayer->setWorldFinnX(i - 3 - (_rc.right - _rc.left) / 2);
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
			switch (i)
			{
			case STAGE_NYMPH_1:	case STAGE_NYMPH_2:	case STAGE_HOUSE:
			{
				SOUNDMANAGER->stop("월드");
				_isChange = true;
				_sceneEffect->setFadeOUT(true);

				//씬 전환 끝나면 씬 체인지
				if (!_sceneEffect->getChangeScene())
				{
					if (i == STAGE_NYMPH_1) DATABASE->setWorldPosition(STAGE_NYMPH_1);
					if (i == STAGE_NYMPH_2) DATABASE->setWorldPosition(STAGE_NYMPH_2);
					if (i == STAGE_HOUSE) DATABASE->setWorldPosition(STAGE_HOUSE);

					SCENEMANAGER->changeScene("SCENE_SAVE_POINT");
				}
			}
				break;
			case STAGE_1_LEFT:
			{
				SOUNDMANAGER->stop("월드");
				_isChange = true;

				_sceneEffect->setFadeOUT(true);
				DATABASE->setWorldPosition(STAGE_1_LEFT);
				//씬 전환 끝나면 씬 체인지
				if (!_sceneEffect->getChangeScene())
				{
					SCENEMANAGER->changeScene("STAGE1");
				}
			}
				break;
			case STAGE_1_RIGHT:
			{
				SOUNDMANAGER->stop("월드");
				_isChange = true;

				_sceneEffect->setFadeOUT(true);
				DATABASE->setWorldPosition(STAGE_1_RIGHT);
				//씬 전환 끝나면 씬 체인지
				if (!_sceneEffect->getChangeScene())
				{
					SCENEMANAGER->changeScene("STAGE1");
				}
			}
				break;
			case STAGE_2_LEFT:
			{
				SOUNDMANAGER->stop("월드");
				_isChange = true;

				_sceneEffect->setFadeOUT(true);
				DATABASE->setWorldPosition(STAGE_2_LEFT);
				//씬 전환 끝나면 씬 체인지
				if (!_sceneEffect->getChangeScene())
				{
					SCENEMANAGER->changeScene("STAGE2");
				}
			}
				break;
			case STAGE_2_RIGHT:
			{
				SOUNDMANAGER->stop("월드");
				_isChange = true;

				_sceneEffect->setFadeOUT(true);
				DATABASE->setWorldPosition(STAGE_2_RIGHT);
				//씬 전환 끝나면 씬 체인지
				if (!_sceneEffect->getChangeScene())
				{
					SCENEMANAGER->changeScene("STAGE2");
				}
			}
				break;
			case STAGE_3_LEFT:
			{
				{
					SOUNDMANAGER->stop("월드");
					_isChange = true;

					_sceneEffect->setFadeOUT(true);
					DATABASE->setWorldPosition(STAGE_3_LEFT);
					//씬 전환 끝나면 씬 체인지
					if (!_sceneEffect->getChangeScene())
					{
						SCENEMANAGER->changeScene("STAGE3");
					}
				}
			}
				break;
			case STAGE_3_RIGHT:
			{
				{
					SOUNDMANAGER->stop("월드");
					_isChange = true;

					_sceneEffect->setFadeOUT(true);
					DATABASE->setWorldPosition(STAGE_3_RIGHT);
					//씬 전환 끝나면 씬 체인지
					if (!_sceneEffect->getChangeScene())
					{
						SCENEMANAGER->changeScene("STAGE3");
					}
				}
			}
				break;
			case STAGE_CHEST:
			{
				{
					SOUNDMANAGER->stop("월드");
					_isChange = true;

					_sceneEffect->setFadeOUT(true);
					DATABASE->setWorldPosition(STAGE_CHEST);
					//씬 전환 끝나면 씬 체인지
					if (!_sceneEffect->getChangeScene())
					{
						SCENEMANAGER->changeScene("CHEST_STAGE");
					}
				}
			}
				break;
			case STAGE_MIDBOSS:
				break;
			case JAKE_BRIDGE_IN:
			{
				if (!_worldPlayer->getIsBridgeState())
				{
					_worldPlayer->setBridge(_eventRC[JAKE_BRIDGE_IN].left + 15, _eventRC[JAKE_BRIDGE_IN].bottom, _eventRC[JAKE_BRIDGE_OUT].left + 15, _eventRC[JAKE_BRIDGE_OUT].top);
				}
			}
				break;
			case JAKE_BRIDGE_OUT:
			{
				if (!_worldPlayer->getIsBridgeState())
				{
					_worldPlayer->setBridge(_eventRC[JAKE_BRIDGE_OUT].left + 15, _eventRC[JAKE_BRIDGE_OUT].top, _eventRC[JAKE_BRIDGE_IN].left + 15, _eventRC[JAKE_BRIDGE_IN].bottom);
				}
			}
				break;
			case JAKE_CLIMB_1:
			{
				if (!_worldPlayer->getIsLongLegState())
				{
					_worldPlayer->setLongLeg(_eventRC[JAKE_CLIMB_1].left + 45, _eventRC[JAKE_CLIMB_1].top, _eventRC[JAKE_CLIMB_1].left + 45, _eventRC[JAKE_CLIMB_1].top - 100);
				}
			}
				break;
			case JAKE_CLIMB_2:
			{
				if (!_worldPlayer->getIsLongLegState())
				{
					_worldPlayer->setLongLeg(_eventRC[JAKE_CLIMB_2].left + 40, _eventRC[JAKE_CLIMB_2].top, _eventRC[JAKE_CLIMB_2].left + 40, _eventRC[JAKE_CLIMB_2].top - 100);
				}
			}
				break;
			case RECTCOLLISION_END:
				break;
			default:
				break;
			}
		}
	}
}
