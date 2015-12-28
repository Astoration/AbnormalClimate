#include "stdafx.h"
#include "Skill.h"
#include "SkillOne.h"
#include "Dummys.h"
#include <iostream>
#include "InStageScene.h"
#include <math.h>


Skill::Skill()
	:SkillKind(1), SkillActive(false), mana(50.0), eaterTime(0.0)
{
	OnePre = new ZeroSprite("Texture/skill/1/5.png");
	ThreePre = new ZeroSprite("Texture/skill/3/4.png");
	FourPre = new ZeroSprite("Texture/skill/4/4.png");
	OnePre->SetColorA(0xFF * 0.7);
	ThreePre->SetColorA(0xFF * 0.7);
	FourPre->SetColorA(0xFF * 0.7);
	FourEffect = new ZeroAnimation(10.0f);
	for (int i = 1; i <= 7; i++){
		FourEffect->PushSprite("Texture/skill/4/%d.png", i);
	}
	for (int i = 0; i <= 15; i++){
		FourEffect->PushSprite("Texture/skill/4/%d.png", (6 + (i % 2)));
	}
	TwoAfterEffect = new ZeroAnimation(6.0f);
	for (int i = 0; i <= 11; i++){
		TwoAfterEffect->PushSprite("Texture/skill/2/%d.png", (i % 4 + 1));
	}
	TwoAfterEffect->Stop();
	FourEffect->Stop();
	SkillTwoPoint = nullptr;
	TwoEffect = new ZeroLine();
	TwoEffect->SetLineWidth(5.0f);
	TwoEffect->SetColor(0xfff7e59c);
	SkillTwoPoint = new ZeroVec(ZeroInputMgr->GetClientPoint());
	anchor= new ZeroSprite("Texture/skill/2/anchor.png");
	ThreeAfterEffect = new ZeroAnimation(8.0f);
	for (int i = 1; i <= 7; i++) ThreeAfterEffect->PushSprite("Texture/skill/3/%d.png", i);
	for (int i = 0; i < 9; i++)ThreeAfterEffect->PushSprite("Texture/skill/3/%d.png", 5 + (i % 3));
	ThreeAfterEffect->Stop();
	TwoAfterEffect->SetRotCenter(TwoAfterEffect->Width() / 2, TwoAfterEffect->Height() / 2);
	SkillBox = new ZeroSprite("Texture/skill/interface/skillbox.png");
	SkillBox->SetPos(20, 20 + 73 *0.7+590);
	SkillBox->SetScale(0.7);
	SkillBox->SetColorA(0xa5);
	   OneBox= new ZeroSprite("Texture/skill/interface/cloud.png");
	  OnePush = new ZeroSprite("Texture/skill/interface/cloudpush.png");
	   TwoBox = new ZeroSprite("Texture/skill/interface/rain.png");
	  TwoPush = new ZeroSprite("Texture/skill/interface/rainpush.png");
	 ThreeBox = new ZeroSprite("Texture/skill/interface/thunder.png");
	ThreePush = new ZeroSprite("Texture/skill/interface/thunderpush.png");
	  FourBox = new ZeroSprite("Texture/skill/interface/wind.png");
	 FourPush = new ZeroSprite("Texture/skill/interface/windpush.png");
	    OneBox->SetScale(0.7);
	   OnePush->SetScale(0.7);
	    TwoBox->SetScale(0.7);
	   TwoPush->SetScale(0.7);
	  ThreeBox->SetScale(0.7);
	 ThreePush->SetScale(0.7);
	   FourBox->SetScale(0.7);
	  FourPush->SetScale(0.7);
	 OneBox->SetPos(   6+30*0.7, 30+73*0.7                       +588);
	 OnePush->SetPos(6 + 30 *0.7, 30 + 73 *0.7                 +588);
	 TwoBox->SetPos(6 + 35 *0.7 + 96 *0.7, 30 + 73 *0.7       +588);
	 TwoPush->SetPos(6 + 35 *0.7 + 96 *0.7, 30 + 73 *0.7      +588);
	 ThreeBox->SetPos(6 + 40 *0.7 + 96 *0.7 * 2, 30 + 73 *0.7 +588);
	 ThreePush->SetPos(6 + 40 *0.7 + 96 *0.7 * 2, 30 + 73 *0.7+588);
	 FourBox->SetPos(6 + 45 *0.7 + 96 *0.7 * 3, 30 + 73 *0.7  +588);
	 FourPush->SetPos(6 + 45 *0.7 + 96 *0.7 * 3, 30 + 73 *0.7 +588);
	    OneBox->SetColorA(0xa5);
	   OnePush->SetColorA(0xa5);
	    TwoBox->SetColorA(0xa5);
	   TwoPush->SetColorA(0xa5);
	  ThreeBox->SetColorA(0xa5);
	 ThreePush->SetColorA(0xa5);
	   FourBox->SetColorA(0xa5);
	  FourPush->SetColorA(0xa5);
	  MpBox = new ZeroSprite("Texture/skill/interface/box.png");
	  MpBox->SetPos(20, 20+590);
	  MpBox->SetColorA(0xa5);
	  MpBox->SetScale(0.7);
	  Mp = new ZeroSprite("Texture/skill/interface/mp.png");
	  Mp->SetPos(54, 29+587);
	  Mp->SetColorA(0xa5);
}


