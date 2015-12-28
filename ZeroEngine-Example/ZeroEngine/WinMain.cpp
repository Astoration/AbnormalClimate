#include "stdafx.h"
#include <Windows.h>
#include "Zero.h"
#include "LoadingScene.h"
#include "TitleScene.h"

#pragma comment(lib, "comctl32")

//이 변수를 주석처리 해버리면 콘솔창 안뜬다.
// ZeroConsole g_Console;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT) {
	int WindowWidth = 1600/1.2;
	int WindowHeight = 900/1.2;

	ZeroApp->RegisterWindowSize(WindowWidth, WindowHeight);
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, ZeroApp->MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"ZeroEngine", NULL };
	RegisterClassEx(&wc);

	srand(GetTickCount());

	// WS_EX_TOPMOST | WS_POPUP :: 전체화면 모드
	// WS_OVERLAPPEDWINDOW		:: 창화면 모드
	HWND hWnd = CreateWindow(L"ZeroEngine", L"AbnormalClimate",
							 WS_EX_TOPMOST | WS_OVERLAPPEDWINDOW, 100, 0, WindowWidth, WindowHeight,
							 GetDesktopWindow(), NULL, wc.hInstance, NULL);

	ZeroApp->SetHwnd(hWnd);

	if (SUCCEEDED(ZeroApp->InitD3D(hWnd, false)))
	{

		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);


		
		
		/*
		* 여기서 부터 배열 테스트 디버깅용
		
		int map[11][14]=
		{
			  { -1, -1, -1, -1, -1, -1, -1, 52, -1, -1, -1, -1, -1, -1 }
			, { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
			, { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
			, { -1, -1, -1, -1, -1, 51, -1, -1, -1, -1, -1, -1, -1, -1 }
			, { -1, -1, -1, -1, -1,  3, -1, -1, -1,  3, -1, -1, -1, -1 }
			, { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 51, -1, -1 }
			, { -1, -1, -1, 52, -1, -1, -1, -1, -1,  1, 1, 1, 2, -1 }
			, { -1, -1, -1,  3, -1, -1,  3, -1,  3, -1, 1,  3, -1, -1 }
			, {  0,  1,  1, -1, -1, -1, -1, 50, -1, -1, -1,  1,  2, -1 }
			, { -1, -1, -1, -1, -1, -1, -1, 51, -1, -1, -1, -1, -1, -1 }
			, {  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2, -1, -1, -1 }

		};

		
		* 여기까지양 >_<
		*/



		ZeroSceneMgr->ChangeScene(new LoadingScene());

		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (msg.message != WM_QUIT) {
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
				ZeroApp->Render();
		}
	}
	//종료
	ZeroSceneMgr->Clear();

	UnregisterClass(L"ZeroEngine", wc.hInstance);
	return 0;
}