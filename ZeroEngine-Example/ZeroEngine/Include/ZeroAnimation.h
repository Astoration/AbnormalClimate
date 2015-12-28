#pragma once

#include "ZeroSprite.h"

using namespace std;

class ZeroAnimation : public ZeroIScene {

private:
	vector<ZeroSprite*> animationList;
	int numberOfFrames;
	float framesPerSecond;
	float currentFrame;
	bool isRunning;
	bool isLooping;

public:
	// Deprecated Constructor
	template <typename T>
	ZeroAnimation(T _frameSpeed, bool _isLooping = true);
	ZeroAnimation(float _frameSpeed, bool _isLooping = true);
	~ZeroAnimation();

	void PushSprite(char* _imageFilePath, ...);
	void Start();
	void Stop();

	void Update(float _eTime);
	void Render();

	int NumberOfFrames() const;
	float FramesPerSecond() const;
	void SetFramesPerSecond(float _framesPerSecond);
	int CurrentFrame() const;
	void SetCurrentFrame(int _currentFrame);
	bool IsRunning() const;
	void SetRunning(bool _isRunning);
	bool IsLooping() const;
	void SetLooping(bool _isLooping);

	// Deprecated Getter and Setter Start
	template <typename T>
	void SetFrameSpeed(T _frameSpeed);
	template <typename T>
	void SetFrame(T _currentFrame);
	float Frame() const;
	int MaxFrame() const;
	// Deprecated Getter and Setter End
};

// Templates only be implemented in the header file

// Deprecated Constructor Start
template <typename T>
ZeroAnimation::ZeroAnimation(T _frameSpeed, bool _isLooping) {
	numberOfFrames = 0;
	framesPerSecond = static_cast<float>(_frameSpeed);
	currentFrame = 0;
	isRunning = true;
	isLooping = _isLooping;
}
// Deprecated Constructor End

// Deprecated Getter and Setter Start
template <typename T>
void ZeroAnimation::SetFrameSpeed(T _frameSpeed) {
	framesPerSecond = static_cast<float>(_frameSpeed);
}

template <typename T>
void ZeroAnimation::SetFrame(T _currentFrame) {
	currentFrame = static_cast<float>(_currentFrame);
}
// Deprecated Getter and Setter End