Skill::~Skill()
{
}

void Skill::AllRender(){
		for (NODE::iterator iter = m_Node.begin(); iter != m_Node.end(); ++iter) {
				(*iter)->Render();
			if ((*iter)->IsErase()) {
				SAFE_DELETE(*iter);
				iter = m_Node.erase(iter);
				if (iter == m_Node.end()) break;
			}
		}
}

void Skill::AllCheck(Player *m_Player){
	for (NODE::iterator iter = m_Node.begin(); iter != m_Node.end(); ++iter) {
		if ((*iter) == OnePre || (*iter) == FourPre) continue;
		ZeroAnimation *tile = ((SkillOne*)(*iter))->GetCloud();
		if ((tile->Pos().x < m_Player->mGetPos().x + m_Player->mGetWidth() / 2) && (tile->Pos().x + tile->Width() > m_Player->mGetPos().x + m_Player->mGetWidth() / 2)){
			if ((tile->Pos().y+50<m_Player->mGetPos().y + m_Player->mGetHeight()) && (tile->Pos().y + 80>m_Player->mGetPos().y + m_Player->mGetHeight())){
				m_Player->mSetPosY(tile->Pos().y+50 - m_Player->mGetHeight());
				m_Player->mSetGravity(0);
				m_Player->mSetDown(false);
			}
		}
		if ((*iter)->IsErase()) {
			SAFE_DELETE(*iter);
			iter = m_Node.erase(iter);
			if (iter == m_Node.end()) break;
		}
	}
}

