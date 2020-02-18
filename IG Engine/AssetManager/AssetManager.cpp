#include "AssetManager.h"

void AssetManager::loadTextures()
{
	auto load = [this](std::string&& path, std::string&& name, bool png) { m_mapTextures[name] = new Texture(path, png); };

	load("Resources/Pictures/zl.jpg", "JanSzescian", false);
	load("Resources/Pictures/zh.png", "Zuza", true);
	//load("bk.jpg", "Greta", false);
	//load("forloo.jpg", "Loop", true);
	load("Resources/Pictures/cursor.png", "Cursor", true);

	std::vector<std::string> files =
	{
		"Resources/Skybox/right.jpg",
		"Resources/Skybox/left.jpg",
		"Resources/Skybox/top.jpg",
		"Resources/Skybox/bottom.jpg",
		"Resources/Skybox/front.jpg",
		"Resources/Skybox/back.jpg"
	};

	std::vector<std::string> files2 =
	{
		"Resources/Skybox/DOOM16right.png",
		"Resources/Skybox/DOOM16left.png",
		"Resources/Skybox/DOOM16top.png",
		"Resources/Skybox/DOOM16bottom.png",
		"Resources/Skybox/DOOM16front.png",
		"Resources/Skybox/DOOM16back.png"
	};

	m_mapTextures["SkyBox"] = new Texture(files,false);
	m_mapTextures["SkyBoxDoom"] = new Texture(files2,true);
}

void AssetManager::loadMeshes()
{
	auto load = [this](std::string&& path, std::string&& name) { m_mapMeshes[name] = new Mesh(path); };

	load("Resources/Cube.mesh", "Cube");
	load("Resources/Plane.mesh", "Plane");
	load("Resources/SkyBox.mesh", "SkyBox");
}

Texture* AssetManager::getTexture(std::string&& name)
{
	return m_mapTextures[name];
}

Mesh* AssetManager::getMesh(std::string&& name)
{
	return m_mapMeshes[name];
}

AssetManager::~AssetManager()
{
	for (auto& texture : m_mapTextures)
		delete texture.second;

	for (auto& mesh : m_mapMeshes)
		delete mesh.second;
}
