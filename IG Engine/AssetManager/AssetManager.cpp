#include "AssetManager.h"

void AssetManager::loadTextures()
{
	auto load = [this](std::string&& path, std::string&& name) { m_mapTextures[name] = new Texture(path); };

	//load("Resources/Pictures/zl.jpg", "JanSzescian");
	//load("Resources/Pictures/cursor.png", "Cursor");
	//load("Resources/Mesh/Stall/stallTexture.png","Stall");
	load("Resources/Pictures/grass.jpg", "Grass");
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
	//load("Resources/Mesh/texture_diffuse1.png", "mapka");
	m_mapTextures["SkyBox"] = new Texture(files);
	m_mapTextures["SkyBoxDoom"] = new Texture(files2);
}

void AssetManager::loadModels()
{
	auto load = [this](std::string&& path, std::string&& name) { m_mapModels[name] = new Model(path); };

	//load("Resources/Mesh/SkyBox.mesh", "SkyBox");
	//load("Resources/Mesh/Cube.mesh", "Cube");
	//load("Resources/Mesh/pln.obj", "plane");
	load("Resources/Mesh/cube.obj", "cube");
	load("Resources/Mesh/backpack/backpack.obj", "bp");
	//load("Resources/Mesh/Stall/stall.obj", "stall");
	//load("Resources/Mesh/Dragon/dragon.obj", "dragon");
	//load("Resources/Mesh/Nanosuit2/nanosuit.obj", "bp");
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
	load("Resources/Pictures/dom.png", "dom");
	load("Resources/Pictures/test.png", "test");
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
