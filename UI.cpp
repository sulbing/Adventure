#include "stdafx.h"
#include "UI.h"

UI::UI(){}
UI::~UI(){}

HRESULT UI::init(void)
{
	_maxHeart = _curHP = 0;

	_imgHeart[0] = IMAGEMANAGER->findImage("UI_HEART_0");
	_imgHeart[1] = IMAGEMANAGER->findImage("UI_HEART_1");
	_imgHeart[2] = IMAGEMANAGER->findImage("UI_HEART_2");
	_imgHeart[3] = IMAGEMANAGER->findImage("UI_HEART_3");
	_imgHeart[4] = IMAGEMANAGER->findImage("UI_HEART_4");

	return S_OK;
}

void UI::release(void)	
{

}

void UI::update(void)	
{
	_maxHeart = DATABASE->getStatusHearts() + 2;
	_curHP = DATABASE->getStatusCureentHP();
}

void UI::render(void)	
{
	for (int i = 0; i < _maxHeart; i++)
	{
		if (i < _curHP / 4) _imgHeart[4]->render(getMemDC(), 40 * i, 0);
		else if (i == _curHP / 4) _imgHeart[_curHP % 4]->render(getMemDC(), 40 * i, 0);
		else _imgHeart[0]->render(getMemDC(), 40 * i, 0);

	}

	IMAGEMANAGER->findImage("UI_HEART_END")->render(getMemDC(), 40 * _maxHeart, 0);


	//char str[256];

	//wsprintf(str, "하트 : %d", DATABASE->getStatusHearts());
	//TextOut(getMemDC(), 0, 50, str, strlen(str));

	//wsprintf(str, "HP : %d", DATABASE->getStatusCureentHP());
	//TextOut(getMemDC(), 0, 70, str, strlen(str));

	//wsprintf(str, "로드 하트 : %d", DATABASE->getSaveData().status_hearts);
	//TextOut(getMemDC(), 0, 90, str, strlen(str));

	//wsprintf(str, "로드 HP : %d", DATABASE->getSaveData().currentHP);
	//TextOut(getMemDC(), 0, 110, str, strlen(str));
}