#include "stdafx.h"
#include "nymphStage.h"


HRESULT nymphStage::init(void)
{
	_UI = new UI;
	_UI->init();

	_nymph = IMAGEMANAGER->findImage("nymph");

	_nymphAni = new animation;
	_nymphAni->init(_nymph->getWidth(), _nymph->getHeight(), _nymph->getFrameWidth(), _nymph->getFrameHeight());
	_nymphAni->setPlayFrame(0, 5, false, true);
	_nymphAni->setFPS(1);
	_nymphAni->start();

	_leftDoor = RectMake(0, WINSIZEY / 2, 10, 400);
	_rightDoor = RectMake(790, WINSIZEY / 2, 10, 400);

	_stageFinn = new stagePlayer;
	_stageFinn->init(2, 0, 0, 8, WINSIZEX / 4, WINSIZEY * 3 / 4, true);

	_stageFinn->setCamX(0);

	_sceneEffect = new sceneEffect;
	_sceneEffect->init();

	_isChange = false;

	_mi1 = new enemy;
	_mi1->init(2, WINSIZEX /2 , WINSIZEY * 3 / 4, _stageFinn);


	return S_OK;
}

void nymphStage::release(void)
{
}

void nymphStage::update(void)
{
	_sceneEffect->update();

	_nymphAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 8);


	//ÇÉ ¾÷µ¥ÀÌÆ®
	if (!_isChange) _stageFinn->update();
	pixelCollision();

	if (_mi1) _mi1->update();

	//¾ÀÀüÈ¯
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_sceneEffect->setFadeOUT(true);
	}
	//¾À ÀüÈ¯ ³¡³ª¸é ¾À Ã¼ÀÎÁö
	if (!_sceneEffect->getChangeScene() && !_sceneEffect->isFadeOUT())
	{
		SCENEMANAGER->changeScene("CHEST_STAGE");
	}
	attackCollision();
	stageDoor();
	_UI->update();
}

void nymphStage::render(void)
{
	IMAGEMANAGER->findImage("savePointCollision")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("savePoint")->render(getMemDC(), 0, 0, 0, 0, WINSIZEX, WINSIZEY);
	_nymph->aniRender(getMemDC(), 300, WINSIZEY - 208, _nymphAni);


	//ÇÉ ·£´õ
	_stageFinn->render();

	if (_mi1) _mi1->render();
	_UI->render();

	_sceneEffect->render();

}

void nymphStage::pixelCollision(void)
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

void nymphStage::stageDoor(void)
{

	RECT temp;

	if (IntersectRect(&temp, &_leftDoor, &_stageFinn->getBodyRC()))
	{
		_isChange = true;
		_sceneEffect->setFadeOUT(true);

		//¾À ÀüÈ¯ ³¡³ª¸é ¾À Ã¼ÀÎÁö
		if (!_sceneEffect->getChangeScene())
		{
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
			SCENEMANAGER->changeScene("SCENE_WORLDMAP");
		}
		_stageFinn->setSpeedX(0);
	}
}

void nymphStage::attackCollision(void)
{

	RECT temp;
	for (int i = DEFAULT; i < SKILLEND; i++)
	{
		
		if (IntersectRect(&temp, &_stageFinn->getSkillHitBox(i), &_mi1->getRect()))
		{
			if (_stageFinn->getX() < _mi1->getX())
			{
				_mi1->setDirection(DIRECTION_LEFT_HIT);
			}
			if (_stageFinn->getX() > _mi1->getX())
			{
				_mi1->setDirection(DIRECTION_RIGHT_HIT);
			}
		}	
	}

	if (IntersectRect(&temp, &_stageFinn->getBodyRC(), &_mi1->getRect()))
	{
		if (_stageFinn->getIsHit() == false)
		{
			_stageFinn->setState(HIT);
			_stageFinn->setCurrentHP(_stageFinn->getCurrentHP() - 1);
		}
	}

}


nymphStage::nymphStage()
{
}


nymphStage::~nymphStage()
{
}
