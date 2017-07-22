#pragma once
#include "singletonBase.h"

class item;

struct tagSaveData
{
	int _status_hearts;
	int _status_attack;
	int _status_speed;
	int _status_bonus;
};

enum RECTCOLLISION
{
	STAGE_NYMPH_1,
	STAGE_NYMPH_2,
	STAGE_HOUSE,
	STAGE_1_IN,
	STAGE_1_OUT,
	STAGE_2_IN,
	STAGE_2_OUT,
	STAGE_3_IN,
	STAGE_3_OUT,
	STAGE_CHEST,
	STAGE_MIDBOSS,
	JAKE_BRIDGE_IN,
	JAKE_BRIDGE_OUT,
	JAKE_CLIMB_1,
	JAKE_CLIMB_2,
	RECTCOLLISION_END
};

class database : public singletonBase<database>
{
private :
	float _WorldX, _WorldY;
	int _status_hearts;
	int _status_attack;
	int _status_speed;
	int _status_bonus;
	int _currentHP;
	std::vector<int> _vItemaddList;
	std::vector<int> _vItemuseList;
	std::vector<int> _vItemList;
	tagSaveData _saveData;
	bool _isLoadInventory;
	bool _isLoadStatus;

	RECTCOLLISION _worldPosition;

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
	int getStatusBonus() { return _status_bonus; }
	int getStatusCureentHP(void) { return _currentHP; }
	POINT getWorldstate(void) { return PointMake(_WorldX, _WorldY); }

	void setstatus(int hearts, int attack, int speed, int bonus, int currentHP);
	void useBonus(int Num);

	void pushbackaddVector(int A) { _vItemaddList.push_back(A); }
	void pushbackuseVector(int A) { _vItemuseList.push_back(A); }

	std::vector<int> getaddVector(void) { return _vItemaddList; }
	void clearaddVector(void) { _vItemaddList.clear(); }

	std::vector<int> getuseVector(void) { return _vItemuseList; }
	void clearuseVector(void) { _vItemuseList.clear(); }

	void invenSaveChange(std::vector<item*> _itemlist);
	std::vector<int> getItemlist(void) { return _vItemList; }

	void saveData(void);
	void loadData(void);

	void setLoadInven(bool A) { _isLoadInventory = A; }
	bool getLoadInven(void) { return _isLoadInventory; }
	void setLoadStatus(bool A) { _isLoadStatus = A; }
	bool getLoadStatus(void) { return _isLoadStatus; }

	void setWorldPosition(RECTCOLLISION worldPosition) { _worldPosition = worldPosition; }
	RECTCOLLISION getWorldPosition() { return _worldPosition; }

	database();
	~database();
};

