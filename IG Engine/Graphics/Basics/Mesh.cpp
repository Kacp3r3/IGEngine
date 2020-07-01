#include "Mesh.h"

//Mesh::Mesh(std::string& path, MeshType m)
//{
//    std::fstream f(path, std::ios::in);
//    if (!f.good())
//       throw IGEXCEPTIONIO(std::string("Unable to load mesh "+ path).c_str());
//    switch (m)
//    {
//        case MeshType::MESH:
//        loadMesh(f);
//        break;
//        case MeshType::OBJ:
//        loadObj(f);
//        break;
//        default:
//            break;
//    }
//    f.close();
//}
//
//void Mesh::loadMesh(std::fstream& f)
//{
//    int nVertex;
//    float x,y,z;
//
//    //Vertex pos
//    f >> nVertex;
//    for (int i = 0; i < nVertex; ++i)
//    {
//        f >> x>>y>>z;
//        m_vecPositions.push_back(x);
//        m_vecPositions.push_back(y);
//        m_vecPositions.push_back(z);
//    }
//
//    //Txt cords
//    f >> nVertex;
//    for (int i = 0; i < nVertex; ++i)
//    {
//        f >> x >> y;
//        m_vecTextureCoords.push_back(x);
//        m_vecTextureCoords.push_back(y);
//    }
//
//    //Normals
//    f >> nVertex;
//    for (int i = 0; i < nVertex; ++i)
//    {
//        f >> x >> y >> z;
//        m_vecNormals.push_back(x);
//        m_vecNormals.push_back(y);
//        m_vecNormals.push_back(z);
//    }
//
//    if (m_vecTextureCoords.size() < 1)m_vecTextureCoords = std::vector<GLfloat>(m_vecPositions.size(), 0.f);
//    if (m_vecNormals.size() < 1)m_vecNormals = std::vector<GLfloat>(m_vecPositions.size(), 0.f);
//    //indices
//    f >> nVertex;
//    int ind;
//    for (int i = 0; i < nVertex; ++i)
//    {
//        f >> ind;
//        m_vecIndices.push_back(ind);
//    }
//}
//
//void Mesh::loadObj(std::fstream& f)
//{
//    auto ind = [](int Vertex, int element) {return Vertex * 3 + element - 1; };
//    std::string line;
//    std::vector<std::string> strings;
//    std::vector<std::string> faces;
//    std::vector<glm::vec3> vertexPos;
//    std::vector<glm::vec2> texturePos;
//    std::vector<glm::vec3> vertexNorm;
//    while (true)
//    {
//        std::getline(f, line);
//        if (line.size() < 1) line = "1";
//        strings.clear();
//        StringUtil::split(line, strings);
//        if (strings[0] == "v")
//        {
//            vertexPos.emplace_back(std::stof(strings[1]), std::stof(strings[2]), std::stof(strings[3]));
//        }
//        else if (strings[0] == "vt")
//        {
//            texturePos.emplace_back(std::stof(strings[1]), std::stof(strings[2]));
//        }
//        else if (strings[0] == "vn")
//        {
//            vertexNorm.emplace_back(std::stof(strings[1]), std::stof(strings[2]), std::stof(strings[3]));
//        }
//        else if (strings[0] == "f")
//        {
//            m_vecPositions = std::vector<GLfloat>(vertexPos.size()*3, 0.f);
//            m_vecTextureCoords = std::vector<GLfloat>(vertexPos.size()*2, 0.f);
//            m_vecNormals = std::vector<GLfloat>(vertexPos.size()*3, 0.f);
//            break;
//        }
//    }
//    
//    int vIndex, txtIndex,normIndex;
//    do
//    {
//        strings.clear();
//        StringUtil::split(line, strings, ' ');
//        if (strings[0] == "f")
//        {       
//            for (int i = 1; i < strings.size(); ++i)
//            {
//                faces.clear();
//                StringUtil::split(strings[i], faces, '/');
//                vIndex = std::stoi(faces[0]) - 1;
//                txtIndex = std::stoi(faces[1]) - 1;
//                normIndex = std::stoi(faces[2]) - 1;
//                m_vecIndices.push_back(vIndex);
//
//
//                m_vecPositions[vIndex*3] = vertexPos[vIndex].x;
//                m_vecPositions[vIndex*3+1] = vertexPos[vIndex].y;
//                m_vecPositions[vIndex*3+2] = vertexPos[vIndex].z;
//
//
//                m_vecTextureCoords[vIndex * 2] = texturePos[txtIndex].x;
//                m_vecTextureCoords[vIndex * 2 + 1] = texturePos[txtIndex].y;
//
//
//                m_vecNormals[vIndex*3] = vertexNorm[normIndex].x;
//                m_vecNormals[vIndex*3+1] = vertexNorm[normIndex].y;
//                m_vecNormals[vIndex*3+2] = vertexNorm[normIndex].z;
//            }
//        }
//    } while (std::getline(f, line));
//}
//
Mesh::Mesh(float pos[], float norm[], int nV, float txt[], int nT, int ind[], int nI, Texture* txtr)
{
    m_vecVert.clear();
    m_vecIndices.clear();
    m_vecVert.reserve(nV);
    m_vecIndices.reserve(nI);
    int txtIndex=0;
    for (int i = 0; i < nV*3; i+=3)
    {
        m_vecVert.push_back({ {pos[i],pos[i + 1],pos[i + 2]},{norm[i],norm[i + 1],norm[i + 2]},{txt[txtIndex],txt[txtIndex +1]} });
        txtIndex += 2;
    }
    for (int i = 0; i < nI; ++i)
    {
        m_vecIndices.push_back(ind[i]);
    }
    delete[]pos;
    delete[]ind;
    delete[]txt;
    delete[]norm;
    m_vecTextures.push_back(txtr);
    setupMesh();
}

