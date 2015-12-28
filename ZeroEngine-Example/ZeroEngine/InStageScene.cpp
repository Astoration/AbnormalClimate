#include "stdafx.h"
#include "GameOverScene.h"
#include "InStageScene.h"
#include "Dummys.h"
#include <iostream>

using namespace std;
InStageScene::InStageScene(int map[11][14],char* BackgroundName,bool isBoss, float _t, int _stageKind, int _stage)
	:ThunderTime(0), ClockCount(0)
{
	for (int i = 0; i < 11; i++){
		for (int j = 0; j < 14; j++){
			this->map[i][j] = map[i][j];
		}
	}
	tt = _t;
	stagekind = _stageKind;
	stage = _stage;
	bossable = isBoss;
	ZeroSoundMgr->Stop("over");
	ZeroSoundMgr->Stop("title");
	ZeroSoundMgr->Stop("s");
	char stageStr[100];
	sprintf(stageStr, isBoss ? "boss%s" : "%sbg", isBoss ? "": BackgroundName);
	ZeroSoundMgr->Play(stageStr);
	bg = new ZeroSprite("Texture/bg/%s%s.png", BackgroundName,isBoss?"boss":"");
	m_Player = new Player();
	PushScene(m_Player);
	m_Player->mSetPos(200, 200);
	for (int j = 0; j < 14; j++){
		for (int i = 0; i < 11; i++) {
			Thunder[i][j] = false;
			if (map[i][j] == -1) {
				tile[i][j] = nullptr;
				continue;
			}
			if (map[i][j] == 25){
				tile[i][j] = nullptr;
				m_Player->mSetPos(97 * j, 66 * i + 30 - m_Player->mGetHeight());
				continue;
			}
			if (map[i][j] == 49){
				tile[i][j] = new Dummys(2, j, i, BackgroundName);
				PushScene(tile[i][j]);
				continue;
			}
			if (map[i][j] == 50){
				tile[i][j] = new Dummys(1, j, i, BackgroundName);
				PushScene(tile[i][j]);
				continue;
			}
			if (map[i][j] == 51){
				tile[i][j] = new Dummys(0, j, i, BackgroundName);
				PushScene(tile[i][j]);
				continue;
			}
			if (map[i][j] == 52){
				tile[i][j] = new Dummys(-1, j, i, BackgroundName);
				ClockCount++;
				PushScene(tile[i][j]);
				continue;
			}
			tile[i][j] = new ZeroSprite("Texture/tile/%s_%d.png",BackgroundName,map[i][j]);
			tile[i][j]->SetPos(97*j, 66*i+30);
			PushScene(tile[i][j]);
		}
	}
	skill = new Skill();
	skill->SetParent(this);
	timeInterface = new ZeroSprite("Texture/time/time.png");
	timeInterface->SetPos(1333 / 2.0 - 195 / 2.0, 20);
	timeInterface->SetColorA(0xa5);
	timeFont = new ZeroFont(50, "");
	timeFont->SetColor(0xa5947c37);
	timeFont->SetPos(1333 / 2.0 - 195 / 2.0+50, 90);
	limitTime = _t;
	cursor = new ZeroSprite("Texture/cursor.png");
}	
//#947c37
//14*12
InStageScene::~InStageScene()
{
}

void InStageScene::SetThunder(int i, int j){
	Thunder[i][j] = true;
	ThunderTime = 0;
}

void InStageScene::Update(float eTime) {
	bg->Update(eTime);
	if (ZeroInputMgr->GetKey('P') == INPUTMGR_KEYDOWN) ClockCount = 0;
	if (ClockCount == 0){ 
		ZeroSceneMgr->ChangeScene(new GameOverScene(false, stagekind, this->bossable, (int)limitTime, stage,map,tt));
		return;
	}
	limitTime -= eTime;
	timeFont->SetString("%d : %d", ((int)limitTime) / 60, ((int)limitTime) % 60);
	ThunderTime += eTime;
	for (int i = 0; i < 11; i++){
		for (int j = 0; j < 14; j++){
			if (Thunder[i][j]&&ThunderTime>0.7){
				Thunder[i][j] = false;
				tile[i][j]->SetErase(true);
				tile[i][j] = nullptr;
			}
		}
	}
	if (ZeroInputMgr->GetKey('1') == INPUTMGR_KEYDOWN) skill->SetSkillKind(1);
	else if(ZeroInputMgr->GetKey('4') == INPUTMGR_KEYDOWN) skill->SetSkillKind(2);
	else if (ZeroInputMgr->GetKey('3') == INPUTMGR_KEYDOWN) skill->SetSkillKind(3);
	else if (ZeroInputMgr->GetKey('2') == INPUTMGR_KEYDOWN) skill->SetSkillKind(4);
	skill->Update(eTime);
	m_Player->Update(eTime);
	for (int j = 0; j < 14; j++){
		for (int i = 0; i < 11; i++){
			if (tile[i][j] == nullptr)continue;
			tile[i][j]->Update(eTime);
			if (tile[i][j]->IsErase()){
				PopScene(tile[i][j],true);
				tile[i][j] = nullptr;
				continue;
			}
			if ((tile[i][j]->Pos().x < m_Player->mGetPos().x + m_Player->mGetWidth()/2) && (tile[i][j]->Pos().x + tile[i][j]->Width() > m_Player->mGetPos().x+m_Player->mGetWidth()/2)){
				if ((tile[i][j]->Pos().y<m_Player->mGetPos().y + m_Player->mGetHeight()) && (tile[i][j]->Pos().y + 30>m_Player->mGetPos().y + m_Player->mGetHeight())){
					m_Player->mSetPosY(tile[i][j]->Pos().y - m_Player->mGetHeight());
					m_Player->mSetGravity(0);
					m_Player->mSetDown(false);
				}
			}
		}
	}
	skill->AllCheck(m_Player);
	if (limitTime < 0 || m_Player->mGetPos().y>750){
		ZeroSceneMgr->ChangeScene(new GameOverScene(true, stagekind, bossable, limitTime, stage,map,tt));
	}
	cursor->SetPos(ZeroInputMgr->GetClientPoint());
}

void InStageScene::Render() {
	bg->Render();
	for (int j = 0; j < 14; j++){
		for (int i = 0; i < 11; i++){
			if (tile[i][j] == nullptr)continue;
			tile[i][j]->Render();
		}
	}
	m_Player->Render();
	skill->Render();
	timeInterface->Render();
	timeFont->Render();
	cursor->Render();
}