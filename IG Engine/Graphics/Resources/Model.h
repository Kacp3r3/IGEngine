#pragma once


#include <glad/glad.h>


#include "Graphics/Resources/Mesh.h"
#include "Graphics/Resources/Texture.h"


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
    Model(const Mesh&& mesh);
    ~Model();
    

public:
    void addData(const Mesh& mesh);
    void bindVAO()const;
    

public:
    void setTexture(Texture* x);
    void haveTexture(bool x);


public:
    int getIndicesCount()const;
    GLuint getTexture();


private:
    void deleteData();
    void genVAO();
    void addEBO(const std::vector<GLuint>& indices);
    void addVBO(int dimensions, const std::vector<GLfloat>& data);


protected:
    int m_nIndices;
    bool m_bTexture;
    Texture* m_pTexture;
    std::vector<GLuint> m_vecVBO;
    GLuint m_VAO, m_EBO;
};

#define IGEXCEPTION_MODEL(x) Model::Exception(__LINE__,__FILE__,x);
