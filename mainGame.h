#pragma once
#include "gameNode.h"


class mainGame : public gameNode
{
private:
	
public:
	virtual HRESULT init(void);		
	virtual void release(void);		
	virtual void update(void);		
	virtual void render(void);

	

	mainGame();
	~mainGame();
};

