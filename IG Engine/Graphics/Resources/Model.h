#pragma once
#include <vector>
#include <fstream>
#include <glad/glad.h>
#include "Utility/IGException.h"
#include "Graphics/Resources/Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Mesh {
    Mesh(std::string& path);
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
    Model();
    ~Model();
    void addData(const Mesh* mesh);
    void bindVAO()const;
    int getIndicesCount()const;
    GLuint getTexture();
    void setTexture(Texture* x);
private:
    void deleteData();
    void genVAO();
    void addEBO(const std::vector<GLuint>& indices);
    void addVBO(int dimensions, const std::vector<GLfloat>& data);
protected:
    //Mesh m_Mesh;
    GLuint m_VAO, m_EBO;
    std::vector<GLuint> m_vecVBO;
    int m_nIndices;
    Texture* m_pTexture;
};
#define IGEXCEPTION_MODEL(x) Model::Exception(__LINE__,__FILE__,x);
