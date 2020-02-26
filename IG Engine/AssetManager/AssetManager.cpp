#include "AssetManager.h"

void AssetManager::loadTextures()
{
	auto load = [this](std::string&& path, std::string&& name, bool png) { m_mapTextures[name] = new Texture(path, png); };

	load("Resources/Pictures/zl.jpg", "JanSzescian", false);
	load("Resources/Pictures/cursor.png", "Cursor", true);
	load("Resources/Mesh/Stall/stallTexture.png","Stall", true);
	load("Resources/Pictures/grass.jpg", "Grass", false);
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

void AssetManager::loadModels()
{
	auto load = [this](std::string&& path, std::string&& name, MeshType m = MeshType::MESH) { m_mapModels[name] = new Model(Mesh(path,m)); };

	load("Resources/Mesh/SkyBox.mesh", "SkyBox");
	load("Resources/Mesh/Cube.mesh", "Cube");
	load("Resources/Mesh/Plane.mesh", "Plane");
	load("Resources/Mesh/Stall/stall.obj", "Stall", MeshType::OBJ);
	load("Resources/Mesh/Dragon/dragon.obj", "Dragon", MeshType::OBJ);
}

void AssetManager::loadModel(Model* m, std::string name)
{
	m_mapModels[name] = m;
}

void AssetManager::loadPictures()
{
	auto load = [this](std::string&& path, std::string&& name) { m_mapPictures[name] = new Picture(path); };

	load("Resources/Pictures/heightmap.jpg", "terrain");
	load("Resources/Pictures/hm.png", "terrain2");
}

Texture* AssetManager::getTexture(std::string&& name)
{
	if (m_mapTextures.find(name) != m_mapTextures.end())
		return m_mapTextures[name];
	else throw IGEXCEPTIONIO(std::string("Proba uzycia nie istniejacej tekstury: " + name).c_str());
}

Model* AssetManager::getModel(std::string&& name)
{
	if (m_mapModels.find(name) != m_mapModels.end())
		return m_mapModels[name];
	else throw IGEXCEPTIONIO(std::string("Proba uzycia nie istniejacej siatki: " + name).c_str());
}

Picture* AssetManager::getPicture(std::string&& name)
{
	return m_mapPictures[name];
}

AssetManager::~AssetManager()
{
	for (auto& texture : m_mapTextures)
		if (texture.second != nullptr) delete texture.second;

	for (auto& model : m_mapModels)
		if (model.second != nullptr) delete model.second;
}
