#pragma once
#include "singletonBase.h"

class database : public singletonBase<database>
{
private :
	float _WorldX, _WorldY;
	int _status_hearts;
	int _status_attack;
	int _status_speed;
	int _currentHP;
	std::vector<int> _vItemaddList;
	std::vector<int> _vItemuseList;

public:
	HRESULT init(void);
	void release(void);

	void setWolrdstate(float x, float y) { _WorldX = x; _WorldY = y; }
	void setStatusHearts(int A) { _status_hearts = A; }
	void setStatusAttack(int A) { _status_attack = A; }
	void setStatusSpeed(int A) { _status_speed = A; }
	void setStatusCurrentHP(int A) { _currentHP = A; }

	int getStatusHearts() { return _status_hearts; }
	int getStatusAttack() { return _status_attack; }
	int getStatusSpeed() { return _status_speed; }
	int getStatusCureentHP(void) { return _currentHP; }

	void pushbackaddVector(int A) { _vItemaddList.push_back(A); }
	void pushbackuseVector(int A) { _vItemuseList.push_back(A); }

	std::vector<int> getaddVector(void) { return _vItemaddList; }
	void clearaddVector(void) { _vItemaddList.clear(); }

	std::vector<int> getuseVector(void) { return _vItemuseList; }
	void clearuseVector(void) { _vItemuseList.clear(); }

	database();
	~database();
};

