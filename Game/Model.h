#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.h"
#include "Mesh.h"

class Model
{
public:
    void init(const char* path);
    void Draw(Shader& shader);

private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(std::string const& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<TextureF> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    unsigned int textureFromFile(const char* path, const std::string& directory, bool gamma);

};

