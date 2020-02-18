#include "Mesh.h"

Mesh::Mesh(std::string& path)
{
    std::fstream f(path, std::ios::in);
    if (!f.good())
       throw IGEXCEPTIONIO(std::string("Unable to load mesh "+ path).c_str());

    int nVertex;
    float tmp;

    //Vertex pos
    f >> nVertex;
    for (int i = 0; i < nVertex; ++i)
    {
        f >> tmp;
        vertexPositions.push_back(tmp);
    }

    //Txt cords
    f >> nVertex;
    for (int i = 0; i < nVertex; ++i)
    {
        f >> tmp;
        textureCoords.push_back(tmp);
    }

    //indices
    f >> nVertex;
    int ind;
    for (int i = 0; i < nVertex; ++i)
    {
        f >> ind;
        indices.push_back(ind);
    }
}