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
}