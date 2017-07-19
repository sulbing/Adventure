#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

#include <stdlib.h>
#include <iostream>
#include <memory.h>
#include <tchar.h>

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "soundManager.h"
#include "timeManager.h"
#include "effectManager.h"
#include "sceneManager.h"
#include "keyAniManager.h"
#include "utils.h"
#include "txtData.h"
#include "database.h"

using namespace std;
using namespace THETA_UTIL;

//==============================
// ## 디파인문 ## 17.04.26 ##
//==============================

#define WINNAME (LPTSTR)(TEXT("Theta API"))	//윈도우 창 이름
#define WINSTARTX 500						//윈도우 시작좌표X
#define WINSTARTY 200						//윈도우 시작좌표Y
#define WINSIZEX 800						//윈도우 가로크기
#define WINSIZEY 480						//윈도우 세로크기
#define WINSTYLE WS_CAPTION | WS_SYSMENU

//싱글톤화 시킨 클래스 디파인화
#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define KEYANIMANAGER keyAniManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define DATABASE database::getSingleton()

//==============================
// ## 매크로함수 ## 17.04.26 ##
//==============================

#define SAFE_DELETE(p) {if(p) {delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[](p); (p) = NULL;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p)=NULL;}}

//==============================
// ## 전역변수 ## 17.05.01 ##
//==============================

extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;