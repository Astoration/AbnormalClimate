#pragma once
#include "Zero.h"
#include "Player.h"
class Skill :
	public ZeroIScene
{
private:
	int SkillKind;
	bool SkillActive;
	ZeroSprite *OnePre, *TwoPre, *ThreePre, *FourPre;
	ZeroAnimation *FourEffect,*TwoAfterEffect, *ThreeAfterEffect;
	ZeroVec *SkillTwoPoint;
	ZeroLine *TwoEffect;
	ZeroSprite *anchor;
	ZeroSprite *SkillBox, *OneBox, *TwoBox, *ThreeBox, *FourBox;
	ZeroSprite *OnePush, *TwoPush, *ThreePush, *FourPush;
	ZeroSprite *MpBox, *Mp;
	float mana;
	float eaterTime;
public:
	Skill();
	virtual ~Skill();
	void Update(float eTime);
	void Render();
	void SetSkillKind(int i){ SkillKind = i; };
	void AllRender();
	void AllCheck(Player *m_Player);
};

