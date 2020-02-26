#pragma once

#include <string>
#include <map>

#include "Graphics/Basics/Texture.h"
#include "Graphics/Basics/Model.h"
#include "Graphics//Basics/Picture.h"


class AssetManager
{
public:
	static AssetManager& get()
	{
		static AssetManager a;
		return a;
	}

	void loadTextures();
	void loadModels();
	void loadModel(Model* m, std::string name);
	void loadPictures();

	Texture* getTexture(std::string&& name);
	Model* getModel(std::string&& name);
	Picture* getPicture(std::string&& name);

private:
	AssetManager()= default;
	~AssetManager();
	AssetManager(const AssetManager&) = delete;
	AssetManager& operator=(const AssetManager&) = delete;


private:
	std::map<std::string, Texture*> m_mapTextures;
	std::map<std::string, Model*> m_mapModels;
	std::map<std::string, Picture*> m_mapPictures;
};


