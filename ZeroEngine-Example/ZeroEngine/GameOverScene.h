#pragma once
#include "Zero.h"
class GameOverScene :
	public ZeroIScene
{
private:
	ZeroSprite *bg, *box;
	ZeroFont *title;
	ZeroFont *time;
	ZeroSprite *button1, *button2;
	bool isStory;
	int map[11][14];
	ZeroSprite* cursor;
	int stageKind, stage;
	char a[10];
	bool bossable;
	int tt;
public:
	GameOverScene(bool GameOverble, int stageKind, bool bossable, int time, int stage, int map[11][14], int tt);
	virtual ~GameOverScene();
	void Update(float eTime);
	void Render();
};

