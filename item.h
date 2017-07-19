#pragma once
#include "gameNode.h"

enum ITEMLIST
{
	ITEMLIST_HABANERO = 0,
	ITEMLIST_BEE,
	ITEMLIST_WING,

	ITEMLIST_JAM,
	ITEMLIST_KETCHUP,
	ITEMLIST_CHOKO,

	ITEMLIST_CAKE,
	ITEMLIST_PIZZA,
	ITEMLIST_DONUT,

	ITEMLIST_PIE,
	ITEMLIST_HAMBURGER,
	ITEMLIST_HOTDOG,

	ITEMLIST_JAMCAKE,
	ITEMLIST_TOMATOPIZZA,
	ITEMLIST_CUPCAKE,

	ITEMLIST_STAR,

	ITEMLIST_END
};

class item : public gameNode
{
private :
	float _x, _y;
	RECT _itemRect;
	image* _itemImage;
	ITEMLIST _itemlist;
	int _frameX, _frameY;

public:
	HRESULT init(ITEMLIST itemlist, float x, float y);
	void changeItem(int itemlist);
	void update();
	void release();
	void render(float x, float y);

	RECT getRect(void) { return _itemRect; }
	int getNum(void) { return (int)_itemlist; }

	void setXY(float x, float y) { _x = x; _y = y; }
	void setCenterXY(float x, float y);

	float getX(void) { return _x; }
	float getY(void) { return _y; }

	float getImageSize(void) { return _itemImage->getFrameWidth() / 2; }

	item();
	~item();
};

