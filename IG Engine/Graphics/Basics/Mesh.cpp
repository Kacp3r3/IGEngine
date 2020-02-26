#include "Mesh.h"

Mesh::Mesh(std::string& path, MeshType m)
{
    std::fstream f(path, std::ios::in);
    if (!f.good())
       throw IGEXCEPTIONIO(std::string("Unable to load mesh "+ path).c_str());
    switch (m)
    {
        case MeshType::MESH:
        loadMesh(f);
        break;
        case MeshType::OBJ:
        loadObj(f);
        break;
        default:
            break;
    }
    f.close();
}

void Mesh::loadMesh(std::fstream& f)
{
    int nVertex;
    float x,y,z;

    //Vertex pos
    f >> nVertex;
    for (int i = 0; i < nVertex; ++i)
    {
        f >> x>>y>>z;
        m_vecPositions.push_back(x);
        m_vecPositions.push_back(y);
        m_vecPositions.push_back(z);
    }

    //Txt cords
    f >> nVertex;
    for (int i = 0; i < nVertex; ++i)
    {
        f >> x >> y;
        m_vecTextureCoords.push_back(x);
        m_vecTextureCoords.push_back(y);
    }

    //Normals
    f >> nVertex;
    for (int i = 0; i < nVertex; ++i)
    {
        f >> x >> y >> z;
        m_vecNormals.push_back(x);
        m_vecNormals.push_back(y);
        m_vecNormals.push_back(z);
    }

    if (m_vecTextureCoords.size() < 1)m_vecTextureCoords = std::vector<GLfloat>(m_vecPositions.size(), 0.f);
    if (m_vecNormals.size() < 1)m_vecNormals = std::vector<GLfloat>(m_vecPositions.size(), 0.f);
    //indices
    f >> nVertex;
    int ind;
    for (int i = 0; i < nVertex; ++i)
    {
        f >> ind;
        m_vecIndices.push_back(ind);
    }
}

void Mesh::loadObj(std::fstream& f)
{
    auto ind = [](int Vertex, int element) {return Vertex * 3 + element - 1; };
    std::string line;
    std::vector<std::string> strings;
    std::vector<std::string> faces;
    std::vector<glm::vec3> vertexPos;
    std::vector<glm::vec2> texturePos;
    std::vector<glm::vec3> vertexNorm;
    while (true)
    {
        std::getline(f, line);
        strings.clear();
        StringUtil::split(line, strings);
        if (strings[0] == "v")
        {
            vertexPos.emplace_back(std::stof(strings[1]), std::stof(strings[2]), std::stof(strings[3]));
        }
        else if (strings[0] == "vt")
        {
            texturePos.emplace_back(std::stof(strings[1]), std::stof(strings[2]));
        }
        else if (strings[0] == "vn")
        {
            vertexNorm.emplace_back(std::stof(strings[1]), std::stof(strings[2]), std::stof(strings[3]));
        }
        else if (strings[0] == "f")
        {
            m_vecPositions = std::vector<GLfloat>(vertexPos.size()*3, 0.f);
            m_vecTextureCoords = std::vector<GLfloat>(vertexPos.size()*2, 0.f);
            m_vecNormals = std::vector<GLfloat>(vertexPos.size()*3, 0.f);
            break;
        }
    }
    
    int vIndex, txtIndex,normIndex;
    do
    {
        strings.clear();
        StringUtil::split(line, strings, ' ');
        if (strings[0] == "f")
        {       
            for (int i = 1; i < 4; ++i)
            {
                faces.clear();
                StringUtil::split(strings[i], faces, '/');
                vIndex = std::stoi(faces[0]) - 1;
                txtIndex = std::stoi(faces[1]) - 1;
                normIndex = std::stoi(faces[2]) - 1;
                m_vecIndices.push_back(vIndex);


                m_vecPositions[vIndex*3] = vertexPos[vIndex].x;
                m_vecPositions[vIndex*3+1] = vertexPos[vIndex].y;
                m_vecPositions[vIndex*3+2] = vertexPos[vIndex].z;


                m_vecTextureCoords[vIndex * 2] = texturePos[txtIndex].x;
                m_vecTextureCoords[vIndex * 2 + 1] = texturePos[txtIndex].y;


                m_vecNormals[vIndex*3] = vertexNorm[normIndex].x;
                m_vecNormals[vIndex*3+1] = vertexNorm[normIndex].y;
                m_vecNormals[vIndex*3+2] = vertexNorm[normIndex].z;
            }
        }
    } while (std::getline(f, line));
}

Mesh::Mesh(float pos[], float norm[], int nV, float txt[], int nT, int ind[], int nI)
{
    m_vecPositions.reserve(nV);
    m_vecNormals.reserve(nV);
    m_vecTextureCoords.reserve(nT);
    m_vecIndices.reserve(nI);
    for (int i = 0; i < nV; ++i)
    {
        m_vecPositions.push_back(pos[i]);
        m_vecNormals.push_back(norm[i]);
    }
    for (int i = 0; i < nT; ++i)
    {
        m_vecTextureCoords.push_back(txt[i]);
    }
    for (int i = 0; i < nI; ++i)
    {
        m_vecIndices.push_back(ind[i]);
    }
    delete[]pos;
    delete[]ind;
    delete[]txt;
    delete[]norm;
}
