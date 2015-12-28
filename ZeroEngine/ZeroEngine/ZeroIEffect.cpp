#include "stdafx.h"
#include "ZeroIEffect.h"
#include "ZeroEffectManager.h"

#pragma warning(disable: 4996)

ZeroIEffect::ZeroIEffect() {
	renderPage = 0;
}

ZeroIEffect::~ZeroIEffect() {

}

void ZeroIEffect::Update(float _eTime) {
	ZeroIScene::Update(_eTime);
}

void ZeroIEffect::Render() {
	ZeroIScene::Render();
}

int ZeroIEffect::RenderPage() const {
	return renderPage;
}
