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
	_stageFinn->init(DATABASE->getStatusHearts(), DATABASE->getStatusAttack(), DATABASE->getStatusSpeed(), DATABASE->getStatusCureentHP(), WINSIZEX / 4, WINSIZEY * 3 / 4, true);

	_stageFinn->setCamX(0);

	_sceneEffect = new sceneEffect;
	_sceneEffect->init();

	_isChange = _isSave = false;

	_nymphRC = RectMake(275, WINSIZEY - 208, _nymph->getFrameWidth() - 50, _nymph->getFrameHeight());

	SOUNDMANAGER->play("스테이지", 0.3f);

<<<<<<< HEAD
=======
	_bw = new bigWorm;
	_bw->init(WINSIZEX / 2, WINSIZEY / 2 + 100, _stageFinn, 500);

>>>>>>> 578f0e346b9ccb64b86dd5ca8cd54b77e08f3e46
	return S_OK;
}

void nymphStage::release(void)
{
}

void nymphStage::update(void)
{
	_sceneEffect->update();

	_nymphAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 8);


	//핀 업데이트
	if (!_isChange) _stageFinn->update();
	pixelCollision();
	
	stageDoor();
	_UI->update();
	save();
}

void nymphStage::render(void)
{
	Rectangle(getMemDC(), _nymphRC.left, _nymphRC.top, _nymphRC.right, _nymphRC.bottom);
	IMAGEMANAGER->findImage("savePointCollision")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("savePoint")->render(getMemDC(), 0, 0, 0, 0, WINSIZEX, WINSIZEY);
	_nymph->aniRender(getMemDC(), 250, WINSIZEY - 208, _nymphAni);

	if (_isSave)
	{
		IMAGEMANAGER->findImage("X")->render(getMemDC(), _nymphRC.left + 105, _nymphRC.top - 60);
	}

	//핀 랜더
	_stageFinn->render();
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
		SOUNDMANAGER->stop("스테이지");

		_isChange = true;
		_sceneEffect->setFadeOUT(true);

		//씬 전환 끝나면 씬 체인지
		if (!_sceneEffect->getChangeScene())
		{
			SCENEMANAGER->changeScene("SCENE_WORLDMAP");
		}
	}

	else if (IntersectRect(&temp, &_rightDoor, &_stageFinn->getBodyRC()))
	{
		SOUNDMANAGER->stop("스테이지");

		_isChange = true;
		_sceneEffect->setFadeOUT(true);

		//씬 전환 끝나면 씬 체인지
		if (!_sceneEffect->getChangeScene())
		{
			SCENEMANAGER->changeScene("SCENE_WORLDMAP");
		}
	}
}


void nymphStage::save()
{
	RECT temp;

	if (IntersectRect(&temp, &_nymphRC, &_stageFinn->getBodyRC()))
	{
		_isSave = true;

		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			_stageFinn->setCurrentHP(8 + DATABASE->getStatusHearts() * 4);
			DATABASE->setStatusCurrentHP(_stageFinn->getCurrentHP());
			DATABASE->saveData();
		}
	}
	else _isSave = false;
}

nymphStage::nymphStage()
{
}


nymphStage::~nymphStage()
{
}
