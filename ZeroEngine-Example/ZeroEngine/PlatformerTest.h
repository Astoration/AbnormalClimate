#pragma once
#include "Zero.h"

class PlatformerTest : public ZeroIScene {
private:
	//플레이어 캐릭터 애니메이션
	ZeroAnimation* m_PlyCharR;
	ZeroAnimation* m_PlyCharL;
	ZeroAnimation* m_PlyCharRunL;
	ZeroAnimation* m_PlyCharRunR;
	//배경.
	ZeroAnimation* m_BG;
public:
	PlatformerTest();
	~PlatformerTest();
	float xvel, yvel, maxspeed = 360;
	int lastdir = 1;
	bool isJumping = false;
	void Update(float eTime);
	void Render();
};