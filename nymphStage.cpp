#include "stdafx.h"
#include "nymphStage.h"


HRESULT nymphStage::init(void)
{
	_nymph = IMAGEMANAGER->findImage("nymph");

	_nymphAni = new animation;
	_nymphAni->init(_nymph->getWidth(), _nymph->getHeight(), _nymph->getFrameWidth(), _nymph->getFrameHeight());
	_nymphAni->setPlayFrame(0, 5, false, true);
	_nymphAni->setFPS(1);
	_nymphAni->start();


	_stageFinn = new stagePlayer;
	_stageFinn->init(2, 0, 0, 8, WINSIZEX / 4, WINSIZEY * 3 / 4, true);

	_sceneEffect = new sceneEffect;
	_sceneEffect->init();

	_mi1 = new enemy;
	_mi1->init(1, WINSIZEX / 4, WINSIZEY * 3 / 4);

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
	_stageFinn->update();
	pixelCollision();

	_mi1->update(_mi1->getType());

	//¾ÀÀüÈ¯
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_sceneEffect->setFadeOUT(true);
	}
	//¾À ÀüÈ¯ ³¡³ª¸é ¾À Ã¼ÀÎÁö
	if (!_sceneEffect->getChangeScene() && !_sceneEffect->isFadeOUT())
	{
		SCENEMANAGER->changeScene("STAGE1");
	}

}

void nymphStage::render(void)
{
	IMAGEMANAGER->findImage("savePointCollision")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("savePoint")->render(getMemDC(), 0, 0, 0, 0, WINSIZEX, WINSIZEY);
	_nymph->aniRender(getMemDC(), 400, WINSIZEY - 208, _nymphAni);


	//ÇÉ ·£´õ
	_stageFinn->render();

	_mi1->render();
}

void nymphStage::pixelCollision(void)
{
	if (_stageFinn->getState() == JUMP || _stageFinn->getState() == HIT)
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

nymphStage::nymphStage()
{
}


nymphStage::~nymphStage()
{
}
