#include "stdafx.h"
#include "TitleScene.h"
#include "SelectStageScene.h"

TitleScene::TitleScene()
{
	bg = new ZeroSprite("Texture/title/background.png");
	bt = new ZeroSprite("Texture/title/start.png");
	cloud1 = new ZeroSprite("Texture/title/cloud1.png");
	cloud2 = new ZeroSprite("Texture/title/cloud2.png");
	cloud1->SetPosY(750 - cloud1->Height());
	cloud2->SetPosY(750 - cloud2->Height());
	reaf = new ZeroSprite("Texture/title/reaf.png");
	wind = new ZeroSprite("Texture/title/wind.png");
	bt->SetPos(708, 500);
	reaf->SetRotCenter(1334 / 2, 750 / 2);
	reaf->SetScale(1.2);
	wind->SetScalingCenter(1334 / 2, 750 / 2);
	ZeroSoundMgr->PushSound("Sound/gameover.mp3", "over");
	ZeroSoundMgr->PushSound("Sound/select.mp3", "s");
	ZeroSoundMgr->PushSound("Sound/0bg.mp3", "0bg");
	ZeroSoundMgr->PushSound("Sound/1bg.mp3", "1bg");
	ZeroSoundMgr->PushSound("Sound/2bg.mp3", "2bg");
	ZeroSoundMgr->PushSound("Sound/boss.mp3", "boss");
	ZeroSoundMgr->PushSound("Sound/title.mp3", "title");
	ZeroSoundMgr->SetConcurrency(1, "title");
	ZeroSoundMgr->Play("title");
	cursor = new ZeroSprite("Texture/cursor.png");
	cloud1->SetScalingCenter(cloud1->Width() / 2.0, cloud1->Height() / 2.0);
	cloud2->SetScalingCenter(cloud2->Width() / 2.0, cloud2->Height() / 2.0);
	cloud1->SetScale(1.3);
	cloud2->SetScale(1.3);
	logo = new ZeroSprite("Texture/title/main_logo.png");
	logo->SetPos(625, 55);
	
}


TitleScene::~TitleScene()
{
}

void TitleScene::Update(float eTime){
	ZeroIScene::Update(eTime);
	if (ZeroInputMgr->GetKey(VK_LBUTTON) == INPUTMGR_KEYDOWN){
		if (bt->IsOverlapped(ZeroInputMgr->GetClientPoint())){
			ZeroSceneMgr->ChangeScene(new SelectStageScene());
		}
	}
	cloud1->SetPosX(0 + ZeroMathMgr->Sin(ZeroMathMgr->Pi * 60 * StartToCurrentTime()*0.5) * 50);
	cloud2->SetPosX(0 + ZeroMathMgr->Cos(ZeroMathMgr->Pi * 60 * StartToCurrentTime()*0.5) * 50);
	reaf->SetRot(0 + ZeroMathMgr->Sin(ZeroMathMgr->Pi * 60 * StartToCurrentTime()*0.5) * 20);
	wind->SetScale(1.2 + ZeroMathMgr->Sin(ZeroMathMgr->Pi * 60 * StartToCurrentTime()*0.5) * 0.1);
	cursor->SetPos(ZeroInputMgr->GetClientPoint());

}

void TitleScene::Render(){
		bg->Render();
		cloud1->Render();
		cloud2->Render();
		wind->Render();
		reaf->Render();
	bt->Render();
	logo->Render();
	cursor->Render();
}