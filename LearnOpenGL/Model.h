#pragma once

#include"Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "stb_image.h"

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

class Model
{
public:
    /*  函数   */
    Model(std::string&& path, bool gamma=false);
    void Draw(Shader& shader);
public:
    /*  模型数据  */
    std::vector<Mesh> m_meshes;
    std::string m_directory;
    std::vector<Texture> textures_loaded;
    bool gammaCorrection;

    /*  函数   */
    void loadModel(std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        std::string&& typeName);
};

