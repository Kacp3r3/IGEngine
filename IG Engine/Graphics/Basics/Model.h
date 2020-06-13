#pragma once


#include <glad/glad.h>
#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags

#include "Graphics/Basics/Mesh.h"
#include "Graphics/Basics/Texture.h"


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
    Model(const std::string& path);
    ~Model();
    
public:
    void draw(Shader& shader);

    void addTexture(Texture* t);

private:
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture*> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    //void deleteData();

private:
    std::vector<Mesh> m_vecMeshes;
    std::string directory;
    std::vector<Texture*> m_vecLoadedTextures;
    
};

#define IGEXCEPTION_MODEL(x) Model::Exception(__LINE__,__FILE__,x);
