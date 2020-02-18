#pragma once

#include <string>
#include <map>

#include "Graphics/Resources/Texture.h"
#include "Graphics/Resources/Model.h"


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


	Texture* getTexture(std::string&& name);
	Mesh* getMesh(std::string&& name);

private:
	AssetManager()= default;
	~AssetManager();
	AssetManager(const AssetManager&) = delete;
	AssetManager& operator=(const AssetManager&) = delete;


private:
	std::map<std::string, Texture*> m_mapTextures;
	std::map<std::string, Mesh*> m_mapMeshes;
};


