#pragma once

#include "ZeroIScene.h"
#include "ZeroResource.h"

class ZeroFont : public ZeroIScene, public ZeroResource {
private:
	LPD3DXFONT font;
	std::string content;
	char* fontName;
	int fontSize;
	int fontWeight;

	void ReloadResource();

public:
	ZeroFont(UINT _size, char* _string, char* _fontname = "맑은 고딕", char* _filename = NULL);
	~ZeroFont();

	void Render();
	void Update(float _eTime);

	void SetString(int _content);
	void SetString(char* _format, ...);

	void SetWeight(int _weight);

	const char* GetString() const;
};
