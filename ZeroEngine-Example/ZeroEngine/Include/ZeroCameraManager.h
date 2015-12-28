#pragma once

#include "ZeroIScene.h"

#define ZeroCameraMgr ZeroCameraManager::Instance()

class ZeroCameraManager {

private:
	ZeroVec currentPosition;
	ZeroIScene* followingTarget;

	bool isCameraEnabled;

	// 카메라가 이동 가능한 위치는 (0, 0)부터 (mapWidth, mapHeight) 사이이다.
	int mapWidth, mapHeight;
	float moveSpeed;

	//싱글 톤
	ZeroCameraManager();

public:
	~ZeroCameraManager();
	static ZeroCameraManager* Instance();

	void Update(float eTime);

	bool IsCamera() const;
	void SetCameraOn();
	void SetCameraOff();

	ZeroVec Pos() const;
	void SetPos(ZeroVec pos);

	template<typename T>
	void SetPos(T x, T y);

	ZeroIScene* Target() const;
	void SetTarget(ZeroIScene* _target);

	int Width() const;
	template<typename T>
	void SetWidth(T _mapWidth);

	int Height() const;
	template<typename T>
	void SetHeight(T _mapHeight);

	template<typename T>
	void SetScreen(T _mapWidth, T _mapHeight);

	float MoveSpeed() const;
	template<typename T>
	void SetSpeed(T _moveSpeed);
};

template <typename T>
void ZeroCameraManager::SetPos(T x, T y) {
	currentPosition.x = static_cast<float>(x); currentPosition.y = static_cast<float>(y);
}

template <typename T>
void ZeroCameraManager::SetWidth(T _mapWidth) {
	mapWidth = static_cast<int>(_mapWidth);
}

template <typename T>
void ZeroCameraManager::SetHeight(T _mapHeight) {
	mapHeight = static_cast<int>(_mapHeight);
}

template <typename T>
void ZeroCameraManager::SetSpeed(T _moveSpeed) {
	moveSpeed = static_cast<float>(_moveSpeed);
}

template <typename T>
void ZeroCameraManager::SetScreen(T _mapWidth, T _mapHeight) {
	mapWidth = static_cast<int>(_mapWidth); mapHeight = static_cast<int>(_mapHeight);
}