#include "AssetManager.h"

void AssetManager::loadTextures()
{
	auto load = [this](std::string path, std::string name, bool trans) { m_mapTextures[name] = new Texture(path, trans); };

	load("zl.jpg", "JanSzescian", false);
	load("zh.png", "Zuza", true);
	//load("bk.jpg", "Greta", false);
	//load("forloo.jpg", "Loop", true);
	load("cursor.png", "Cursor", true);
}

Texture* AssetManager::getTexture(std::string name)
{
	return m_mapTextures[name];
}
