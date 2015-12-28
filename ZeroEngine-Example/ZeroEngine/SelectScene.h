#pragma once
#include "Zero.h"
#include <iostream>
using namespace std;
class SelectScene :
	public ZeroIScene
{
private:
	ZeroSprite *Background;
	ZeroSprite *Stages[10];
	char clearCharData[10];
	int kind;
public:
	SelectScene(int kind);
	virtual ~SelectScene();
	void Update(float eTime);
	void Render();
	void ChildSetPosX(float x);
	void ChildAddPosX(float x);
	void GetThisPosX(){ cout << Background->Pos().x << endl; };
};

