#pragma once

#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.h>

#include <string>
#include <vector>

#include "shader.h"

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture
{
    unsigned int id;
    std::string  type;
    std::string  path;
};

class Mesh
{
    public:

        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;

        unsigned int VAO;

        Mesh(
            std::vector<Vertex>       vertices,
            std::vector<unsigned int> indices,
            std::vector<Texture>      textures
        );

        void drawMesh(Shader &shader);

    private:

        unsigned int VBO, EBO;

};

class Model
{
    public:

        std::vector<Texture> textures_loaded;
        std::vector<Mesh> meshes;
        std::string directory;

        Model(std::string path);
        void drawModel(Shader &shader);

    private:

        void loadModel(std::string path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);

        std::vector<Texture> loadMaterialTextures(
            aiMaterial* material,
            aiTextureType type,
            std::string typeName
        );
        unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
};

#endif