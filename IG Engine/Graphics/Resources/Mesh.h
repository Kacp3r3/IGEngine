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


class Mesh 
{
public:
    Mesh(std::string& path, MeshType m = MeshType::MESH);


private:
    void loadMesh(std::fstream& f);
    void loadObj(std::fstream& f);
public:
    std::vector<GLfloat> m_vecPositions;
    std::vector<GLfloat> m_vecTextureCoords;
    std::vector<GLfloat> m_vecNormals;
    std::vector<GLuint> m_vecIndices;
};

