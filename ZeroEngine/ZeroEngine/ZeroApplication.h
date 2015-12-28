#pragma once

#include "ZeroRingBuffer.h"
#include "ZeroProcessMonitor.h"
#include "ZeroRegulator.h"
#include "ZeroCameraManager.h"
#include "ZeroSceneManager.h"
#include "ZeroSoundManager.h"
#include "ZeroInputManager.h"
#include "ZeroTextureManager.h"
#include "ZeroSpriteManager.h"
#include "ZeroShaderManager.h"
#include "ZeroResourceManager.h"

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=0; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=0; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=0; } }

#define ZeroApp ZeroApplication::Instance()

class ZeroApplication {

private:
	ZeroApplication();

	LPDIRECT3D9 D3D;
	LPDIRECT3DDEVICE9 D3D9Device;
	D3DPRESENT_PARAMETERS D3D9DeviceProperty;
	HWND hWnd;

	ZeroRingBuffer<LONGLONG, 10> times;
	ZeroProcessMonitor processMonitor;
	ZeroRegulator* processCpuUsageRegulator;
	ZeroRegulator* processMemoryUsageRegulator;

	float fps;
	float memoryUsage;
	float cpuUsage;

	int windowWidth;
	int windowHeight;

	bool CheckAndResetDevice();

public:
	~ZeroApplication();
	void Cleanup();

	static ZeroApplication* Instance();

	void CalculateFPS();
	void CalculateMemoryUsage();
	void CalculateCpuUsage();
	HWND GetHwnd() const;
	void SetHwnd(HWND _hWnd);
	LPDIRECT3DDEVICE9 GetDevice() const;
	float GetFPS() const;
	float GetMemoryUsage() const;
	float GetCpuUsage() const;
	int GetWindowWidth();
	int GetWindowHeight();
	void RegisterWindowSize(int _windowWidth, int _windowHeight);

	void Update(float _eTime);
	void Render();

	static LRESULT WINAPI MsgProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
	HRESULT InitD3D(HWND _hWnd, bool _isFullScreen = false);
};
