#pragma once
#include "gameNode.h"

class UI : public gameNode
{
private:
	image* _imgHeart[5];

	int _maxHeart;
	int _curHP;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	UI();
	~UI();
};

