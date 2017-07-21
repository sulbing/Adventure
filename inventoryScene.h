#pragma once
#include "gameNode.h"
#include "item.h"

class inventoryScene : public gameNode
{
private :
	std::vector<item*> _vItem;
	std::vector<item*>::iterator _viItem;
	POINT _itemSlot[40];
	item* _itemTemp;
	bool _drag;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void addItem(ITEMLIST itemlist, float x, float y);
	void useItem(void);

	void itemMix(void);

	void loadItem(void);

	inventoryScene();
	~inventoryScene();
};

