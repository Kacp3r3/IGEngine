#pragma once
#include "Graphics/Texture.h"
#include <string>
#include <map>
class AssetManager
{
public:
	static AssetManager& get()
	{
		static AssetManager a;
		return a;
	}

	void loadTextures();
	Texture* getTexture(std::string name);
private:
	AssetManager()= default;
	std::map<std::string, Texture*> m_mapTextures;
};

