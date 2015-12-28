#pragma once
#include "SelectScene.h"
#include "Zero.h"
class SelectStageScene :
	public ZeroIScene
{
private:
	SelectScene *Stage[3];
	int onNowStage;
	ZeroSprite* cursor;
	bool onMoveRight, onMoveLeft;
	float moveValue, moves;
public:
	SelectStageScene();
	virtual ~SelectStageScene();
	void Update(float eTime);
	void Render();
};

