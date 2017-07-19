#include "stdafx.h"
#include "worldMapScene.h"


worldMapScene::worldMapScene() {}
worldMapScene::~worldMapScene() {}


HRESULT worldMapScene::init(void)
{

	_background = IMAGEMANAGER->findImage("WORLDMAP");
	_mapSizeWidth = _background->getWidth();
	_mapSizeHeight = _background->getHeight();

	//집 앞 좌표
	_x = 1395;
	_y = 820;

	return S_OK;
}

void worldMapScene::release(void)
{

}

void worldMapScene::update(void)
{

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _x -= 3;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _x += 3;
	if (KEYMANAGER->isStayKeyDown(VK_UP)) _y -= 3;
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) _y += 3;

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SCENEMANAGER->changeScene("SCENE_SAVE_POINT");
	}
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

	RectangleMake(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, 50, 50);
	RectangleMake(getMemDC(), _x, _y, 20, 50);

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

}