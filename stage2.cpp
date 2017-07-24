#include "stdafx.h"
#include "stage2.h"


HRESULT stage2::init(void)
{
	_UI = new UI;
	_UI->init();

	_leftDoor = RectMake(0, WINSIZEY / 2, 10, 400);
	_rightDoor = RectMake(6640, WINSIZEY / 2, 10, 400);

	_sceneEffect = new sceneEffect;
	_sceneEffect->init();


	_stageFinn = new stagePlayer;
	if (DATABASE->getWorldPosition() == STAGE_2_LEFT)
	{
		_stageFinn->init(DATABASE->getStatusHearts(), DATABASE->getStatusAttack(), DATABASE->getStatusSpeed(), DATABASE->getStatusCureentHP(), WINSIZEX / 4, WINSIZEY - 100, true);

		_camX = 0;
	}
	else if (DATABASE->getWorldPosition() == STAGE_2_RIGHT)
	{
		_stageFinn->init(DATABASE->getStatusHearts(), DATABASE->getStatusAttack(), DATABASE->getStatusSpeed(), DATABASE->getStatusCureentHP(), 6600, WINSIZEY / 2 + 50, false);

		_camX = 6650 - WINSIZEX;
		_stageFinn->setCamX(_camX);
	}

	_camY = 0;

	_isChange = false;
	
	return S_OK;
}

void stage2::release(void)
{
}

void stage2::update(void)
{
	_sceneEffect->update();

	for (_vistageItem = _vstageItem.begin(); _vistageItem != _vstageItem.end(); ++_vistageItem)
	{
		(*_vistageItem)->update();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		setItem();
	}

	eatItem();

	//ÇÉ ¾÷µ¥ÀÌÆ®
	if (!_isChange)
	{
		_stageFinn->update();
	}
	pixelCollision();
	stageDoor();
	camMove();
	_UI->update();
}

