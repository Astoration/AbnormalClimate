#include "stdafx.h"
#include "Dummys.h"
#include "InStageScene.h"
#include "Player.h"
#include <iostream>


Dummys::Dummys(int kind, int x, int y,char* bgName)
	:isMoving(false), isClock(false), isMovingVertical(false)
{
	if (kind == 2){
		DummySprite = new ZeroSprite("Texture/Object/mold.png");
		isMovingVertical = true;
	}
	else if (kind == 1){
		DummySprite = new ZeroSprite("Texture/Object/mold.png");
		isMoving = true;
	}
	else if(kind==0){
		DummySprite = new ZeroSprite("Texture/Object/%s_dis.png",bgName);
	}
	else{
		DummySprite = new ZeroSprite("Texture/Object/%s_clock.png",bgName);
		isClock = true;
		DummySprite->SetRotCenter(DummySprite->Width() / 2.0f, DummySprite->Height() / 2.0f);
	}
	DummySprite->SetPos(97 * x+10, 66 * y + 30 - (DummySprite->Height()-66));
	if (kind != 1)DummySprite->AddPosY(5);
	PushScene(DummySprite);
}


Dummys::~Dummys()
{
}

void Dummys::Update(float eTime){
	ZeroIScene::Update(eTime);
	if (DummySprite == nullptr)this->SetErase(true);
	if (isMoving){
		DummySprite->AddPosX(ZeroMathMgr->Sin(this->StartToCurrentTime()*50)*1.5);
	}
	if (isMovingVertical){
		DummySprite->AddPosY(ZeroMathMgr->Sin(this->StartToCurrentTime() * 50)*1.5);
	}
	if (isClock){
		DummySprite->AddRot(ZeroMathMgr->Sin(this->StartToCurrentTime() *2)*1.5);
	}
	InStageScene *m_p = (InStageScene*)this->Parent();
	Player* m_Player = m_p->GetPlayer();
	ZeroVec pPos = m_Player->mGetPos();
	float pWidth = m_Player->mGetWidth(), pHeight = m_Player->mGetHeight();
	ZeroVec dPos = DummySprite->Pos();
	float dWidth = DummySprite->Width(), dHeight = DummySprite->Height();
	if (dPos.x<pPos.x + pWidth&&dPos.x + dWidth>pPos.x){
		if (dPos.y<pPos.y + pHeight&&dPos.y + dHeight>pPos.y){
			if(!m_Player->isNuckBack()&&!isClock)m_Player->SetNuckBack(true);
			if (isClock){
				m_p->ClockCount--;
				this->SetErase(true);
			}
		}
	}
}

void Dummys::Render(){
	DummySprite->Render();
}