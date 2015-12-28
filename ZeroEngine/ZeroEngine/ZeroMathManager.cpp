#include "stdafx.h"
#include "ZeroMathManager.h"

#pragma warning(disable: 4996)

ZeroMathManager::ZeroMathManager() : MaxInt((std::numeric_limits<int>::max)()),
MaxDouble((std::numeric_limits<double>::max)()),
MinDouble((std::numeric_limits<double>::min)()),
MaxFloat((std::numeric_limits<float>::max)()),
MinFloat((std::numeric_limits<float>::min)()),
Pi(3.14159265359f) {

	for (int i = 0; i < 360; ++i) {
		sinTable[i] = sin(DegToRad(static_cast<float>(i)));
		cosTable[i] = cos(DegToRad(static_cast<float>(i)));
	}
}

ZeroMathManager::~ZeroMathManager() {

}

ZeroMathManager* ZeroMathManager::Instance() {
	static ZeroMathManager instance;
	return &instance;
}

int ZeroMathManager::RandInt(int _x, int _y) {
	return rand() % (_y - _x + 1) + _x;
}

float ZeroMathManager::RandFloat(float x, float y) {
	return x + (rand() / (RAND_MAX + 1.0f)) * (y - x);
}