void stage2::render(void)
{
	IMAGEMANAGER->findImage("STAGE2_PIXEL_COLLISION")->render(getMemDC(), 0, 0, _camX, _camY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("STAGE_BACKGROUND")->render(getMemDC(), 0, 0, _camX / 10, _camY / 10, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("STAGE2")->render(getMemDC(), 0, 0, _camX, _camY, WINSIZEX, WINSIZEY);

	for (_vistageItem = _vstageItem.begin(); _vistageItem != _vstageItem.end(); ++_vistageItem)
	{
		(*_vistageItem)->render(_camX, true);
	}

	//ÇÉ ·£´õ
	_stageFinn->render();

	_UI->render();
	_sceneEffect->render();
}

void stage2::pixelCollision(void)
{
	//º®¿¡ ºÎµúÈ÷¸é ¸ØÃã
	if (_stageFinn->getIsRight() == true)
	{
		for (int i = _stageFinn->getX() + _stageFinn->getWidth() / 2 - 10; i < _stageFinn->getX() + _stageFinn->getWidth() / 2; ++i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("STAGE2_PIXEL_COLLISION")->getMemDC(), i, _stageFinn->getY() + _stageFinn->getHeight() / 2 - 15);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 0 && g == 0 && b == 255))
			{
				_stageFinn->setX(i - _stageFinn->getWidth() / 2);
				_stageFinn->setSpeedX(0);
				break;
			}
		}
	}

	else if (_stageFinn->getIsRight() == false)
	{
		for (int i = _stageFinn->getX() - _stageFinn->getWidth() / 2 + 10; i > _stageFinn->getX() - _stageFinn->getWidth() / 2; --i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("STAGE2_PIXEL_COLLISION")->getMemDC(), i, _stageFinn->getY() + _stageFinn->getHeight() / 2 - 15);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 0 && g == 0 && b == 255))
			{
				_stageFinn->setX(i + _stageFinn->getWidth() / 2);
				_stageFinn->setSpeedX(0);
				break;
			}
		}
	}

	//¹Ù´Ú¿¡ ÂøÁö
	if (_stageFinn->getState() == JUMP || _stageFinn->getState() == HIT || _stageFinn->getState() == JUMPATTACK || _stageFinn->getState() == DEAD)
	{
		if (_stageFinn->getSpeedY() >= 0)
		{
			for (int i = _stageFinn->getY() + _stageFinn->getHeight() / 2 - 10; i < _stageFinn->getY() + _stageFinn->getHeight() / 2; ++i)
			{
				COLORREF color = GetPixel(IMAGEMANAGER->findImage("STAGE2_PIXEL_COLLISION")->getMemDC(), _stageFinn->getX(), i);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				if ((r == 0 && g == 0 && b == 255) || (r == 255 && g == 0 && b == 0))
				{
					_stageFinn->setY(i - _stageFinn->getHeight() / 2);
					if (_stageFinn->getState() != DEAD)
					{
						if (KEYMANAGER->isStayKeyDown(VK_RIGHT) || KEYMANAGER->isStayKeyDown(VK_LEFT)) _stageFinn->setState(WALK);
						else _stageFinn->setState(IDLE);
					}
					break;
				}

			}

			COLORREF color = GetPixel(IMAGEMANAGER->findImage("STAGE1_PIXEL_COLLISION")->getMemDC(), _stageFinn->getX(), _stageFinn->getY() - 50);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 0 && g == 255 && b == 0))
			{
				_stageFinn->init(2, 0, 0, 8, WINSIZEX / 4, WINSIZEY - 100, true);
			}
		}
	}

	//¾ÉÀ¸¸é »¡°£ºÎºÐ Åë°ú
	else if (_stageFinn->getState() == CROUCH)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("STAGE2_PIXEL_COLLISION")->getMemDC(), _stageFinn->getX(), _stageFinn->getY() + _stageFinn->getHeight() / 2);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_stageFinn->setY(_stageFinn->getY() + 17);
			_stageFinn->setState(JUMP);
		}
	}

	//Ãß¶ô
	else if (_stageFinn->getState() == WALK || _stageFinn->getState() == IDLE || _stageFinn->getState() == TACKLE)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("STAGE2_PIXEL_COLLISION")->getMemDC(), _stageFinn->getX(), _stageFinn->getY() + _stageFinn->getHeight() / 2);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 0 && g == 0 && b == 255) && !(r == 255 && g == 0 && b == 0))
		{
			_stageFinn->setState(JUMP);
		}
	}


	//¶³¾îÁö±â
	if (_stageFinn->getState() == JUMP || _stageFinn->getState() == HIT || _stageFinn->getState() == JUMPATTACK || _stageFinn->getState() == DEAD)
	{
		if (_stageFinn->getSpeedY() >= 0)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("STAGE2_PIXEL_COLLISION")->getMemDC(), _stageFinn->getX(), _stageFinn->getY());

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 255 && b == 0))
			{
				_stageFinn->setCurrentHP(_stageFinn->getCurrentHP() - 1);
				if (DATABASE->getWorldPosition() == STAGE_2_LEFT)
				{
					_stageFinn->init(_stageFinn->getStatus_hearts(), _stageFinn->getStatus_attack(), _stageFinn->getStatus_speed(), _stageFinn->getCurrentHP(), WINSIZEX / 4, WINSIZEY - 100, true);

					_camX = 0;
				}
				else if (DATABASE->getWorldPosition() == STAGE_2_RIGHT)
				{
					_stageFinn->init(_stageFinn->getStatus_hearts(), _stageFinn->getStatus_attack(), _stageFinn->getStatus_speed(), _stageFinn->getCurrentHP(), 6630, WINSIZEY - 100, false);
					_camX = 6650 - WINSIZEX;
					_stageFinn->setCamX(_camX);
				}
			}
		}
	}
}

