#include "stdafx.h"
#include "ZeroCursorManager.h"
#include "ZeroTextureManager.h"
#include "ZeroApplication.h"

#pragma warning(disable: 4996)

ZeroCursorManager::ZeroCursorManager() {
	cursorSurface = NULL;
	isCurserEnabled = true;
}

ZeroCursorManager::~ZeroCursorManager() {
	SAFE_RELEASE(cursorSurface);
}

ZeroCursorManager* ZeroCursorManager::Instance() {
	static ZeroCursorManager instance;
	return &instance;
}

void ZeroCursorManager::SetCursorShape() {
	ZeroTexMgr->LoadTextureFromFile("Texture/cursor.png")->GetSurfaceLevel(0, &cursorSurface);
	ZeroApp->GetDevice()->SetCursorProperties(15, 15, cursorSurface);
}

void ZeroCursorManager::ReloadResource() {
	ZeroTexMgr->LoadTextureFromFile("Texture/cursor.png")->GetSurfaceLevel(0, &cursorSurface);
	ZeroApp->GetDevice()->SetCursorProperties(15, 15, cursorSurface);
}

void ZeroCursorManager::UpdateCursorShape() {

}

void ZeroCursorManager::SetCursorOn() {
	isCurserEnabled = true;
}

void ZeroCursorManager::SetCursorOff() {
	isCurserEnabled = false;
}

void ZeroCursorManager::SetCursorToggle() {
	isCurserEnabled = !isCurserEnabled;
}

bool ZeroCursorManager::IsShowingCursor() {
	return isCurserEnabled;
}
