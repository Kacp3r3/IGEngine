#pragma once
#include <vector>
#include <glad/glad.h>
#include "Graphics/Texture.h"
#include "Utility/IGException.h"
struct Mesh {
    std::vector<GLfloat> vertexPositions;
    std::vector<GLfloat> textureCoords;
    std::vector<GLuint> indices;
};

class Model
{
public:
    class Exception : public IGException
    {
    public:
        Exception(int line, const char* file, const char* what) noexcept;
    private:
        const char* getType()const noexcept override;
    };
public:
    Model() = default;

    void addData(const Mesh& mesh);
    void bindVAO() const;
    int getIndicesCount() const;
    GLuint getTexture();
    void setTexture(Texture* x);
private:
    void deleteData(GLuint& v, std::vector<GLuint>& vec);
    void genVAO(GLuint& v, std::vector<GLuint>& vec);
    void addEBO(const std::vector<GLuint>& indices);
    void addVBO(int dimensions, const std::vector<GLfloat>& data);
private:
    int m_nIndices;
    Texture* m_pTexture;
};

class Cube : public Model
{
public:
    Cube();
private:
    glm::vec3 pos;
    static Mesh m_Mesh;
    static GLuint m_VAO, m_EBO;
    static std::vector<GLuint> m_vecVBO;
};
#define IGEXCEPTION_MODEL(x) Model::Exception(__LINE__,__FILE__,x);
