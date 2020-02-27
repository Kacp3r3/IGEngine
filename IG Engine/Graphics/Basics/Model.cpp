#include "Model.h"
Model::Model(const Mesh&& mesh)
    :
    m_pTexture(nullptr)
    ,m_bTexture(true)
{
    addData(mesh);
}

Model::~Model()
{
    deleteData();
}

void Model::addData(const Mesh& mesh)
{
    genVAO();
    addVBO(3, mesh.m_vecPositions);
    addVBO(2, mesh.m_vecTextureCoords);
    addVBO(3, mesh.m_vecNormals);
    addEBO(mesh.m_vecIndices);
}

void Model::deleteData()
{
    if (m_VAO)
        glDeleteVertexArrays(1, &m_VAO);
    if (m_vecVBO.size() > 0)
        glDeleteBuffers(static_cast<GLsizei>(m_vecVBO.size()),
            m_vecVBO.data());
    m_vecVBO.clear();
    glDeleteBuffers(1, &m_EBO);
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

void Model::haveTexture(bool x)
{
    m_bTexture = x;
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
    try {
        if (m_bTexture)
        {
            if (m_pTexture == nullptr)
                throw IGEXCEPTION_MODEL("Model nie ma przydzielonej tekstury!");
            return m_pTexture->getID();    
        }
    }
    catch (IGException & e) { printf("%s", e.what()); }
    return 0;
}

Model::Exception::Exception(int line, const char* file, const char* what) noexcept
    :
    IGException(line, file, what)
{}

const char* Model::Exception::getType() const noexcept
{
    return "IGModel Exception";
}

