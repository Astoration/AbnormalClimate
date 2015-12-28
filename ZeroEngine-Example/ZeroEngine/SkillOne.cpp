#include "stdafx.h"
#include "SkillOne.h"


SkillOne::SkillOne(ZeroVec temp)
	:isRained(false), isWind(false), isThunder(false)
{
	p_mSkillOne = new ZeroAnimation(8.0f);
	for (int i = 1; i <= 5; i++){
		p_mSkillOne->PushSprite("Texture/skill/1/%d.png", i);
	}
	p_mSkillOne->SetPos(temp);
	PushScene(p_mSkillOne);
}


SkillOne::~SkillOne()
{
}

void SkillOne::Update(float eTime){
	ZeroIScene::Update(eTime);
	p_mSkillOne->Update(eTime);
	if (isWind){
		p_mSkillOne->AddPos(ZeroMathMgr->Cos(angle)*200*eTime, ZeroMathMgr->Sin(angle)*100*eTime);
		if ((p_mSkillOne->Pos().x + p_mSkillOne->Width() < 0) || (p_mSkillOne->Pos().x > 1333) || (p_mSkillOne->Pos().y > 750) || (p_mSkillOne->Pos().y + p_mSkillOne->Height() < 0)){
			this->SetErase(true);
			return;
		}
	}
	if (isThunder){
		time += eTime;
		if (time > 0.7){
			this->SetErase(true);
		}
	}
	if (isRained){
		p_mSkillOne->AddPosY(200 * eTime);
		if (p_mSkillOne->Pos().y > 750){
			this->SetErase(true);
			return;
		}
	}
	if (p_mSkillOne->CurrentFrame() == 4){ p_mSkillOne->Stop(); p_mSkillOne->SetCurrentFrame(4); }
	
}

void SkillOne::SetRain(bool _option){
	isRained = _option;
}

void SkillOne::SetWind(float angle){
	this->angle = angle;
	isWind = true;
}
void SkillOne::SetThunder(bool _option){
	isThunder = true;
	time = 0;
	return;
}
void SkillOne::Render(){
	p_mSkillOne->Render();
}