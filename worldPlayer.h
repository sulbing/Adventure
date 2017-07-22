#pragma once
#include "gameNode.h"

class worldPlayer : public gameNode
{
	

private:
	RECT _rc;
	bool _haveBridgeSkill;
	bool _haveClimbSkill;


	//ÁÂÇ¥
	float _X, _y;
	
public:

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);


	worldPlayer();
	~worldPlayer();
};

