#pragma once

#pragma warning(disable: 4996)

#define ZeroSoundMgr ZeroSoundManager::Instance()

class ZeroSoundManager {
private:
	ZeroSoundManager();

	FMOD::System* system;
	std::map<std::string, std::tuple<FMOD::Sound*, std::list<FMOD::Channel*>, int>> soundList;

public:
	~ZeroSoundManager();

	static ZeroSoundManager* Instance();

	void Update(float _eTime);

	void PushSound(char* _filepath, char* _name, ...);
	void PopSound(char* _name, ...);

	void SetConcurrency(int _concurrency, char* _name, ...);

	void Play(const char* name, ...);

	void Stop();
	void Stop(char* _name, ...);

	void Reset();
	void Reset(char* _name, ...);
};
