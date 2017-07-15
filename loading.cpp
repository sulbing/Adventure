#include "stdafx.h"
#include "loading.h"

loadItem::loadItem() {}
loadItem::~loadItem() {}

HRESULT loadItem::initForImage(string keyName, int width, int height)
{
	_kind = LOAD_KIND_IMAGE_0;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char* fileName, int width, int height,
	BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_IMAGE_1;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char* fileName, float x, float y, int width, int height,
	BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_IMAGE_2;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, int width, int height,
	int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, float x, float y, int width, int height,
	int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}


loading::loading()
{
}


loading::~loading()
{

}

HRESULT loading::init()
{
	_background = IMAGEMANAGER->addImage("로딩백그라운드", "overwatchLoading.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_loadingBar = new progressBar;
	_loadingBar->init("loadingBarTop", "loadingBarBottom", WINSIZEX / 2, WINSIZEY - 20, WINSIZEX, 20);
	_loadingBar->setGauge(0, 0);

	_currentGauge = 0;

	return S_OK;
}

void loading::release()
{
	SAFE_DELETE(_loadingBar);
}

void loading::update()
{
	_loadingBar->update();
}

void loading::render()
{
	_background->render(getMemDC(), 0, 0);
	_loadingBar->render();
}


void loading::loadImage(string keyName, int width, int height)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, width, height);

	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char* fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, width, height, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char* fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, x, y, width, height, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, width, height, frameX, frameY, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, x, y, width, height, frameX, frameY, trans, transColor);

	_vLoadItem.push_back(item);
}

BOOL loading::loadingDone()
{
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE;
	}

	loadItem* item = _vLoadItem[_currentGauge];

	switch (item->getLoadingKind())
	{
	case LOAD_KIND_IMAGE_0:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
	}
	break;

	case LOAD_KIND_IMAGE_1:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height,
			img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_IMAGE_2:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height,
			img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_FRAMEIMAGE_0:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height,
			img.frameX, img.frameY, img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_FRAMEIMAGE_1:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height,
			img.frameX, img.frameY, img.trans, img.transColor);
	}
	break;

	case LOAD_KIND_SOUND:
	{
		//과제로 남겨놓겠돠!
	}
	break;
	}

	_loadingBar->setGauge(_currentGauge, _vLoadItem.size());

	_currentGauge++;

	return FALSE;
}