#include "stdafx.h"
#include "mainGame.h"

//전역변수 선언하는 곳
HINSTANCE	_hInstance;		//window App 고유번호
HWND		_hWnd;			//윈도우 핸들
mainGame	_mg;
POINT		_ptMouse;		//마우스 좌표 받을 POINT 변수

//=============================================================================

LPTSTR _lpszClass = TEXT("Theta API");	//윈도우 창 텍스트

//함수 전방선언 == 함수의 프로토타입 선언
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowsSize(int x, int y, int width, int height);

//이게 메인함수
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG			message;	//운영체제에서 발생하는 메시지 정보를 저장하기 위한 구조체
	WNDCLASS	wndClass;	//윈도우(창)의 정보를 저장하기 위한 구조체

	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;										//클래스 여분 메모리 설정
	wndClass.cbWndExtra = 0;										//윈도우 여분 메모리 설정
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//윈도우 백그라운드 칼라
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//윈도우 커서 모양 (현재 화살표)
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//윈도우 아이콘 모양
	wndClass.hInstance = hInstance;									//윈도우 인스턴스
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//윈도우 프로시져
	wndClass.lpszClassName = _lpszClass;							//윈도우 클래스이름
	wndClass.lpszMenuName = NULL;									//윈도우 메뉴이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//윈도우 스타일

	//윈도우 정보 등록
	RegisterClass(&wndClass);

	_hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,
		WINSTARTX,				//윈도우 창 시작위치 X
		WINSTARTY,				//윈도우 창 시작위치 y
		WINSIZEX,				//윈도우 창 가로크기
		WINSIZEY,				//윈도우 창 세로크기
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);
	
	//클라이언트 영역 재조정 완료.
	setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//윈도우 창 화면에 보여주는 명령어
	ShowWindow(_hWnd, cmdShow);

	//메인게임 클래스의 이닛(초기화) 함수가 실패하면
	if (FAILED(_mg.init()))
	{
		//종료처리
		return 0;
	}

	//메시지 루프
	//GetMessage : 메시지를 보내면 그때 루프가 돈다
	//PeekMessage : 항시 루프가 돈다

	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);		//키보드 입력하는 순간 그 메시지 처리를 담당
			DispatchMessage(&message);		//실제로 윈도우로 메시지들을 전달하는 담당
		}
		else
		{
			//여기서 처리한다
			TIMEMANAGER->update(60.0f);
			_mg.update();
			_mg.render();
		}

	}

	//릴리즈 함수가 밑에 있다는건 메시지를 다 돌았으면 메인게임 해제해라
	_mg.release();

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg.MainProc(hWnd, iMessage, wParam, lParam);
}

//클라이언트 영역 재조정 함수
void setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	AdjustWindowRect(&winRect, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);
}