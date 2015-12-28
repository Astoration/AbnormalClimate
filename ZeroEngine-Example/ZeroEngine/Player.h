#pragma once
#include "Zero.h"
class Player :
	public ZeroIScene
{
private:
	ZeroAnimation* m_pPlayer[3];
	bool Run, Jump, Down, NuckBack;
	int gravity, JumpPWD, NuckPWD;
public:
	Player();
	virtual ~Player();
	void Update(float eTime);
	void Render();
	bool isRun(){ return Run; };
	bool isJump(){ return Jump; };
	bool isDown(){ return Down; };
	void mSetPosY(float y);
	void mSetPos(float x, float y);
	ZeroVec mGetPos(){ return m_pPlayer[1]->Pos(); }
	float mGetHeight(){ return m_pPlayer[1]->Height(); }
	float mGetWidth(){ return m_pPlayer[1]->Width(); }
	void mSetGravity(int tmp){ gravity = tmp; }
	void mSetDown(bool down){ Down = down; };
	bool isNuckBack(){ return NuckBack; }
	void SetNuckBack(bool _option){ this->NuckBack = _option; NuckPWD = 600; }
};

