#include "stdafx.h"
#include "database.h"
#include "item.h"
#include "inventoryScene.h"
#include "statusScene.h"
#include "minimapScene.h"

database::database()
	: _worldPosition(STAGE_HOUSE)
{
}


database::~database()
{
}

HRESULT database::init(void)
{
	_isLoadInventory = false;
	_isOninventory = false;
	_isLoadStatus = false;
	_useItem = false;
	_status_bonus = 0;
	_inven = new inventoryScene;
	_inven->init();
	_status = new statusScene;
	_status->init();
	_minimap = new minimapScene;
	_minimap->init();
	_interfaceNum = 0;
	setstatus(0, 0, 0, 0, 8);

	_saveData.currentHP = 8;
	_saveData.status_attack = 0;
	_saveData.status_bonus = 0;
	_saveData.status_hearts = 0;
	_saveData.status_speed = 0;

	for (int i = 0; i < 3; i++)
	{
		_effectItem[i] = false;
	}
	return S_OK;
}

void database::release(void)
{

}

void database::invenSaveChange(std::vector<item*> _itemlist)
{
	_vItemList.clear();
	for (int i = 0; i < _itemlist.size(); i++)
	{
		_vItemList.push_back(_itemlist[i]->getNum());
	}
}

void database::saveData(void)
{
	_saveData.status_attack = _status_attack;
	_saveData.status_hearts = _status_hearts;
	_saveData.status_speed = _status_speed;
	_saveData.status_bonus = _status_bonus;
	_saveData.currentHP = _currentHP;

	if (_saveData.vItemaddList.size() != 0) _saveData.vItemaddList.clear();
	if (_vItemaddList.size() != 0) _saveData.vItemaddList = _vItemaddList;

	if (_saveData.vItemList.size() != 0) _saveData.vItemList.clear();
	if (_vItemList.size() != 0) _saveData.vItemList = _vItemList;
}

void database::loadData(void)
{
	_status_attack = _saveData.status_attack;
	_status_hearts = _saveData.status_hearts;
	_status_speed = _saveData.status_speed;
	_status_bonus = _saveData.status_bonus;
	_currentHP = _saveData.currentHP;

	if (_saveData.vItemaddList.size() != 0) _vItemaddList = _saveData.vItemaddList;
	if (_saveData.vItemList.size() != 0) _vItemList = _saveData.vItemList;
}

void database::setstatus(int hearts, int attack, int speed, int bonus, int currentHP)
{
	_status_attack = attack;
	_status_hearts = hearts;
	_status_speed = speed;
	_status_bonus = bonus;
	_currentHP = currentHP;
}

void database::useBonus(int Num)
{
	_status_bonus -= 1;
	switch (Num)
	{
	case 12:
		_status_hearts++;
		setStatusCurrentHP(getStatusCureentHP() + 4);
		break;
	case 13:
		_status_attack++;
		break;
	case 14:
		_status_speed++;
		break;
	}
}

gameNode* database::getInterface(void)
{
	switch (_interfaceNum)
	{
	case 0: return _status; break;
	case 1: return _inven; break;
	case 2: return _minimap; break;
	}
	
}