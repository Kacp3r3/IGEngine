#include "Model.h"

void Model::addData(const Mesh& mesh)
{
    m_Mesh = mesh;
    genVAO();
    addVBO(3, mesh.vertexPositions);
    addVBO(2, mesh.textureCoords);
    addEBO(mesh.indices);
    m_pTexture = nullptr;
}

void Model::deleteData(GLuint& v, std::vector<GLuint>& vec)
{
    if (v)
        glDeleteVertexArrays(1, &v);
    if (vec.size() > 0)
        glDeleteBuffers(static_cast<GLsizei>(vec.size()),
            vec.data());
    vec.clear();
}

void Model::genVAO(GLuint &v, std::vector<GLuint>& vec)
{
    if (v != 0)
        deleteData(v,vec);
    glGenVertexArrays(1, &v);
    glBindVertexArray(v);
}

void Model::addEBO(GLuint& ebo, const std::vector<GLuint>& indices)
{
    m_nIndices = static_cast<GLuint>(indices.size());
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
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

Cube::Cube()
{
	Mesh mesh = {
		//Front
		{1.0f, 1.f, 1.f, //0
		 1.f, -1.f, 1.f,   //1
		-1.f, -1.f, 1.f,	  //2
		-1.f,  1.f, 1.f,	  //3

		//Top
		1.0f, 1.f, 1.f,	  //4
		1.0f,  1.f, -1.f, //5
		-1.f, 1.f, -1.f,	  //6
		-1.f, 1.f, 1.f,	  //7

		//Back
		1.0f,  -1.f, -1.f, //8
		1.0f, 1.f, -1.f, //9
		-1.f,  1.f,-1.f,  //10
		-1.f, -1.f,-1.f,  //11

		//Bottom
		1.0f,  -1.f, -1.f,
		1.0f, -1.f,  1.f,
		-1.f,  -1.f,1.f,
		-1.f, -1.f,-1.f,

		//Left
		-1.0f,  1.f, -1.f,
		-1.0f, 1.f, 1.f,
		-1.f,  -1.f,1.f,
		-1.f, -1.f,-1.f,


		//Right
		1.0f,  1.f, 1.f,
		1.0f, 1.f, -1.f,
		1.f,  -1.f,-1.f,
		1.f, -1.f, 1.f,


    }
    ,{0.f,1.f,
      0.f,0.f,
      1.f,0.f,
      1.f,1.f,
    
    
      1.f,0.f,
      1.f,1.f,
      0.f,1.f,
      0.f,0.f,
    
      0.f,0.f,
      0.f,1.f,
      1.f,1.f,
      1.f,0.f,
    
      0.f,1.f,
      0.f,0.f,
      1.f,0.f,
      1.f,1.f,
    
      1.f,1.f,
      0.f,1.f,
      0.f,0.f,
      1.f,0.f,
    
      1.f,1.f,
      0.f,1.f,
      0.f,0.f,
      1.f,0.f,
    }
    
    ,{0,1,3, 1,2,3,
      4,5,7, 5,6,7,
      8,9,11, 9,10,11,
      12,13,15, 13,14,15,
      16,17,19, 17,18,19,
      20,21,23,21,22,23
     } };
    addData(mesh);

}
