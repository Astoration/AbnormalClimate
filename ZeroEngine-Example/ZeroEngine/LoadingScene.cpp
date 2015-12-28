#include "stdafx.h"
#include "LoadingScene.h"

#include "TitleScene.h"
LoadingScene::LoadingScene()
{
	load = new ZeroSprite("Texture/loading.png");
	cursor = new ZeroSprite("Texture/cursor.png");
}


LoadingScene::~LoadingScene()
{
}

void LoadingScene::Update(float eTime){
	cursor->SetPos(ZeroInputMgr->GetClientPoint());
}

void LoadingScene::Render(){
	load->Render();
	ZeroSceneMgr->ChangeScene(new TitleScene(), TR::DropFade, 10.0f);
	cursor->Render();
}