#pragma once


#include <vector>
#include <string>
#include <glad/glad.h>
#include <fstream>
#include <string>
#include <glm/glm.hpp>


#include "Utility/Enums.h"
#include "Utility/IGException.h"
#include "Utility/StringUtil.h"
#include "Graphics/Basics/Texture.h"
#include "Graphics/Shaders/Shader.h"



struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture;
};

class Mesh 
{
public:

    Mesh(std::vector<Vertex> v, std::vector<GLuint> ind, std::vector<Texture*> t);
    Mesh(std::string& path, MeshType m = MeshType::MESH);
public:
    void draw(Shader& shader);


private:
    void setupMesh();
    void loadMesh(std::fstream& f);
    //void loadObj(std::fstream& f);
public:
    GLuint VAO, VBO, EBO;
    std::vector<Vertex> m_vecVert;
    std::vector<GLuint> m_vecIndices;
    std::vector<Texture*> m_vecTextures;
};

