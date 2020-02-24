#pragma once
#include<glm/glm.hpp>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <iostream>
class Material
{
public:
	Material()=delete;
	Material(std::string dataPath);
	~Material();

	//Material Choices
	void setMaterial(std::string x);
	void nextMaterial();
	void ListMaterials();
	//Gettery
	glm::vec3& getAmbient() { return _current->second.ambient; }
	glm::vec3& getDiffuse() { return _current->second.diffuse; }
	glm::vec3& getSpecular() { return _current->second.specular; }
	float getShininess() { return _current->second.shininess; }
	std::string getCurrName() { return _current->first; }
private:
	//Material stuff
	struct material
	{
		material(glm::vec3 am, glm::vec3 dif, glm::vec3 spec, float shi) : ambient(am), diffuse(dif), specular(spec), shininess(shi) {}
		material() :ambient(0.f, 0.f, 0.f),diffuse(0.f, 0.f, 0.f),specular(0.f, 0.f, 0.f),shininess(0.f) {}
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;
	};

	//Class stuff
	std::map<std::string, material> _materials;
	std::map<std::string, material>::iterator _current;
	std::vector<std::string> _materialNames;
};

