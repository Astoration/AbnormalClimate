#include "stdafx.h"
#include "Player.h"
#include <Windows.h>
#define PLAYERS for (int i = 0; i < 3; i++)


Player::Player()
	:Run(false), Jump(false), gravity(100), JumpPWD(0), Down(false), NuckBack(false)
{
	for (int i = 0; i < 2; i++){
		m_pPlayer[i] = new ZeroAnimation(i ? 8.0f : 15.0f);
		char* path=i ? "Texture/player/stop/%d.png" : "Texture/player/run/%d.png";
		for (int j = 1; j <= (i ? 3 : 8); j++)
			m_pPlayer[i]->PushSprite(path, j);
		m_pPlayer[i]->SetScalingCenter(m_pPlayer[i]->Width() / 2,0);
		PushScene(m_pPlayer[i]);
	}
	m_pPlayer[2] = new ZeroAnimation(2.0f);
	for (int i = 1; i <= 3; i++) {
		m_pPlayer[2]->PushSprite("Texture/player/jump/%d.png", i);
	}
	m_pPlayer[2]->SetScalingCenter(m_pPlayer[2]->Width() / 2, 0);
	PushScene(m_pPlayer[2]);
}


Player::~Player()
{
}

void Player::Update(float eTime){
	Run = false;
	if (isNuckBack()){
		NuckPWD -= 30;
		int sign = m_pPlayer[0]->Scale().x;
		PLAYERS m_pPlayer[i]->AddPosX(sign*NuckPWD*eTime);
		PLAYERS m_pPlayer[i]->SetColorA(0xff - ZeroMathMgr->Sin(m_pPlayer[0]->StartToCurrentTime() * 3000) * 200);
		if (NuckPWD < 0){
			NuckPWD = 0;
			PLAYERS m_pPlayer[i]->SetColorA(0xff);
			NuckBack = false;
		}
	}
	if (isJump()){
		JumpPWD -= 30;
		if (JumpPWD < 0){
			JumpPWD = 0;
			Jump = false;
			Down = true;

		}
		PLAYERS m_pPlayer[i]->AddPosY(-1*JumpPWD*eTime);
	}
	else{
		gravity += 30;
		PLAYERS m_pPlayer[i]->AddPosY(gravity*eTime);
	}
	if (ZeroInputMgr->GetKey('A') == INPUTMGR_KEYON&&!isNuckBack()){
		PLAYERS m_pPlayer[i]->SetScale(1.0, 1.0);
		PLAYERS m_pPlayer[i]->AddPosX(-600 * eTime);
		Run = true;
	}
	else if (ZeroInputMgr->GetKey('D') == INPUTMGR_KEYON&&!isNuckBack()){
		PLAYERS m_pPlayer[i]->SetScale(-1.0, 1.0);
		PLAYERS m_pPlayer[i]->AddPosX(600 * eTime);
		Run = true;
	}
	if (!isNuckBack()&&ZeroInputMgr->GetKey('W') == INPUTMGR_KEYDOWN&&(!isJump()&&!isDown())){
		Jump = true;
		JumpPWD = 600;
	}
	PLAYERS m_pPlayer[i]->Update(eTime);
}

void Player::mSetPosY(float y){
	PLAYERS m_pPlayer[i]->SetPosY(y);
}
void Player::mSetPos(float x,float y){
	PLAYERS m_pPlayer[i]->SetPos(x,y);
}
void Player::Render(){
	if (!isJump()&&!isDown()){
		if (isRun()) m_pPlayer[0]->Render();
		else m_pPlayer[1]->Render();
	}
	else{
		m_pPlayer[2]->Render();
	}

}