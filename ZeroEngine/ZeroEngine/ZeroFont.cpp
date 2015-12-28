#include "stdafx.h"
#include "ZeroFont.h"
#include "ZeroApplication.h"

#pragma warning(disable: 4996)

ZeroFont::ZeroFont(UINT _fontSize, char* _string, char* _fontName, char *_fileName)
	: fontSize(_fontSize), content(_string), fontName(_fontName), fontWeight(400) {
	m_Color = D3DCOLOR_ARGB(255, 0, 0, 0);

	if (_fileName != NULL) {
		AddFontResourceExA(_fileName, FR_NOT_ENUM, NULL);
	}
	D3DXCreateFontA(ZeroApp->GetDevice(), static_cast<UINT>(_fontSize), 0, fontWeight, D3DX_DEFAULT, NULL, 
		DEFAULT_CHARSET, OUT_TT_PRECIS, CLEARTYPE_QUALITY, NULL, fontName, &font);
}

ZeroFont::~ZeroFont() {
	SAFE_RELEASE(font);
}

void ZeroFont::ReloadResource() {
	font->Release();
	D3DXCreateFontA(ZeroApp->GetDevice(), static_cast<UINT>(fontSize), 0, fontWeight, D3DX_DEFAULT, NULL,
		DEFAULT_CHARSET, OUT_TT_PRECIS, CLEARTYPE_QUALITY, NULL, fontName, &font);
	m_Color = D3DCOLOR_ARGB(255, 0, 0, 0);
}

void ZeroFont::Render() {
	ZeroIScene::Render();
	ZeroVec pos = ZeroVec(0, 0);
	D3DXVec2TransformCoord(&pos, &pos, &m_Mat);
	SetRect(static_cast<int>(pos.x), static_cast<int>(pos.y), -1, -1);
	font->DrawTextA(NULL, content.c_str(), content.size(), &Rect(), DT_TOP | DT_LEFT | DT_NOCLIP, m_Color);
}

void ZeroFont::Update(float _eTime) {
	ZeroIScene::Update(_eTime);
}

void ZeroFont::SetString(int _content) {
	std::ostringstream s;
	s << _content;

	content = s.str();
}

void ZeroFont::SetString(char* _format, ...) {
	// 가변 인자의 전체 길이 구하기 https://kldp.org/node/76855
	char buffer[256] = { 0 };
	char* data = buffer;
	va_list vargs;
	va_start(vargs, _format);
	int ret = vsnprintf(data, sizeof(buffer), _format, vargs);
	va_end(vargs);
	if (ret + 1 > sizeof(buffer)) data = static_cast<char *>(malloc(ret + 1));
	va_start(vargs, _format);
	vsprintf(data, _format, vargs);
	va_end(vargs);
	std::string args(data);
	if (data != buffer) free(data);

	content = args;
}

void ZeroFont::SetWeight(int _weight) {
	fontWeight = _weight;
	font->Release();
	D3DXCreateFontA(ZeroApp->GetDevice(), static_cast<UINT>(fontSize), 0, fontWeight, D3DX_DEFAULT, NULL, DEFAULT_CHARSET, OUT_TT_PRECIS, CLEARTYPE_QUALITY, NULL, fontName, &font);
	m_Color = D3DCOLOR_ARGB(255, 0, 0, 0);
}

const char* ZeroFont::GetString() const {
	return content.c_str();
}
