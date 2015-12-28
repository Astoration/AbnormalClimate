#pragma once
#include "Zero.h"
class Dummys :
	public ZeroIScene
{
private:
	ZeroSprite *DummySprite;
	bool isMoving, isMovingVertical;
public:
	bool isClock;
	Dummys(int kind, int x, int y,char* BackgroundName);
	virtual ~Dummys();
	void Update(float eTime);
	void Render();
	ZeroSprite* getDummy(){ return DummySprite; }
};

