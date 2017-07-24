#include "stdafx.h"
#include "bossScene.h"


bossScene::bossScene()
{
}


bossScene::~bossScene()
{
}

HRESULT bossScene::init(void)
{
	_UI = new UI;
	_UI->init();

	_leftDoor = RectMake(0, WINSIZEY / 2, 10, 400);
	_rightDoor = RectMake(790, WINSIZEY / 2, 10, 400);

	_sceneEffect = new sceneEffect;
	_sceneEffect->init();

	_stageFinn = new stagePlayer;

	_stageFinn->init(DATABASE->getStatusHearts(), DATABASE->getStatusAttack(), DATABASE->getStatusSpeed(), DATABASE->getStatusCureentHP(), WINSIZEX / 4, WINSIZEY - 100, true);

	_camX = 0;
	_camY = 0;

	_stageFinn->setCamX(0);
	_isChange = false;

	_bw = new bigWorm;
	_bw->init(WINSIZEX / 2, WINSIZEY / 2 + 50, _stageFinn, 500);

	//SOUNDMANAGER->play("스테이지", 0.3f);

	return S_OK;
}

void bossScene::release(void)
{
}

void bossScene::update(void)
{
	_sceneEffect->update();

	eatItem();
	attackCollision();
	//핀 업데이트
	if (!_isChange)
	{
		_stageFinn->update();
	}
	pixelCollision();

	if (_stageFinn->getX() < 20)
	{
		_stageFinn->setX(20);
	}
	else if (_stageFinn->getX() > WINSIZEX - 20)
	{

		_stageFinn->setX(WINSIZEX - 20);
	}


	_bw->update();

	_UI->update();
}

void bossScene::render(void)
{
	IMAGEMANAGER->findImage("CHEST_STAGE_PIXEL_COLLISION")->render(getMemDC(), 0, 0, _camX, _camY, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("BOSS_STAGE")->render(getMemDC(), 0, 0, 0, 0, WINSIZEX, WINSIZEY);

	_bw->render();
	//핀 랜더
	_stageFinn->render();

	_sceneEffect->render();

	_UI->render();
	if (_bw->getHP() <= 0)
	{
		IMAGEMANAGER->findImage("ENDING")->render(getMemDC(), 0, 0, 0, 0, WINSIZEX, WINSIZEY);
	}
}

void bossScene::pixelCollision(void)
{
	if (_stageFinn->getState() == JUMP || _stageFinn->getState() == HIT || _stageFinn->getState() == JUMPATTACK)
	{
		if (_stageFinn->getSpeedY() >= 0)
		{
			for (int i = _stageFinn->getY() + _stageFinn->getHeight() / 2 - 10; i < _stageFinn->getY() + _stageFinn->getHeight() / 2; ++i)
			{
				COLORREF color = GetPixel(IMAGEMANAGER->findImage("savePointCollision")->getMemDC(), _stageFinn->getX(), i);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				if ((r == 0 && g == 0 && b == 255))
				{
					_stageFinn->setY(i - _stageFinn->getHeight() / 2);
					if (KEYMANAGER->isStayKeyDown(VK_RIGHT) || KEYMANAGER->isStayKeyDown(VK_LEFT)) _stageFinn->setState(WALK);
					else _stageFinn->setState(IDLE);
					break;
				}
			}
		}
	}

	else if (_stageFinn->getState() == WALK || _stageFinn->getState() == IDLE)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("savePointCollision")->getMemDC(), _stageFinn->getX(), _stageFinn->getY() + _stageFinn->getHeight() / 2);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 0 && g == 0 && b == 255))
		{
			_stageFinn->setState(JUMP);
		}

	}
}


void bossScene::camMove(void)
{
}

void bossScene::setItem(int x, int y)
{
}

void bossScene::eatItem(void)
{
}

void bossScene::attackCollision(void)
{
	RECT temp;

	for (int j = DEFAULT; j < SKILLEND; j++)
	{
		if (IntersectRect(&temp, &_bw->getRect(),
			&_stageFinn->getSkillHitBox(j)) && _stageFinn->getSkillIsFire(j) && _bw->getState() != BDIRECTION_HIT)
		{
			_bw->delHP(_stageFinn->getSkillDamage(j));
			_bw->setHit();
			if (_stageFinn->getState() == TACKLE)
			{
				_stageFinn->tackleKnockBack();
			}

			if (_bw->getHP() <= 0)
			{


			}

		}
	}

	if (IntersectRect(&temp, &_bw->getRect(),
		&_stageFinn->getBodyRC()) && _stageFinn->getState() != DEAD && (_stageFinn->getIsHit() == false) && _bw->getHP() > 0)
	{
		_stageFinn->setCurrentHP(_stageFinn->getCurrentHP() - 1);
		_stageFinn->setState(HIT);
	}

	for (int i = 0; i < _bw->getVector().size(); i++)
	{
		if (IntersectRect(&temp, &_bw->getVector()[i]->getRect(), &_stageFinn->getBodyRC()) &&
			_stageFinn->getState() != DEAD && _stageFinn->getIsHit() == false)
		{
			_stageFinn->setCurrentHP(_stageFinn->getCurrentHP() - 1);
			_stageFinn->setState(HIT);
			_bw->eraseBullet(i);
	
			break;
		}
	}

}

