#pragma once
#include "Zero.h"
#include "Player.h"
#include "Skill.h"
class InStageScene :
	public ZeroIScene
{
private:
	ZeroSprite* bg;
	Skill *skill;
	Player* m_Player;
	float ThunderTime;
	ZeroSprite *timeInterface;
	ZeroSprite *cursor;
	ZeroFont *timeFont;
	float limitTime;
	bool bossable;
	int stage, stagekind;
	int map[11][14];
	int tt;
public:
	InStageScene(int map[11][14],char* BackgroundName,bool isBoss, float _t, int _stageKind, int _stage);
	virtual ~InStageScene();
	void Update(float eTime);
	void Render();
	int ClockCount;
	ZeroIScene* tile[11][14];
	bool Thunder[11][14];
	void SetThunder(int i, int j);
	Player* GetPlayer(){ return m_Player; }
};

