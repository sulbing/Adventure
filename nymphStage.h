#pragma once
#include"gameNode.h"
#include"stagePlayer.h"

class nymphStage : public gameNode
{
private:
	image* _nymph;
	animation* _nymphAni;

	stagePlayer* _stageFinn;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	nymphStage();
	~nymphStage();
};