#pragma once


#include <vector>
#include <string>
#include <glad/glad.h>
#include <fstream>


#include "Utility/IGException.h"


class Mesh 
{
public:
    Mesh(std::string& path);

public:
    std::vector<GLfloat> vertexPositions;
    std::vector<GLfloat> textureCoords;
    std::vector<GLuint> indices;
};

