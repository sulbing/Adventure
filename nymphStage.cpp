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


	return S_OK;
}

void nymphStage::release(void)
{
}

void nymphStage::update(void)
{

	_nymphAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 8);

	//ÇÉ ¾÷µ¥ÀÌÆ®
	_stageFinn->update();
	pixelCollision();


}

void nymphStage::render(void)
{
	IMAGEMANAGER->findImage("savePointCollision")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("savePoint")->render(getMemDC(), 0, 0, 0, 0, WINSIZEX, WINSIZEY);
	_nymph->aniRender(getMemDC(), 400, WINSIZEY - 208, _nymphAni);


	//ÇÉ ·£´õ
	_stageFinn->render();
}

void nymphStage::pixelCollision(void)
{
	if (_stageFinn->getState() == JUMP)
	{
		for (int i = _stageFinn->getY() + _stageFinn->getHeight() / 2 - 20 / 2; i < _stageFinn->getY() + _stageFinn->getHeight(); ++i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("savePointCollision")->getMemDC(), _stageFinn->getX(), i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 0 && g == 0 && b == 255))
			{
				_stageFinn->setY(i - _stageFinn->getHeight() / 2);
				//{ i - _stageFinn->getHeight() / 2; } = i - _stageFinn->getHeight() / 2;
				_stageFinn->setSpeedY(0);
				_stageFinn->setState(IDLE);
				break;
			}
		}
		
	}
}

nymphStage::nymphStage()
{
}


nymphStage::~nymphStage()
{
}
