#pragma once
#include "singletonBase.h"

class inventoryScene;
class statusScene;
class minimapScene;
class item;

struct tagSaveData
{
	int status_hearts;
	int status_attack;
	int status_speed;
	int status_bonus;
	int currentHP;

	std::vector<int> vItemaddList;
	std::vector<int> vItemList;
};

enum RECTCOLLISION
{
	STAGE_NYMPH_1,		//���� ����
	STAGE_NYMPH_2,		//������ ����
	STAGE_HOUSE,		//�� ��
	STAGE_1_LEFT,		//���� ��� �Ʒ�
	STAGE_1_RIGHT,		//���� ��� ��
	STAGE_2_LEFT,		//������ �Ʒ� ��� �Ʒ�
	STAGE_2_RIGHT,		//������ �Ʒ� ��� ��
	STAGE_3_LEFT,		//������ �� ��� �Ʒ�
	STAGE_3_RIGHT,		//������ �� ��� ��
	STAGE_CHEST,		//���� ��
	STAGE_MIDBOSS,		//������ �Ʒ� ��
	JAKE_BRIDGE_IN,		//�ٸ� ��
	JAKE_BRIDGE_OUT,	//�ٸ� �Ʒ�
	JAKE_CLIMB_1,		//�Ʒ� �ö󰡱�
	JAKE_CLIMB_2,		//�� �ö󰡱�
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
	bool _isOninventory;
	int _interfaceNum;

	inventoryScene* _inven;
	statusScene* _status;
	minimapScene* _minimap;

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
	bool getInvenOn(void) { return _isOninventory; }
	POINT getWorldstate(void) { return PointMake(_WorldX, _WorldY); }
	tagSaveData getSaveData(void) { return _saveData; }

	void setstatus(int hearts, int attack, int speed, int bonus, int currentHP);
	void useBonus(int Num);
	void changeInven(void) { if (_isOninventory) _isOninventory = false; else _isOninventory = true; }

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

	gameNode* getInterface(void);

	void changeNum(int Num) { _interfaceNum = Num; }

	database();
	~database();
};

