#pragma once
#include "Graphics/Resources/Texture.h"
#include "Graphics/Resources/Model.h"
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
	void loadMeshes();
	Texture* getTexture(std::string name);
	Mesh* getMesh(std::string name);

private:
	AssetManager()= default;
	std::map<std::string, Texture*> m_mapTextures;
	std::map<std::string, Mesh*> m_mapMeshes;
};