void Skill::Update(float eTime){
	if (ZeroInputMgr->GetKey(VK_LBUTTON)==INPUTMGR_KEYDOWN&&(!SkillActive)){
		SkillActive = true;
		if (SkillKind == 2){
			SkillTwoPoint->x = ZeroInputMgr->GetClientPoint().x;
			SkillTwoPoint->y = ZeroInputMgr->GetClientPoint().y;
			TwoEffect->ClearPoint();
			TwoEffect->PushBackPoint(2, ZeroVec(SkillTwoPoint->x, SkillTwoPoint->y), ZeroVec(ZeroInputMgr->GetClientPoint().x, ZeroInputMgr->GetClientPoint().y));

		}
		return;
	}

	ZeroIScene::Update(eTime);
	eaterTime += eTime;
	if (eaterTime > 1){
		eaterTime = 0;
		mana += 1.5;
		if (mana > 100)mana = 100;
	}
	Mp->SetScale(mana / 100.0,1.0);
	FourEffect->Update(eTime);
	if (FourEffect->IsRunning()&&FourEffect->CurrentFrame()==22){
		FourEffect->Stop();
		FourEffect->SetCurrentFrame(0);
	}
	TwoAfterEffect->Update(eTime);
	if (TwoAfterEffect->IsRunning() && TwoAfterEffect->CurrentFrame() == 11){
		TwoAfterEffect->Stop();
		TwoAfterEffect->SetCurrentFrame(0);
	}
	ThreeAfterEffect->Update(eTime);
	if (ThreeAfterEffect->IsRunning() && ThreeAfterEffect->CurrentFrame() == 15){
		ThreeAfterEffect->Stop();
		ThreeAfterEffect->SetCurrentFrame(0);
	}
	if (SkillActive){ 
		float dx, dy, angle;
		if (ZeroInputMgr->GetKey(VK_RBUTTON) == INPUTMGR_KEYDOWN){ SkillActive = false; return; }
		switch (SkillKind)
		{
		case 1:
			OnePre->SetPos(ZeroInputMgr->GetClientPoint().x - OnePre->Width() / 2, ZeroInputMgr->GetClientPoint().y-50);
			break;
		case 2:
			TwoEffect->ClearPoint();
			TwoEffect->PushBackPoint(2, ZeroVec(SkillTwoPoint->x, SkillTwoPoint->y), ZeroVec(ZeroInputMgr->GetClientPoint().x, ZeroInputMgr->GetClientPoint().y));
			cout << "sk :" << SkillTwoPoint->x << "," << SkillTwoPoint->y << endl << "point :" << ZeroInputMgr->GetClientPoint().x << "," << ZeroInputMgr->GetClientPoint().y << endl;
			dy= ZeroInputMgr->GetClientPoint().y-SkillTwoPoint->y;
			dx = ZeroInputMgr->GetClientPoint().x-SkillTwoPoint->x;;
			angle = atan(dy/dx)*(180.0/ZeroMathMgr->Pi);
			if (dx<0.0) angle+=180.0;
			else if(dy<0.0) angle+=360.0;
			anchor->SetPos(ZeroInputMgr->GetClientPoint());
			anchor->SetRot(angle+135);
			break;
		case 3:
			ThreePre->SetPos(ZeroInputMgr->GetClientPoint().x - ThreePre->Width() / 2, ZeroInputMgr->GetClientPoint().y - 50);
			break;
		case 4:
			FourPre->SetPos(ZeroInputMgr->GetClientPoint().x - FourPre->Width() / 2, ZeroInputMgr->GetClientPoint().y - 50);
			break;
		}
		if (ZeroInputMgr->GetKey(VK_LBUTTON) == INPUTMGR_KEYDOWN){
			SkillOne* temp;
			float skWidth, skHeight;
			ZeroVec *SkPos;
			InStageScene *tpP;
			switch (SkillKind){
			case 1:
				if (mana < 10)break;
				temp = new SkillOne(OnePre->Pos());
				PushScene((ZeroIScene*)temp);
				SkillActive = false;
				// 시연용 mana -= 10;
				break;
			case 2:
				if (mana < 40)break;
				// 시연용 mana -= 40;
				RECT SkillRect;
				SkillRect.left = (ZeroInputMgr->GetClientPoint().x < SkillTwoPoint->x) ? ZeroInputMgr->GetClientPoint().x : SkillTwoPoint->x;
				SkillRect.right = (ZeroInputMgr->GetClientPoint().x > SkillTwoPoint->x) ? ZeroInputMgr->GetClientPoint().x : SkillTwoPoint->x;
				SkillRect.top = (ZeroInputMgr->GetClientPoint().y < SkillTwoPoint->y) ? ZeroInputMgr->GetClientPoint().y : SkillTwoPoint->y;
				SkillRect.bottom = (ZeroInputMgr->GetClientPoint().y > SkillTwoPoint->y) ? ZeroInputMgr->GetClientPoint().y : SkillTwoPoint->y;

				for (NODE::iterator iter = m_Node.begin(); iter != m_Node.end(); ++iter) {
					if ((*iter) == OnePre || (*iter) == TwoPre || (*iter) == ThreePre || (*iter) == FourEffect || (*iter) == TwoAfterEffect || (*iter) == TwoEffect || (*iter) == ThreeAfterEffect || (*iter) == FourPre) continue;
					SkillOne *temp = (SkillOne*)(*iter);
					ZeroVec *tempPos = new ZeroVec((temp)->GetCloud()->Pos().x, (temp)->GetCloud()->Pos().y);
					float tempWidth = (temp)->GetCloud()->Width();
					float tempHeight = (temp)->GetCloud()->Height();
					RECT TempRect, answerRect;
					TempRect.top = tempPos->y;
					TempRect.left = tempPos->x;
					TempRect.right = tempPos->x + tempWidth;
					TempRect.bottom = tempPos->y + tempHeight;
					if (IntersectRect(&answerRect,&SkillRect,&TempRect)){
							SkillOne *tempThis = (SkillOne*)(*iter);
							tempThis->SetWind(angle);
					}
					if ((*iter)->IsErase()) {
						SAFE_DELETE(*iter);
						iter = m_Node.erase(iter);
						if (iter == m_Node.end()) break;
					}
				}
				TwoAfterEffect->SetPos((*SkillTwoPoint));
				TwoAfterEffect->AddPos(-400, -200);
				TwoAfterEffect->SetRot(angle);
				TwoAfterEffect->Start();
				SkillActive = false;
				break;
			case 3:
				if (mana < 20)break;
				// 시연용 mana -= 20;
				SkPos = new ZeroVec(ThreePre->Pos().x, ThreePre->Pos().y);
				skWidth = ThreePre->Width();
				skHeight = ThreePre->Height();
				tpP = (InStageScene*)this->Parent();
				for (int i = 0; i < 11; i++){
					for (int j = 0; j < 14; j++){
						ZeroIScene* tpTile = tpP->tile[i][j];
						if (tpTile == nullptr) continue;
						ZeroVec tempPos = tpTile->Pos();
						float tempWidth = tpTile->Width();
						float tempHeight = tpTile->Height();
						if (tempPos.x == 0){
							if (((Dummys*)tpTile)->isClock)continue;
							tpTile = ((Dummys*)tpTile)->getDummy();
							tempPos = tpTile->Pos();
							tempWidth = tpTile->Width();
							tempHeight = tpTile->Height();
						}
						if ((SkPos->x<tempPos.x + tempWidth) && (SkPos->x + skWidth>tempPos.x)){
							if ((SkPos->y<tempPos.y + tempHeight) && (SkPos->y + skHeight>tempPos.y)){
								tpP->SetThunder(i, j);
							}
						}
					}
				}
				for (int i = 0; i < 5; i++){
					for (NODE::iterator iter = m_Node.begin(); iter != m_Node.end(); ++iter) {
						if ((*iter) == OnePre || (*iter) == TwoPre || (*iter) == ThreePre || (*iter) == FourEffect || (*iter) == TwoAfterEffect || (*iter) == TwoEffect || (*iter) == ThreeAfterEffect || (*iter) == FourPre) continue;
						SkillOne *temp = (SkillOne*)(*iter);
						ZeroVec *tempPos = new ZeroVec((temp)->GetCloud()->Pos().x, (temp)->GetCloud()->Pos().y);
						float tempWidth = (temp)->GetCloud()->Width();
						float tempHeight = (temp)->GetCloud()->Height();
						if (
							(
							(SkPos->x)
							<
							(tempPos->x + tempWidth)
							)
							&&
							(
							(SkPos->x + skWidth)
							>
							(tempPos->x)
							)
							){
							if (
								(
								SkPos->y
								<
								tempPos->y + tempHeight
								)
								&&
								(
								SkPos->y + skHeight
								>
								tempPos->y
								)
								){
								SkillOne *tempThis = (SkillOne*)(*iter);
								tempThis->SetThunder(true);
							}
						}
						if ((*iter)->IsErase()) {
							SAFE_DELETE(*iter);
							iter = m_Node.erase(iter);
							if (iter == m_Node.end()) break;
						}
					}
				}
				ThreeAfterEffect->SetPos(ThreePre->Pos());
				ThreeAfterEffect->Start();
				SkillActive = false;
				break;
			case 4:
				if (mana < 20)break;
				// 시연용 mana -= 20;
				ZeroVec *SkPos = new ZeroVec(FourPre->Pos().x, FourPre->Pos().y);
				float skWidth = FourPre->Width();
				float skHeight = FourPre->Height();
				for (NODE::iterator iter = m_Node.begin(); iter != m_Node.end(); ++iter) {
					if ((*iter) == OnePre || (*iter) == TwoPre || (*iter) == ThreePre || (*iter) == FourEffect || (*iter) == TwoAfterEffect || (*iter) == TwoEffect || (*iter) == ThreeAfterEffect || (*iter) == FourPre) continue;
					SkillOne *temp = (SkillOne*)(*iter);
					ZeroVec *tempPos = new ZeroVec((temp)->GetCloud()->Pos().x, (temp)->GetCloud()->Pos().y);
					float tempWidth = (temp)->GetCloud()->Width();
					float tempHeight = (temp)->GetCloud()->Height();
					if (
						(
							(SkPos->x)
							<
							(tempPos->x + tempWidth)
						)
						&&
						(
							(SkPos->x + skWidth)
							>
							(tempPos->x)
						)
					){
						if (
								(
									SkPos->y
									<
									tempPos->y + tempHeight
								)
								&&
								(
									SkPos->y + skHeight 
									>
									tempPos->y
								)
						){
							SkillOne *tempThis = (SkillOne*)(*iter);
							tempThis->SetRain(true);
						}
					}
					if ((*iter)->IsErase()) {
						SAFE_DELETE(*iter);
						iter = m_Node.erase(iter);
						if (iter == m_Node.end()) break;
					}
				}
				FourEffect->SetPos(FourPre->Pos());
				FourEffect->Start();
				SkillActive = false;
				break;
			}
		}
	}

}

void Skill::Render(){
	AllRender();
	if (SkillActive){
		switch (SkillKind){
		case 1:
			OnePre->Render();
			break;
		case 2:
			TwoEffect->Render();
			anchor->Render();
			break;
		case 3:
			ThreePre->Render();
			break;
		case 4:
			FourPre->Render();
			break;
		}
	}
	if (FourEffect->IsRunning())FourEffect->Render();
	if (TwoAfterEffect->IsRunning()) TwoAfterEffect->Render();
	if (ThreeAfterEffect->IsRunning())ThreeAfterEffect->Render();
	SkillBox->Render();
	if (SkillKind == 1) OnePush->Render(); else OneBox->Render();
	if (SkillKind == 4) TwoPush->Render(); else TwoBox->Render();
	if (SkillKind == 3) ThreePush->Render(); else ThreeBox->Render();
	if (SkillKind == 2) FourPush->Render(); else FourBox->Render();
	MpBox->Render();
	Mp->Render();
}