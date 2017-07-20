#pragma once
#include "gameNode.h"

class sceneEffect : gameNode
{
private:
	int _alphaValue;

	bool _isChangeScene;
	bool _isFadeIN;
	bool _isFadeOUT;

public:
	sceneEffect();
	~sceneEffect();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void fadeIN();
	void fadeOUT();

	bool getChangeScene() { return _isChangeScene; }
	bool isFadeIN() { return _isFadeIN; }
	bool isFadeOUT() { return _isFadeOUT; }

	void setChangeScene(bool isChangeScene) { _isChangeScene = isChangeScene; }
	void setFadeIN(bool isFadeIN) { _isFadeIN = isFadeIN; }
	void setFadeOUT(bool isFadeOUT) { _isFadeOUT = isFadeOUT; }
};

