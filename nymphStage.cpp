#include "stdafx.h"
#include "nymphStage.h"


HRESULT nymphStage::init(void)
{
	IMAGEMANAGER->addImage("savePointCollision", "Image/NYMPH_PIXEL_COLLISION.bmp", 860, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("savePoint", "Image/WATTERNYMPH_BACKGROUND.bmp", 860, 480, true, RGB(255, 0, 255));
	_nymph = IMAGEMANAGER->addFrameImage("nymph", "Image/WATTERNYMPH.bmp", 1752, 148, 6, 1, true, RGB(255, 0, 255));


	_nymphAni = new animation;
	_nymphAni->init(_nymph->getWidth(), _nymph->getHeight(), _nymph->getFrameWidth(), _nymph->getFrameHeight());
	_nymphAni->setPlayFrame(0, 5, false, true);
	_nymphAni->setFPS(2);
	_nymphAni->start();

	return S_OK;
}

void nymphStage::release(void)
{
}

void nymphStage::update(void)
{

	_nymphAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
}

void nymphStage::render(void)
{
	IMAGEMANAGER->findImage("savePoint")->render(getMemDC(), 0, 0, 0, 0, WINSIZEX, WINSIZEY);
	_nymph->aniRender(getMemDC(), 400, WINSIZEY - 208, _nymphAni);

}

nymphStage::nymphStage()
{
}


nymphStage::~nymphStage()
{
}
