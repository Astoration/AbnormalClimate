#pragma once

using namespace std;

#define ZeroShaderMgr ZeroShaderManager::Instance()

class ZeroShaderManager {
private:
	ZeroShaderManager();

	typedef map<char*, LPD3DXEFFECT> SHADER;
	SHADER shaderList;

public:
	~ZeroShaderManager();

	static ZeroShaderManager* Instance();

	LPD3DXEFFECT LoadShaderFromFile(char * _path);
	void ReloadResource();
};
