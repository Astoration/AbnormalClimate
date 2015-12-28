#include "stdafx.h"
#include "PlatformerTest.h"
#include "ZeroVec.h"
/*--------------------------------------------------------------------------------*/
//
//							생성자 부분에서 변수 초기화
//
/*--------------------------------------------------------------------------------*/
PlatformerTest::PlatformerTest() {
	//5.0f의 속도로 애니메이션을 한다.
	//수치가 높아질수록 빠름
	//1.0f일 경우 1초에 한장씩 애니메이션함
	//(그러면 5.0f일 경우는 1초에 5장넘어가겟죠)
	m_PlyCharR = new ZeroAnimation(8.0f);
	m_PlyCharL = new ZeroAnimation(8.0f);
	m_PlyCharRunL = new ZeroAnimation(15.0f);
	m_PlyCharRunR = new ZeroAnimation(15.0f);
	m_BG = new ZeroAnimation(1.0f);
	m_BG->Stop();
	m_BG->SetPos(0, 0);
	PushScene(m_BG);
	PushScene(m_PlyCharR);
	PushScene(m_PlyCharL);
	PushScene(m_PlyCharRunL);
	PushScene(m_PlyCharRunR);
	yvel = 0;
	xvel = 0;
	for (int i = 1; i <= 3; i++){
		m_PlyCharL->PushSprite("Texture/PlayerCharacter/idle/left/idle%d.png", i);
		m_PlyCharR->PushSprite("Texture/PlayerCharacter/idle/right/idle%d.png", i);
		m_BG->PushSprite("Texture/background_%d.png", i);
	}
	for (int i = 1; i <= 8; i++){
		m_PlyCharRunL->PushSprite("Texture/PlayerCharacter/run/left/run_%d.png", i);
		m_PlyCharRunR->PushSprite("Texture/PlayerCharacter/run/right/run_%d.png", i);
	}
}
/*--------------------------------------------------------------------------------*/
//
//										소멸자
//
/*--------------------------------------------------------------------------------*/
PlatformerTest::~PlatformerTest() {
}
/*--------------------------------------------------------------------------------*/
//
//							Update 함수에서는 기능을 검사
//
/*--------------------------------------------------------------------------------*/
void PlatformerTest::Update(float eTime) {
	ZeroIScene::Update(eTime);
	if (ZeroInputMgr->GetKey('D') == INPUTMGR_KEYON){
		if (xvel <= maxspeed)
		{
			xvel += 60;
		}
		lastdir = 1;
	}
	if (ZeroInputMgr->GetKey('A') == INPUTMGR_KEYON){
		if (xvel >= -maxspeed)
		{
			xvel -= 60;
		}
		lastdir = -1;
	}
	if (ZeroInputMgr->GetKey(VK_SPACE) == INPUTMGR_KEYDOWN  && isJumping == false){
		yvel = -600;
		isJumping = true;
	}
	if (ZeroInputMgr->GetKey('R') == INPUTMGR_KEYDOWN){
		int curframe = m_BG->CurrentFrame();
		switch (curframe){
			case 3:m_BG->SetFrame(1); break;
			default:m_BG->SetFrame(curframe + 1);
		}
	}
	m_PlyCharR->AddPosX(xvel * eTime);
	m_PlyCharR->AddPosY(yvel * eTime);
	m_PlyCharL->AddPosX(xvel * eTime);
	m_PlyCharL->AddPosY(yvel * eTime);
	m_PlyCharRunL->AddPosX(xvel * eTime);
	m_PlyCharRunL->AddPosY(yvel * eTime);
	m_PlyCharRunR->AddPosX(xvel * eTime);
	m_PlyCharRunR->AddPosY(yvel * eTime);
	if (xvel != 0){
		if (xvel>0)
		{
			xvel -= 20;
		}
		else if (xvel<0)
		{
			xvel += 20;
		}
	}
	if (isJumping == true)
	{
		yvel += 20;
	}
}
/*--------------------------------------------------------------------------------*/
//
//							Render함수에서는 그리기만 한다.
//
/*--------------------------------------------------------------------------------*/
void PlatformerTest::Render() {
	ZeroIScene::Render();
	m_BG->Render();
	if (xvel < 3 && xvel > -3 && !ZeroInputMgr->GetKey('D') && !ZeroInputMgr->GetKey('A'))
		switch (lastdir){
		case 1:
			m_PlyCharR->Render();
			break;
		case -1:
			m_PlyCharL->Render();
		}
	else if (xvel < 3)
		m_PlyCharRunL->Render();
	else 
		m_PlyCharRunR->Render();
}