#include "stdafx.h"
#include "GameOverScene.h"
#include "InStageScene.h"
#include "StoryScene.h"
#include "SelectStageScene.h"


GameOverScene::GameOverScene(bool GameOverble, int stageKind,bool bossable, int time, int stage,int map[11][14],int tt)
{
	FILE *i, *o;

	for (int i = 0; i < 11; i++){
		for (int j = 0; j < 14; j++){
			this->map[i][j] = map[i][j];
		}
	}
	this->stageKind = stageKind;
	isStory = false;
	if (bossable)isStory = true;
	this->stage = stage;
	this->bossable = bossable;
	this->tt = tt;
	ZeroSoundMgr->Stop("title");
	ZeroSoundMgr->Stop("s");
	ZeroSoundMgr->Stop("0bg");
	ZeroSoundMgr->Stop("1bg");
	ZeroSoundMgr->Stop("2bg");
	ZeroSoundMgr->Stop("boss");
	ZeroSoundMgr->SetConcurrency(1, "over");
	ZeroSoundMgr->Play("over");
	bg = new ZeroSprite("Texture/bg/%d%s.png", stageKind, bossable ? "boss" : "");
	box = new ZeroSprite("Texture/gameover/kawai.png");
	box->SetPos(1334 / 2 - box->Width() / 2, 750 / 2.0 - box->Height() / 2);
	title = new ZeroFont(50, GameOverble ? "Game Over" : "Stage Clear");
	title->SetPos(box->Pos().x + 130, box->Pos().y + 80);
	title->SetColor(0xff989768);
	PushScene(bg);
	PushScene(box);
	PushScene(title);
	this->time = nullptr;
	button1 = nullptr;
	button2 = nullptr;
	button2 = new ZeroSprite("Texture/gameover/menu.png");
	if (!GameOverble){
		this->time = new ZeroFont(50, "");
		this->time->SetString("%d : %d", time / 60, time % 60);
		this->time->SetPos(title->Pos().x+50, title->Pos().y+200);
		this->time->SetColor(0xff989768);
		button2->SetPos(1334 / 2.0 - button2->Width() / 2, 500);
		char path[100];
		sprintf(path, "Texture/clear%d.dat", stageKind);
		i = fopen(path, "r");
		fscanf(i, "%s", &a);
		if (stage < 9){
			a[stage + 1] = '1';
		}
		else{
			if (stageKind < 2){
				sprintf(path, "Texture/clear%d.dat", stageKind + 1);
				i = fopen(path, "r");
				fscanf(i, "%s", &a);
				a[0] = '1';
			}
		}
		o = fopen(path, "w");
		fprintf(o, a);
		fclose(o);
		fclose(i);
	}
	else{
		button1 = new ZeroSprite("Texture/gameover/replay.png");
		button1->SetPos(550, 500);
		button2->SetPos(700, 500);
	}
	cursor = new ZeroSprite("Texture/cursor.png");
}


GameOverScene::~GameOverScene()
{
}

void GameOverScene::Update(float eTime){
	ZeroIScene::Update(eTime);
	if (ZeroInputMgr->GetKey(VK_LBUTTON)){
		if (button1 != nullptr){
			if (button1->IsOverlapped(ZeroInputMgr->GetClientPoint())){
				char str[100];
				sprintf(str, "%d", stageKind);
				ZeroSceneMgr->ChangeScene(new InStageScene(map, str, bossable, tt, stageKind, stage));
				return;
			}
		}
		if (button2->IsOverlapped(ZeroInputMgr->GetClientPoint())){
			if (isStory) ZeroSceneMgr->ChangeScene(new StoryScene());
			else ZeroSceneMgr->ChangeScene(new SelectStageScene());
			return;
		}
	}
	cursor->SetPos(ZeroInputMgr->GetClientPoint());
}

void GameOverScene::Render(){
	ZeroIScene::Render();
	bg->Render();
	box->Render();
	title->Render();
	if (time != nullptr)time->Render();
	if (button1 != nullptr)button1->Render();
	if (button2 != nullptr)button2->Render();
	cursor->Render();
}
