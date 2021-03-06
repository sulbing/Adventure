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

	addEnemy();

	SOUNDMANAGER->play("��������", 0.3f);
	
	return S_OK;
}

void stage2::release(void)
{
}

void stage2::update(void)
{
	_sceneEffect->update();

	for (int i = 0; i < _vLittleWorm.size(); i++)
	{
		_vLittleWorm[i]->update();
	}

	for (_vistageItem = _vstageItem.begin(); _vistageItem != _vstageItem.end(); ++_vistageItem)
	{
		(*_vistageItem)->update();
	}

	eatItem();
	attackCollision();
	//�� ������Ʈ
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

	for (int i = 0; i < _vLittleWorm.size(); i++)
	{
		_vLittleWorm[i]->render();
	}

	//�� ����
	_stageFinn->render();

	_UI->render();
	_sceneEffect->render();
}

void stage2::pixelCollision(void)
{
	//���� �ε����� ����
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

	//�ٴڿ� ����
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

	//������ �����κ� ���
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

	//�߶�
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


	//��������
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
		SOUNDMANAGER->stop("��������");

		_isChange = true;
		_sceneEffect->setFadeOUT(true);

		//�� ��ȯ ������ �� ü����
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
		SOUNDMANAGER->stop("��������");

		_isChange = true;
		_sceneEffect->setFadeOUT(true);

		//�� ��ȯ ������ �� ü����
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

void stage2::setItem(int x, int y)
{
	item* stageItem;
	stageItem = new item;
	int i = RND->getFromIntTo(0, 8);
	stageItem->init((ITEMLIST)i, x, y);

	_vstageItem.push_back(stageItem);
}

void stage2::attackCollision(void)
{
	RECT temp;

	for (int i = 0; i < _vLittleWorm.size(); i++)
	{
		for (int j = DEFAULT; j < SKILLEND; j++)
		{
			if (IntersectRect(&temp, &_vLittleWorm[i]->getRect(),
				&_stageFinn->getSkillHitBox(j)) && _stageFinn->getSkillIsFire(j) && _vLittleWorm[i]->getState() != DIRECTION_HIT)
			{
				int k = RND->getInt(2);

				if (k) SOUNDMANAGER->play("Ÿ����1", 1.0f);
				else SOUNDMANAGER->play("Ÿ����2", 1.0f);

				_vLittleWorm[i]->delHP(_stageFinn->getSkillDamage(j));
				_vLittleWorm[i]->setHit();
				if (_stageFinn->getState() == TACKLE)
				{
					_stageFinn->tackleKnockBack();
				}

				if (_vLittleWorm[i]->getHP() <= 0)
				{
					setItem(_vLittleWorm[i]->getX(), _vLittleWorm[i]->getY() - 10);
				}

				if (_vLittleWorm[i]->getHP() <= 0)
				{
					_vLittleWorm.erase(_vLittleWorm.begin() + i);
					return;
				}

			}
		}

		if (IntersectRect(&temp, &_vLittleWorm[i]->getRect(),
			&_stageFinn->getBodyRC()) && _stageFinn->getState() != DEAD && (_stageFinn->getIsHit() == false))
		{
			SOUNDMANAGER->play("�¾�����", 1.0f);
			_stageFinn->setCurrentHP(_stageFinn->getCurrentHP() - 1);
			_stageFinn->setState(HIT);
		}
	}

	if (_stageFinn->getIsDead())
	{
		SOUNDMANAGER->stop("��������");

		_isChange = true;
		_sceneEffect->setFadeOUT(true);

		//�� ��ȯ ������ �� ü����
		if (!_sceneEffect->getChangeScene())
		{
			_vstageItem.clear();
			DATABASE->loadData();
			SCENEMANAGER->changeScene("SCENE_SAVE_POINT");
		}
		_stageFinn->setSpeedX(0);
	}
}

void stage2::addEnemy()
{
	_vLittleWorm.clear();

	littleWorm* _littleWorm;
	_littleWorm = new littleWorm;
	_littleWorm->init(794, 356 - IMAGEMANAGER->findImage("liileWorm")->getFrameHeight() / 2 + 10, _stageFinn, 250);
	_vLittleWorm.push_back(_littleWorm);

	_littleWorm = new littleWorm;
	_littleWorm->init(1918, 356 - IMAGEMANAGER->findImage("liileWorm")->getFrameHeight() / 2 + 10, _stageFinn, 230);
	_vLittleWorm.push_back(_littleWorm);

	_littleWorm = new littleWorm;
	_littleWorm->init(3150, 410 - IMAGEMANAGER->findImage("liileWorm")->getFrameHeight() / 2 + 10, _stageFinn, 250);
	_vLittleWorm.push_back(_littleWorm);

	_littleWorm = new littleWorm;
	_littleWorm->init(4172, 424 - IMAGEMANAGER->findImage("liileWorm")->getFrameHeight() / 2 + 10, _stageFinn, 300);
	_vLittleWorm.push_back(_littleWorm);

	_littleWorm = new littleWorm;
	_littleWorm->init(5640, 354 - IMAGEMANAGER->findImage("liileWorm")->getFrameHeight() / 2 + 10, _stageFinn, 250);
	_vLittleWorm.push_back(_littleWorm);
}

stage2::stage2()
{
}


stage2::~stage2()
{
}
