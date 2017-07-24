#include "stdafx.h"
#include "item.h"


item::item()
{
}


item::~item()
{
}


HRESULT item::init(ITEMLIST itemlist, float x, float y)
{
	_itemImage = IMAGEMANAGER->findImage("ITEM");
	_itemlist = itemlist;
	_x = x;
	_y = y;

	switch (_itemlist)
	{
		case ITEMLIST_HABANERO :
		{
			_frameX = 0;
			_frameY = 0;
		}
		break;
		case ITEMLIST_BEE :
		{
			_frameX = 1;
			_frameY = 0;
		}
		break;
		case ITEMLIST_WING :
		{
			_frameX = 2;
			_frameY = 0;
		}
		break;
		case ITEMLIST_JAM :
		{
			_frameX = 0;
			_frameY = 1;
		}
		break;
		case ITEMLIST_KETCHUP :
		{
			_frameX = 1;
			_frameY = 1;
		}
		break;
		case ITEMLIST_CHOKO :
		{
			_frameX = 2;
			_frameY = 1;
		}
		break;
		case ITEMLIST_CAKE :
		{
			_frameX = 0;
			_frameY = 2;
		}
		break;
		case ITEMLIST_PIZZA :
		{
			_frameX = 1;
			_frameY = 2;
		}
		break;
		case ITEMLIST_DONUT :
		{
			_frameX = 2;
			_frameY = 2;
		}
		break;
		case ITEMLIST_PIE:
		{
			_frameX = 0;
			_frameY = 3;
		}
		break;
		case ITEMLIST_HAMBURGER:
		{
			_frameX = 1;
			_frameY = 3;
		}
		break;
		case ITEMLIST_HOTDOG:
		{
			_frameX = 2;
			_frameY = 3;
		}
		break;
		case ITEMLIST_JAMCAKE :
		{
			_frameX = 0;
			_frameY = 4;
		}
		break;
		case ITEMLIST_TOMATOPIZZA :
		{
			_frameX = 1;
			_frameY = 4;
		}
		break;
		case ITEMLIST_CUPCAKE :
		{
			_frameX = 2;
			_frameY = 4;
		}
		break;
		case ITEMLIST_STAR :
		{
			_frameX = 0;
			_frameY = 5;
		}
		break;
		case ITEMLIST_END:
		{
			_frameX = 1;
			_frameY = 5;
		}
	}

	return S_OK;
}



void item::update()
{
	_itemRect = RectMake(_x, _y, _itemImage->getFrameWidth(), _itemImage->getFrameHeight());
}

void item::release()
{

}

void item::render(float x, float y)
{
	_itemImage->frameRender(getMemDC(), x, y, _frameX, _frameY);
}

void item::render(int camX, bool isCam)
{
	_itemImage->frameRender(getMemDC(), _x - camX, _y, _frameX, _frameY);
}

void item::setCenterXY(float x, float y)
{
	_x = x - _itemImage->getFrameWidth() / 2;
	_y = y - _itemImage->getFrameHeight() / 2;
}

void item::changeItem(int itemlist)
{
	_itemlist = (ITEMLIST)itemlist;
	switch (_itemlist)
	{
	case ITEMLIST_HABANERO:
	{
		_frameX = 0;
		_frameY = 0;
	}
	break;
	case ITEMLIST_BEE:
	{
		_frameX = 1;
		_frameY = 0;
	}
	break;
	case ITEMLIST_WING:
	{
		_frameX = 2;
		_frameY = 0;
	}
	break;
	case ITEMLIST_JAM:
	{
		_frameX = 0;
		_frameY = 1;
	}
	break;
	case ITEMLIST_KETCHUP:
	{
		_frameX = 1;
		_frameY = 1;
	}
	break;
	case ITEMLIST_CHOKO:
	{
		_frameX = 2;
		_frameY = 1;
	}
	break;
	case ITEMLIST_CAKE:
	{
		_frameX = 0;
		_frameY = 2;
	}
	break;
	case ITEMLIST_PIZZA:
	{
		_frameX = 1;
		_frameY = 2;
	}
	break;
	case ITEMLIST_DONUT:
	{
		_frameX = 2;
		_frameY = 2;
	}
	break;
	case ITEMLIST_PIE:
	{
		_frameX = 0;
		_frameY = 3;
	}
	break;
	case ITEMLIST_HAMBURGER:
	{
		_frameX = 1;
		_frameY = 3;
	}
	break;
	case ITEMLIST_HOTDOG:
	{
		_frameX = 2;
		_frameY = 3;
	}
	break;
	case ITEMLIST_JAMCAKE:
	{
		_frameX = 0;
		_frameY = 4;
	}
	break;
	case ITEMLIST_TOMATOPIZZA:
	{
		_frameX = 1;
		_frameY = 4;
	}
	break;
	case ITEMLIST_CUPCAKE:
	{
		_frameX = 2;
		_frameY = 4;
	}
	break;
	case ITEMLIST_STAR:
	{
		_frameX = 0;
		_frameY = 5;
	}
	break;
	}
}