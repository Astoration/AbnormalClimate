#pragma once
#include "Zero.h"
class SkillOne :
	public ZeroIScene
{
private:
	ZeroAnimation *p_mSkillOne;
	bool isRained, isWind,isThunder;
	float angle, time;;
public:
	ZeroAnimation* GetCloud(){ return p_mSkillOne; };
	SkillOne(ZeroVec temp);
	virtual ~SkillOne();
	void Update(float eTime);
	void Render();
	void SetRain(bool _option);
	void SetWind(float angle);
	void SetThunder(bool _option);
};

