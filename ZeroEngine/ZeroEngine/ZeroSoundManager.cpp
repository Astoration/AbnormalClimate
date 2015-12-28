#include "stdafx.h"
#include "ZeroSoundManager.h"
#include <iostream>
ZeroSoundManager::ZeroSoundManager() {
	FMOD::System_Create(&system);
	system->init(256, FMOD_INIT_NORMAL, NULL);
}

ZeroSoundManager::~ZeroSoundManager() {

}

void ZeroSoundManager::Update(float _eTime) {
	system->update();

	for (auto iter = soundList.begin(); iter != soundList.end(); ++iter) {
		for (auto iter_ = std::get<1>(iter->second).begin(); iter_ != std::get<1>(iter->second).end();) {
			bool isPlaying;
			(*iter_)->isPlaying(&isPlaying);
			if (!isPlaying) {
				iter_ = std::get<1>(iter->second).erase(iter_++);
			}
			else {
				++iter_;
			}
		}
	}
}

ZeroSoundManager* ZeroSoundManager::Instance() {
	static ZeroSoundManager instance;
	return &instance;
}

void ZeroSoundManager::PushSound(char* _filepath, char* _name, ...) {
	char buffer[256] = { 0 };
	char* data = buffer;
	va_list vargs;
	va_start(vargs, _name);
	int ret = vsnprintf(data, sizeof(buffer), _name, vargs);
	va_end(vargs);
	if (ret + 1 > sizeof(buffer)) data = static_cast<char *>(malloc(ret + 1));
	va_start(vargs, _name);
	vsprintf(data, _name, vargs);
	va_end(vargs);
	std::string args(data);
	if (data != buffer) free(data);
	std::cout << data << std::endl;
	FMOD::Sound* sound;
	std::list<FMOD::Channel*> channel;
	system->createSound(_filepath, FMOD_DEFAULT, 0, &sound);

	if (soundList.find(args) == soundList.end()) {
		soundList[args] = std::make_tuple(sound, channel, 256);
	}
}

void ZeroSoundManager::PopSound(char* _name, ...) {
	char buffer[256] = { 0 };
	char* data = buffer;
	va_list vargs;
	va_start(vargs, _name);
	int ret = vsnprintf(data, sizeof(buffer), _name, vargs);
	va_end(vargs);
	if (ret + 1 > sizeof(buffer)) data = static_cast<char *>(malloc(ret + 1));
	va_start(vargs, _name);
	vsprintf(data, _name, vargs);
	va_end(vargs);
	std::string args(data);
	if (data != buffer) free(data);

	std::get<0>(soundList[args])->release();
	soundList.erase(args);
}

void ZeroSoundManager::SetConcurrency(int _concurrency, char* _name, ...) {
	char buffer[256] = { 0 };
	char* data = buffer;
	va_list vargs;
	va_start(vargs, _name);
	int ret = vsnprintf(data, sizeof(buffer), _name, vargs);
	va_end(vargs);
	if (ret + 1 > sizeof(buffer)) data = static_cast<char *>(malloc(ret + 1));
	va_start(vargs, _name);
	vsprintf(data, _name, vargs);
	va_end(vargs);
	std::string args(data);
	if (data != buffer) free(data);

	std::get<2>(soundList[args]) = _concurrency;
}

void ZeroSoundManager::Play(const char* _name, ...) {
	char buffer[256] = { 0 };
	char* data = buffer;
	va_list vargs;
	va_start(vargs, _name);
	int ret = vsnprintf(data, sizeof(buffer), _name, vargs);
	va_end(vargs);
	if (ret + 1 > sizeof(buffer)) data = static_cast<char *>(malloc(ret + 1));
	va_start(vargs, _name);
	vsprintf(data, _name, vargs);
	va_end(vargs);
	std::string args(data);
	if (data != buffer) free(data);

	int delta = std::get<1>(soundList[args]).size() - std::get<2>(soundList[args]) + 1;
	for (auto i = 0; i < delta; i++) {
		std::get<1>(soundList[args]).front()->stop();
	}

	FMOD::Channel* channel;
	system->playSound(std::get<0>(soundList[args]), 0, false, &channel);
	std::get<1>(soundList[args]).push_back(channel);
}

void ZeroSoundManager::Stop() {
	for (auto iter : soundList) {
		for (auto iter_ : std::get<1>(iter.second)) {
			iter_->stop();
		}
	}
}

void ZeroSoundManager::Stop(char* _name, ...) {
	char buffer[256] = { 0 };
	char* data = buffer;
	va_list vargs;
	va_start(vargs, _name);
	int ret = vsnprintf(data, sizeof(buffer), _name, vargs);
	va_end(vargs);
	if (ret + 1 > sizeof(buffer)) data = static_cast<char *>(malloc(ret + 1));
	va_start(vargs, _name);
	vsprintf(data, _name, vargs);
	va_end(vargs);
	std::string args(data);
	if (data != buffer) free(data);

	for (auto iter : std::get<1>(soundList[args])) {
		iter->stop();
	}
}

void ZeroSoundManager::Reset() {
	for (auto iter : soundList) {
		for (auto iter_ : std::get<1>(iter.second)) {
			iter_->stop();
		}
		Play(iter.first.c_str());
	}
}

void ZeroSoundManager::Reset(char* _name, ...) {
	for (auto iter : std::get<1>(soundList[_name])) {
		iter->stop();
	}
	Play(_name);
}
