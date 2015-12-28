#include "stdafx.h"
#include "SelectStageScene.h"
#include "SelectScene.h"


SelectStageScene::SelectStageScene()
	:onNowStage(1), onMoveRight(false), onMoveLeft(false), moveValue(0), moves(0)
{
	for (int i = 0; i < 3; i++){
		Stage[i] = new SelectScene(i);
		Stage[i]->ChildSetPosX(1334 * i);
		PushScene(Stage[i]);
	}
	ZeroSoundMgr->Stop("title");
	ZeroSoundMgr->Stop("0bg");
	ZeroSoundMgr->Stop("1bg");
	ZeroSoundMgr->Stop("2bg");
	ZeroSoundMgr->Stop("boss");
	ZeroSoundMgr->Stop("over");
	ZeroSoundMgr->SetConcurrency(1, "s");
	ZeroSoundMgr->Play("s");
	cursor = new ZeroSprite("Texture/cursor.png");
}


SelectStageScene::~SelectStageScene()
{
}

void SelectStageScene::Update(float eTime){
	if (onMoveRight){
		if (moveValue < moves||moveValue<0){
			for (int i = 0; i < 3; i++)Stage[i]->ChildSetPosX(1334 * ((i + 1) - onNowStage));
			moveValue = 0;
			moves = 0;
			onMoveRight = false;
			return;
		}
		for (int i = 0; i < 3;i++)Stage[i]->ChildAddPosX(moves);
		moveValue += moves;
		moves += eTime*2;
	}
	if (onMoveLeft){
		if (moveValue < moves || moveValue<0){
			for (int i = 0; i < 3; i++)Stage[i]->ChildSetPosX(1334 * ((i+1) - onNowStage));
			moveValue = 0;
			moves = 0;
			onMoveLeft = false;
			return;
		}
		for (int i = 0; i < 3; i++)Stage[i]->ChildAddPosX(moves);
		moveValue -= moves;
		moves -= eTime*2;
	}
	if (ZeroInputMgr->GetKey(VK_LBUTTON) == INPUTMGR_KEYDOWN
		&&
		!(onMoveLeft||onMoveRight)
		){
		if (ZeroInputMgr->GetClientPoint().x > 1200&&onNowStage!=3){
			onMoveRight = true;
			moveValue = 1334;
			moves = -20*2;
			onNowStage++;
		}
		if (ZeroInputMgr->GetClientPoint().x < 150 && onNowStage != 1){
			onMoveLeft = true;
			moveValue = 1334;
			moves = 20*2;
			onNowStage--;
		}
	}
	Stage[onNowStage - 1]->Update(eTime);
	cursor->SetPos(ZeroInputMgr->GetClientPoint());
}

void SelectStageScene::Render(){
	for (int i = 0; i < 3; i++){
		Stage[i]->Render();
	}
	cursor->Render();
}