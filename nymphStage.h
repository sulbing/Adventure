#pragma once
#include"gameNode.h"
#include"stagePlayer.h"
#include"enemy.h"

class nymphStage : public gameNode
{
private:
	image*			_nymph;
	animation*		 _nymphAni;

	stagePlayer*	_stageFinn;
	enemy*			_mi1;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void pixelCollision(void);

	nymphStage();
	~nymphStage();
};