#pragma once


using namespace std;

#define ZeroTexMgr ZeroTextureManager::Instance()

class ZeroTextureManager {
private:
	ZeroTextureManager();

	typedef map<string, LPDIRECT3DTEXTURE9> TEXTURE;
	TEXTURE textureList;

public:
	~ZeroTextureManager();

	static ZeroTextureManager* Instance();
	LPDIRECT3DTEXTURE9 LoadTextureFromFile(char* _path);
	void Release(char* _path, ...);
	void Clear();
	void ReloadResource();
};
