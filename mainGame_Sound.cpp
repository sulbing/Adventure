#include "stdafx.h"
#include "mainGame.h"

void mainGame::addSound()
{
	SOUNDMANAGER->addSound("opening", "Sound/opening.wav", true, false);
	SOUNDMANAGER->addSound("Ÿ����1", "Sound/Ÿ����1.wav", false, false);
	SOUNDMANAGER->addSound("Ÿ����2", "Sound/Ÿ����2.wav", false, false);
	SOUNDMANAGER->addSound("�۶�", "Sound/�۶�.wav", false, false);
	SOUNDMANAGER->addSound("�����Ҷ�", "Sound/�����Ҷ�.wav", false, false);
	SOUNDMANAGER->addSound("�¾�����", "Sound/�¾�����.wav", false, false);
	SOUNDMANAGER->addSound("������", "Sound/������.mp3", false, false);

	SOUNDMANAGER->addSound("����", "Sound/����.mp3", true, true);
	SOUNDMANAGER->addSound("������������", "Sound/������������.mp3", true, true);
	SOUNDMANAGER->addSound("��������", "Sound/��������.mp3", true, true);
	SOUNDMANAGER->addSound("��������", "Sound/��������.mp3", true, true);
}