Mesh::Mesh(std::vector<Vertex> v, std::vector<GLuint> ind, std::vector<Texture*> t)
{
    m_vecIndices = ind;
    m_vecVert = v;
    m_vecTextures = t;
    setupMesh();
}

Mesh::Mesh(std::string& path, MeshType m)
{
    std::fstream f(path, std::ios::in);
    if (!f.good())
        throw IGEXCEPTIONIO(std::string("Unable to load mesh " + path).c_str());

    loadMesh(f);
    setupMesh();
}

void Mesh::draw(Shader& shader)
{
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < m_vecTextures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = m_vecTextures[i]->m_Type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to stream
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to stream
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to stream

        // now set the sampler to the correct texture unit
        shader.setInt((name + number), i);
        //glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, m_vecTextures[i]->m_nID);
    }

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, m_vecIndices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, m_vecVert.size() * sizeof(Vertex) , &m_vecVert[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vecIndices.size() * sizeof(unsigned int),
        &m_vecIndices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)*3));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 6));

    glBindVertexArray(0);
}

void Mesh::loadMesh(std::fstream& f)
{
    int nVertex;
    float x, y, z;

    //Vertex pos
    f >> nVertex;
    for (int i = 0; i < nVertex; ++i)
    {
        f >> x >> y >> z;
        m_vecVert.emplace_back();
        m_vecVert[i].position = glm::vec3(x, y, z);
    }

    //Txt cords
    f >> nVertex;
    for (int i = 0; i < nVertex; ++i)
    {
        f >> x >> y;
        m_vecVert[i].texture = glm::vec2(x, y);
    }

    //Normals
    f >> nVertex;
    for (int i = 0; i < nVertex; ++i)
    {
        f >> x >> y >> z;
        m_vecVert[i].normal = glm::vec3(x, y, z);
    }

    //if (m_vecTextureCoords.size() < 1)m_vecTextureCoords = std::vector<GLfloat>(m_vecPositions.size(), 0.f);
    //if (m_vecNormals.size() < 1)m_vecNormals = std::vector<GLfloat>(m_vecPositions.size(), 0.f);
    //indices
    f >> nVertex;
    int ind;
    for (int i = 0; i < nVertex; ++i)
    {
        f >> ind;
        m_vecIndices.push_back(ind);
    }
}
