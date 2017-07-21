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

	_drag = false;

	_itemTemp = new item;
	_itemTemp->init(ITEMLIST_END, 0,0);

	return S_OK;
}

void inventoryScene::release()	 
{

}

void inventoryScene::update()	 
{
	if (DATABASE->getaddVector().size() != 0)
	{
		for (int i = 0; i < DATABASE->getaddVector().size(); i++)
		{
			addItem((ITEMLIST)DATABASE->getaddVector()[i], _itemSlot[_vItem.size() + i].x, _itemSlot[_vItem.size() + i].y);
		}
		DATABASE->clearaddVector();
	}

	_itemTemp->setCenterXY(_ptMouse.x, _ptMouse.y);
	_itemTemp->update();

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
				_itemTemp->changeItem((ITEMLIST)_vItem[i]->getNum());
				_vItem.erase(_vItem.begin() + i);
				break;
			}
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _drag)
	{
		itemMix();
		_itemTemp->changeItem(ITEMLIST_END);
		_drag = false;
	}
	
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->setXY(_itemSlot[i].x, _itemSlot[i].y);
	}

	loadItem();
	
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
	int count = 0;
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		count++;
		if (PtInRect(&(*_viItem)->getRect(), _ptMouse))
		{
			if ((*_viItem)->getNum() == 3 && _itemTemp->getNum() == 6) { (*_viItem)->changeItem(12); _itemTemp->changeItem(ITEMLIST_END); break; }
			else if ((*_viItem)->getNum() == 3 && _itemTemp->getNum() == 7) { (*_viItem)->changeItem(9); _itemTemp->changeItem(ITEMLIST_END); break; }
			else if ((*_viItem)->getNum() == 3 && _itemTemp->getNum() == 8) { (*_viItem)->changeItem(9); _itemTemp->changeItem(ITEMLIST_END); break; }

			else if ((*_viItem)->getNum() == 4 && _itemTemp->getNum() == 6) { (*_viItem)->changeItem(10); _itemTemp->changeItem(ITEMLIST_END); break; }
			else if ((*_viItem)->getNum() == 4 && _itemTemp->getNum() == 8) { (*_viItem)->changeItem(10); _itemTemp->changeItem(ITEMLIST_END); break; }
			else if ((*_viItem)->getNum() == 4 && _itemTemp->getNum() == 7) { (*_viItem)->changeItem(13); _itemTemp->changeItem(ITEMLIST_END); break; }

			else if ((*_viItem)->getNum() == 5 && _itemTemp->getNum() == 8) { (*_viItem)->changeItem(14); _itemTemp->changeItem(ITEMLIST_END); break; }
			else if ((*_viItem)->getNum() == 5 && _itemTemp->getNum() == 7) { (*_viItem)->changeItem(11); _itemTemp->changeItem(ITEMLIST_END); break; }
			else if ((*_viItem)->getNum() == 5 && _itemTemp->getNum() == 6) { (*_viItem)->changeItem(11); _itemTemp->changeItem(ITEMLIST_END); break; }
																										  
			else if ((*_viItem)->getNum() == 6 && _itemTemp->getNum() == 3) { (*_viItem)->changeItem(12); _itemTemp->changeItem(ITEMLIST_END); break; }
			else if ((*_viItem)->getNum() == 6 && _itemTemp->getNum() == 4) { (*_viItem)->changeItem(10); _itemTemp->changeItem(ITEMLIST_END); break; }
			else if ((*_viItem)->getNum() == 6 && _itemTemp->getNum() == 5) { (*_viItem)->changeItem(11); _itemTemp->changeItem(ITEMLIST_END); break; }

			else if ((*_viItem)->getNum() == 7 && _itemTemp->getNum() == 4) { (*_viItem)->changeItem(13); _itemTemp->changeItem(ITEMLIST_END);  break; }
			else if ((*_viItem)->getNum() == 7 && _itemTemp->getNum() == 3) { (*_viItem)->changeItem(9);  _itemTemp->changeItem(ITEMLIST_END); break; }
			else if ((*_viItem)->getNum() == 7 && _itemTemp->getNum() == 5) { (*_viItem)->changeItem(11); _itemTemp->changeItem(ITEMLIST_END);  break; }

			else if ((*_viItem)->getNum() == 8 && _itemTemp->getNum() == 5) { (*_viItem)->changeItem(14); _itemTemp->changeItem(ITEMLIST_END);  break; }
			else if ((*_viItem)->getNum() == 8 && _itemTemp->getNum() == 3) { (*_viItem)->changeItem(9);  _itemTemp->changeItem(ITEMLIST_END); break; }
			else if ((*_viItem)->getNum() == 8 && _itemTemp->getNum() == 4) { (*_viItem)->changeItem(10); _itemTemp->changeItem(ITEMLIST_END);  break; }
			else
			{
				addItem((ITEMLIST)_itemTemp->getNum(), _itemSlot[_vItem.size()].x, _itemSlot[_vItem.size()].y);
				_itemTemp->changeItem(ITEMLIST_END);
				break;
			}
		}
		if (count == _vItem.size()) { addItem((ITEMLIST)_itemTemp->getNum(), _itemSlot[_vItem.size()].x, _itemSlot[_vItem.size()].y); _itemTemp->changeItem(ITEMLIST_END); break; }
	}
}

void inventoryScene::loadItem(void)
{
	if (DATABASE->getLoadInven())
	{
		DATABASE->setLoadInven(false);
		_vItem.clear();
		for (int i = 0; i < DATABASE->getItemlist().size(); i++)
		{
			addItem((ITEMLIST)DATABASE->getItemlist()[i], _itemSlot[i].x, _itemSlot[i].y);
		}
	}
}