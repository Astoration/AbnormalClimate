#pragma once
#include "Zero.h"
class LoadingScene :
	public ZeroIScene
{
public:
	ZeroSprite* load;
	ZeroSprite* cursor;
	LoadingScene();
	virtual ~LoadingScene();
	void Update(float eTime);
	void Render();
};

