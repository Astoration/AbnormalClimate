#pragma once
#include "Zero.h"
class TitleScene :
	public ZeroIScene
{
private :
	ZeroSprite *bg, *bt, *cloud1, *cloud2, *reaf, *wind, *logo;
	ZeroSprite* cursor;

public:
	TitleScene();
	virtual ~TitleScene();
	void Update(float eTime);
	void Render();
};

