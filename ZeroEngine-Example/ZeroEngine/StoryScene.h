#pragma once
#include "Zero.h"
class StoryScene :
	public ZeroIScene
{
public:
	StoryScene();
	virtual ~StoryScene();
	ZeroSprite *story[4];
	bool Check[4];
	void Update(float eTime);
	void Render();
};

