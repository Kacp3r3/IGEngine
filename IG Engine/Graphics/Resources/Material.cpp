#include "Material.h"

Material::Material(std::string dataPath)
{
	std::fstream file;
	file.open(dataPath, std::ios::in);

	if (!file.good()) throw std::runtime_error("File: " + dataPath + " not sucessfuly loaded");
	material tmp;
	std::string tmpname;
	float r, g, b;

	file >> tmpname;

	while (tmpname != "@")
	{
		//Ambient
		file >> r >> g >> b;
		tmp.ambient.r = r;
		tmp.ambient.g = g;
		tmp.ambient.b = b;

		//Diffuse
		file >> r >> g >> b;
		tmp.diffuse.r = r;
		tmp.diffuse.g = g;
		tmp.diffuse.b = b;

		//Specular
		file >> r >> g >> b;
		tmp.specular.r = r;
		tmp.specular.g = g;
		tmp.specular.b = b;

		//Shininess
		file >> r;
		tmp.shininess = r*128.f;

		//Adding data
		_materials.emplace(tmpname,tmp);
		_materialNames.push_back(tmpname);

		//Next
		file >> tmpname;
	}
	
	file.close();
	tmp.ambient = { 0.3,0.3,0.3 };
	tmp.specular = {0.2,0.2,0.2 };
	tmp.diffuse = { 0.2,0.2,0.2 };
	tmp.shininess = 0.2f;
	_materials.emplace("DefaultLight", tmp);
	_materialNames.push_back("DefaultLight");
	tmp.ambient = { 0.,0.,0. };
	tmp.specular = { 0.,0.,0. };
	tmp.diffuse = { 0.,0.,0. };
	tmp.shininess = 0.0f;
	_materials.emplace("Default", tmp);
	_materialNames.push_back("Default");
	_current = _materials.begin();
	ListMaterials();
}

Material::~Material()
{
	
}

void Material::setMaterial(std::string x)
{
	auto tmp = _materials.begin();
	while (tmp != _materials.end())
	{
		if (tmp->first == x) _current = tmp;
	}

}

void Material::nextMaterial()
{
     std::advance(_current, 1);
	 if (_current != _materials.end()) return;
	 else _current = _materials.begin();
}

void Material::ListMaterials()
{
	for (auto x : _materials)
	{
		std::cout << x.first << ": " << x.second.ambient.r <<"|"<< x.second.ambient.g << "|"<< x.second.ambient.b << " "
				  << x.second.diffuse.r << "|" << x.second.diffuse.g << "|" << x.second.diffuse.b << " "
				  << x.second.specular.r <<"|" << x.second.specular.g << "|" << x.second.specular.b << " " << x.second.shininess<<'\n';
	}
}


