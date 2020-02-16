#include "Model.h"

Model::Model()
    :
    m_pTexture(nullptr)
{
}

Model::~Model()
{
    deleteData();
}

void Model::addData(const Mesh* mesh)
{
    //m_Mesh = mesh;
    genVAO();
    addVBO(3, mesh->vertexPositions);
    addVBO(2, mesh->textureCoords);
    addEBO(mesh->indices);
}

void Model::deleteData()
{
    if (m_VAO)
        glDeleteVertexArrays(1, &m_VAO);
    if (m_vecVBO.size() > 0)
        glDeleteBuffers(static_cast<GLsizei>(m_vecVBO.size()),
            m_vecVBO.data());
    m_vecVBO.clear();
}

void Model::genVAO()
{
    if (m_VAO != 0)
        deleteData();
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
}

void Model::addEBO(const std::vector<GLuint>& indices)
{
    m_nIndices = static_cast<GLuint>(indices.size());
    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
        indices.data(), GL_STATIC_DRAW);
}

void Model::addVBO(int dimensions, const std::vector<GLfloat>& data)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(),
        GL_STATIC_DRAW);

    glVertexAttribPointer(static_cast<GLuint>(m_vecVBO.size()), dimensions, GL_FLOAT,
        GL_FALSE, 0, (GLvoid*)0);

    glEnableVertexAttribArray(static_cast<GLuint>(m_vecVBO.size()));

    m_vecVBO.push_back(vbo);
}

void Model::setTexture(Texture* x)
{
    m_pTexture = x;
}

void Model::bindVAO() const
{
    glBindVertexArray(m_VAO);
}

int Model::getIndicesCount() const
{
    return m_nIndices;
}

GLuint Model::getTexture()
{
    if (m_pTexture==nullptr) throw IGEXCEPTION_MODEL("Model nie ma przydzielonej tekstury!");
    return m_pTexture->getID();
}

Model::Exception::Exception(int line, const char* file, const char* what) noexcept
    :
    IGException(line, file, what)
{}

const char* Model::Exception::getType() const noexcept
{
    return "IGModel Exception";
}

Mesh::Mesh(std::string& path)
{
    std::fstream f(path, std::ios::in);
    if (!f.good()) throw IGEXCEPTION_MODEL("Unable  to load mesh");

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
