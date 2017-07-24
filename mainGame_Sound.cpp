#include "stdafx.h"
#include "mainGame.h"

void mainGame::addSound()
{
	SOUNDMANAGER->addSound("opening", "Sound/opening.wav", true, false);
	SOUNDMANAGER->addSound("타격음1", "Sound/타격음1.wav", false, false);
	SOUNDMANAGER->addSound("타격음2", "Sound/타격음2.wav", false, false);
	SOUNDMANAGER->addSound("뛸때", "Sound/뛸때.wav", false, false);
	SOUNDMANAGER->addSound("착지할때", "Sound/착지할때.wav", false, false);
	SOUNDMANAGER->addSound("맞았을때", "Sound/맞았을때.wav", false, false);
	SOUNDMANAGER->addSound("죽을때", "Sound/죽을때.mp3", false, false);

	SOUNDMANAGER->addSound("월드", "Sound/월드.mp3", true, true);
	SOUNDMANAGER->addSound("보스스테이지", "Sound/보스스테이지.mp3", true, true);
	SOUNDMANAGER->addSound("보물상자", "Sound/보물상자.mp3", true, true);
	SOUNDMANAGER->addSound("스테이지", "Sound/스테이지.mp3", true, true);
}