#include "stdafx.h"
#include "database.h"
#include "item.h"


database::database()
{
}


database::~database()
{
}

HRESULT database::init(void)
{
	_isLoadInventory = false;
	_isLoadStatus = false;
	_status_bonus = 0;


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
	_saveData._status_attack = _status_attack;
	_saveData._status_hearts = _status_hearts;
	_saveData._status_speed = _status_speed;
	_saveData._status_bonus = _status_bonus;
}

void database::loadData(void)
{
	_status_attack = _saveData._status_attack;
	_status_hearts = _saveData._status_hearts;
	_status_speed = _saveData._status_speed;
	_status_bonus = _saveData._status_bonus;
}

void database::setstatus(int hearts, int attack, int speed, int bonus, int currentHP)
{
	_status_attack = hearts;
	_status_hearts = attack;
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
		break;
	case 13:
		_status_attack++;
		break;
	case 14:
		_status_speed++;
		break;
	}
}