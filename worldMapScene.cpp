#include "stdafx.h"
#include "worldMapScene.h"


worldMapScene::worldMapScene() {}
worldMapScene::~worldMapScene() {}


HRESULT worldMapScene::init(void)
{
	//���̵� ��/�ƿ�
	_sceneEffect = new sceneEffect;
	_sceneEffect->init();

	_background = IMAGEMANAGER->findImage("WORLDMAP");
	_mapSizeWidth = _background->getWidth();
	_mapSizeHeight = _background->getHeight();

	//�� �� ��ǥ
	_x = 1395;
	_y = 820;

	_rc = RectMake(_x, _y, 30, 30);

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

	if (!_sceneEffect->isFadeIN() && KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_sceneEffect->setFadeOUT(true);
	}
	//�� ��ȯ ������ �� ü����
	if (!_sceneEffect->getChangeScene() && !_sceneEffect->isFadeOUT())
	{
		SCENEMANAGER->changeScene("SCENE_SAVE_POINT");
	}

	_rc = RectMake(_x, _y, 30, 30);

	pixelCollision();
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

	//��������ó�� ������ �������� ����
	x = x % _mapSizeWidth;
	y = y % _mapSizeHeight;

	//�̹����� ȭ������������ �������� ����
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
	//bool isCheck = false;

	////LEFTTOP
	//if (!isCheck)
	//{
	//	for (int i = 0; i < 5; ++i)
	//	{
	//		COLORREF color = GetPixel(IMAGEMANAGER->findImage("WORLDMAP_PIXEL_COLLISION")->getMemDC(), _rc.left, _rc.top);

	//		int r = GetRValue(color);
	//		int g = GetGValue(color);
	//		int b = GetBValue(color);

	//		if ((r == 0 && g == 0 && b == 255))
	//		{
	//			isCheck = true;

	//			if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _x += 3;
	//			if (KEYMANAGER->isStayKeyDown(VK_UP)) _y += 3;

	//			break;
	//		}
	//	}
	//}

	////RIGHTTOP
	//if (!isCheck)
	//{
	//	for (int i = 0; i < 5; ++i)
	//	{
	//		COLORREF color = GetPixel(IMAGEMANAGER->findImage("WORLDMAP_PIXEL_COLLISION")->getMemDC(), _rc.right, _rc.top);

	//		int r = GetRValue(color);
	//		int g = GetGValue(color);
	//		int b = GetBValue(color);

	//		if ((r == 0 && g == 0 && b == 255))
	//		{
	//			isCheck = true;

	//			if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _x -= 3;
	//			if (KEYMANAGER->isStayKeyDown(VK_UP)) _y += 3;

	//			break;
	//		}
	//	}
	//}

	////LEFTBOTTOM
	//if (!isCheck)
	//{
	//	for (int i = 0; i < 5; ++i)
	//	{
	//		COLORREF color = GetPixel(IMAGEMANAGER->findImage("WORLDMAP_PIXEL_COLLISION")->getMemDC(), _rc.left, _rc.bottom);

	//		int r = GetRValue(color);
	//		int g = GetGValue(color);
	//		int b = GetBValue(color);

	//		if ((r == 0 && g == 0 && b == 255))
	//		{
	//			isCheck = true;

	//			if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _x += 3;
	//			if (KEYMANAGER->isStayKeyDown(VK_DOWN)) _y -= 3;

	//			break;
	//		}
	//	}
	//}

	////RIGHTBOTTOM
	//if (!isCheck)
	//{
	//	for (int i = 0; i < 5; ++i)
	//	{
	//		COLORREF color = GetPixel(IMAGEMANAGER->findImage("WORLDMAP_PIXEL_COLLISION")->getMemDC(), _rc.right, _rc.bottom);

	//		int r = GetRValue(color);
	//		int g = GetGValue(color);
	//		int b = GetBValue(color);

	//		if ((r == 0 && g == 0 && b == 255))
	//		{
	//			isCheck = true;

	//			if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _x -= 3;
	//			if (KEYMANAGER->isStayKeyDown(VK_DOWN)) _y -= 3;

	//			break;
	//		}
	//	}
	//}

	_probeTop = _rc.top;
	_probeBottom = _rc.bottom;
	_probeLeft = _rc.left;
	_probeRight = _rc.right;

	//TOP
	for (int i = _probeTop; i < _probeTop + 5; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("WORLDMAP_PIXEL_COLLISION")->getMemDC(), _x + ((_rc.right - _rc.left) / 2), i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 0 && b == 255))
		{
			_y = i;
			break;
		}
	}

	/*
	//BOTTOM
	for (int i = _probeBottom - 5; i < _probeBottom; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("WORLDMAP_PIXEL_COLLISION")->getMemDC(), _x + ((_rc.right - _rc.left) / 2), i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 0 && b == 255))
		{
			_y = i - ((_rc.bottom - _rc.top) / 2);
			break;
		}
	}

	//LEFT
	for (int i = _probeLeft; i < _probeLeft + 5; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("WORLDMAP_PIXEL_COLLISION")->getMemDC(), i, _y + ((_rc.bottom - _rc.top) / 2));

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 0 && b == 255))
		{
			_x = i;
			break;
		}
	}

	//RIGHT
	for (int i = _probeRight - 5; i < _probeRight; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("WORLDMAP_PIXEL_COLLISION")->getMemDC(), i, _y + ((_rc.bottom - _rc.top) / 2));

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 0 && b == 255))
		{
			_x = i - ((_rc.right - _rc.left) / 2);
			break;
		}
	}
	*/

}