#pragma once
#include"gameNode.h"

class nymphStage : public gameNode
{
private:
	image* _nymph;
	animation* _nymphAni;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	nymphStage();
	~nymphStage();
};