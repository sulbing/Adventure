#pragma once
#include "gameNode.h"

struct tagSlot
{
	POINT starSlot;
	bool On;
	RECT rcSlot;
};

class statusScene : public gameNode
{
private :
	image* _background;
	image* _star;
	image* _plus;

	tagSlot _Slot[15];

public:
	HRESULT init(void);
	void release();
	void update();
	void render();


	statusScene();
	~statusScene();
};

