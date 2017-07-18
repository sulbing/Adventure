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

	return S_OK;
}

void nymphStage::release(void)
{
}

void nymphStage::update(void)
{

	_nymphAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 8);


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