void stage2::stageDoor(void)
{
	RECT temp;

	if (IntersectRect(&temp, &_leftDoor, &_stageFinn->getBodyRC()))
	{
		_isChange = true;
		_sceneEffect->setFadeOUT(true);

		//¾À ÀüÈ¯ ³¡³ª¸é ¾À Ã¼ÀÎÁö
		if (!_sceneEffect->getChangeScene())
		{
			_vstageItem.clear();
			DATABASE->setWorldPosition(STAGE_2_LEFT);
			DATABASE->setstatus(_stageFinn->getStatus_hearts(), _stageFinn->getStatus_attack(), _stageFinn->getStatus_speed(), DATABASE->getStatusBonus(), _stageFinn->getCurrentHP());
			SCENEMANAGER->changeScene("SCENE_WORLDMAP");
		}
	}

	else if (IntersectRect(&temp, &_rightDoor, &_stageFinn->getBodyRC()))
	{
		_isChange = true;
		_sceneEffect->setFadeOUT(true);

		//¾À ÀüÈ¯ ³¡³ª¸é ¾À Ã¼ÀÎÁö
		if (!_sceneEffect->getChangeScene())
		{
			_vstageItem.clear();
			DATABASE->setWorldPosition(STAGE_2_RIGHT);
			DATABASE->setstatus(_stageFinn->getStatus_hearts(), _stageFinn->getStatus_attack(), _stageFinn->getStatus_speed(), DATABASE->getStatusBonus(), _stageFinn->getCurrentHP());
			SCENEMANAGER->changeScene("SCENE_WORLDMAP");
		}
	}
}

void stage2::camMove(void)
{
	if (_stageFinn->getIsRight() == true)
	{
		if (_camX >= 0 && _camX < 6650 - WINSIZEX)
		{
			if (_stageFinn->getX() + _stageFinn->getWidth() / 2 == 6370)
			{
				_stageFinn->setSpeedX(0);
			}
			if (_camX == 6650 - WINSIZEX);
			else if (_stageFinn->getX() > WINSIZEX / 3)
			{
				if (_stageFinn->getX() - _camX > WINSIZEX / 3 + 7)
				{
					_camX += _stageFinn->getSpeedX() * 2 + 3;
				}
				else _camX = _stageFinn->getX() - WINSIZEX / 3 + 6;
				_stageFinn->setCamX(_camX);
			}
		}

		if (_camX > 6650 - WINSIZEX) _camX = 6650 - WINSIZEX;
	}

	else if (_stageFinn->getIsRight() == false)
	{
		if (_camX > 0 && _camX <= 6650 - WINSIZEX)
		{
			if (_stageFinn->getX() - _stageFinn->getWidth() / 2 == 0) _stageFinn->setSpeedX(0);
			if (_camX == 0);
			else if (_stageFinn->getX() < 6650 - WINSIZEX / 3)
			{
				if (_stageFinn->getX() - _camX < WINSIZEX / 3 * 2 - 7)
				{
					_camX += _stageFinn->getSpeedX() * 2 - 3;
				}
				else _camX = _stageFinn->getX() - WINSIZEX / 3 * 2 - 5;
				_stageFinn->setCamX(_camX);
			}
		}

		if (_camX < 0) _camX = 0;
	}
}

void stage2::setItem(void)
{
	item* stageItem;
	stageItem = new item;
	int i = RND->getFromIntTo(3, 8);
	stageItem->init((ITEMLIST)i, _stageFinn->getX() + 50, _stageFinn->getY() - 10);

	_vstageItem.push_back(stageItem);
}

void stage2::eatItem(void)
{
	RECT temp;

	for (int i = 0; i < _vstageItem.size(); i++)
	{
		if (IntersectRect(&temp, &_vstageItem[i]->getRect(),
			&_stageFinn->getBodyRC()))
		{
			DATABASE->pushbackaddVector(_vstageItem[i]->getNum());
			_vstageItem.erase(_vstageItem.begin() + i);
			break;
		}
	}
}


stage2::stage2()
{
}


stage2::~stage2()
{
}
