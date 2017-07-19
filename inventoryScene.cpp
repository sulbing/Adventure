#include "stdafx.h"
#include "inventoryScene.h"


inventoryScene::inventoryScene()
{
}


inventoryScene::~inventoryScene()
{
}


HRESULT inventoryScene::init()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			_itemSlot[i * 8 + j] = PointMake(106 + j * 64, 76 + i* 64);
		}
	}

	int size = _vItem.size();

	if (DATABASE->getaddVector().size() != 0)
	{
		for (int i = 0; i < DATABASE->getaddVector().size(); i++)
		{
			addItem((ITEMLIST)DATABASE->getaddVector()[i], _itemSlot[size + i].x, _itemSlot[size + i].y);
		}
		DATABASE->clearaddVector();
	}

	_drag = false;

	return S_OK;
}

void inventoryScene::release()	 
{

}

void inventoryScene::update()	 
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->update();
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON)) useItem();
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vItem.size(); i++)
		{
			if (PtInRect(&_vItem[i]->getRect(), _ptMouse) && !_drag)
			{
				_drag = true;
				_itemTemp = _vItem[i];
				_vItem.erase(_vItem.begin() + i);
				break;
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _drag)
	{
		_itemTemp->setCenterXY(_ptMouse.x, _ptMouse.y);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _drag)
	{
		itemMix();
		_drag = false;
	}
	
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->setXY(_itemSlot[i].x, _itemSlot[i].y);
	}
}

void inventoryScene::render()	 
{
	IMAGEMANAGER->findImage("INVENTORY")->render(getMemDC(), 0, 0);
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->render(_vItem[i]->getX(), _vItem[i]->getY());
	}

	if (_drag) _itemTemp->render(_itemTemp->getX(), _itemTemp->getY());
}

void inventoryScene::addItem(ITEMLIST itemlist, float x, float y)
{
	item* _item;
	_item = new item;
	_item->init(itemlist, x, y);
	_vItem.push_back(_item);
}

void inventoryScene::useItem(void)
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		if (PtInRect(&_vItem[i]->getRect(), _ptMouse))
		{
			DATABASE->pushbackuseVector(_vItem[i]->getNum());
			_vItem.erase(_vItem.begin() + i);
			break;
		}
	}
}

void inventoryScene::itemMix(void)
{
	RECT rcTemp;

	for (int i = 0; i < _vItem.size(); i++)
	{
		if (PtInRect(&_vItem[i]->getRect(), _ptMouse))
		{
			if (_vItem[i]->getNum() == 3 && _itemTemp->getNum() == 6) { _vItem[i]->changeItem(12); break; }
			if (_vItem[i]->getNum() == 4 && _itemTemp->getNum() == 7) { _vItem[i]->changeItem(13); break; }
			if (_vItem[i]->getNum() == 5 && _itemTemp->getNum() == 8) { _vItem[i]->changeItem(14); break; }

			if (_vItem[i]->getNum() == 3 && ((_itemTemp->getNum() == 7) || (_itemTemp->getNum() == 8))) { _vItem[i]->changeItem(9); break; }
			if (_vItem[i]->getNum() == 4 && ((_itemTemp->getNum() == 6) || (_itemTemp->getNum() == 8))) { _vItem[i]->changeItem(10); break; }
			if (_vItem[i]->getNum() == 5 && ((_itemTemp->getNum() == 6) || (_itemTemp->getNum() == 7))) { _vItem[i]->changeItem(11); break; }

			if (_vItem[i]->getNum() == 6 && _itemTemp->getNum() == 3) { _vItem[i]->changeItem(12); break; }
			if (_vItem[i]->getNum() == 7 && _itemTemp->getNum() == 4) { _vItem[i]->changeItem(13); break; }
			if (_vItem[i]->getNum() == 8 && _itemTemp->getNum() == 5) { _vItem[i]->changeItem(14); break; }

			if (_vItem[i]->getNum() == 6 && ((_itemTemp->getNum() == 4) || (_itemTemp->getNum() == 5))) { _vItem[i]->changeItem(9); break;	  }
			if (_vItem[i]->getNum() == 7 && ((_itemTemp->getNum() == 3) || (_itemTemp->getNum() == 5))) { _vItem[i]->changeItem(10); break;  }
			if (_vItem[i]->getNum() == 8 && ((_itemTemp->getNum() == 3) || (_itemTemp->getNum() == 4))) { _vItem[i]->changeItem(11); break;  }
		}
	}
}