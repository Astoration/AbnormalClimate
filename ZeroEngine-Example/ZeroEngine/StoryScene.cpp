#include "stdafx.h"
#include "SelectStageScene.h"
#include "StoryScene.h"


StoryScene::StoryScene()
{
	for (int i = 0; i < 4; i++){
		Check[i] = false;
	}
	Check[0] = true;
	story[0] = new ZeroSprite("Texture/story/a.png");
	story[1] = new ZeroSprite("Texture/story/b.png");
	story[2] = new ZeroSprite("Texture/story/c.png");
	story[3] = new ZeroSprite("Texture/story/d.png");

}


StoryScene::~StoryScene()
{

}

void StoryScene::Update(float eTime){
	if (ZeroInputMgr->GetKey(VK_SPACE) == INPUTMGR_KEYDOWN || ZeroInputMgr->GetKey(VK_LBUTTON) == INPUTMGR_KEYDOWN){
		if (Check[1] == false)Check[1] = true;
		else if (Check[2] == false)Check[2] = true;
		else if (Check[3] == false)Check[3] = true;
		else ZeroSceneMgr->ChangeScene(new SelectStageScene(),TR::Fade);
	}
}

void StoryScene::Render(){
	for (int i = 0; i < 4; i++){
		if (Check[i]) story[i]->Render();
	}
}