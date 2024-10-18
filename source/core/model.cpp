#include <model.h>

Mesh::Mesh(
    std::vector<Vertex>  vertices, 
    std::vector<GLuint>  indices,
    std::vector<Texture> textures
) 
{
    this->vertices = vertices;
    this->indices  = indices;
    this->textures = textures;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER, 
        vertices.size() * sizeof(Vertex),
        &vertices[0],
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, 
        indices.size() * sizeof(GLuint),
        &indices[0],
        GL_STATIC_DRAW
    );

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, Normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

void Mesh::drawMesh(Shader &shader)
{
    unsigned int diffuseNumber  = 0;
    unsigned int specularNumber = 0;

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string name = textures[i].type;
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNumber++);
        else if(name == "texture_specular")
            number = std::to_string(specularNumber++);

        shader.setInt((name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

Model::Model(std::string path)
{
    loadModel(path);
}

void Model::drawModel(Shader &shader)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].drawMesh(shader);
    }
}

void Model::loadModel(std::string path)
{
    Assimp::Importer import;
    
    const aiScene* scene = import.ReadFile(
        path,
        aiProcess_Triangulate |
        aiProcess_FlipUVs
    );

    if (!scene || scene->mFlags &
        AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode)
    {
        std::cout << "Failed to load model: "
                  << import.GetErrorString()
                  << '\n';
        return;
    }
    
    directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        meshes.push_back(processMesh(scene->mMeshes[node->mMeshes[i]], scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;

//  ======================================================[Processing vertices]
    
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        
        Vertex vertex;
        glm::vec3 _position;
        glm::vec3 _normal;
        glm::vec2 _texcoords;

        _position.x = mesh->mVertices[i].x;
        _position.y = mesh->mVertices[i].y;
        _position.z = mesh->mVertices[i].z;
        vertex.Position = _position;

        if (mesh->HasNormals())
        {
            _normal.x = mesh->mNormals[i].x;
            _normal.y = mesh->mNormals[i].y;
            _normal.z = mesh->mNormals[i].z;
            vertex.Normal = _normal;
        }

        if (mesh->mTextureCoords[0])
        {
            _texcoords.x = mesh->mTextureCoords[0][i].x;
            _texcoords.y = mesh->mTextureCoords[0][i].y;
        }
        else
            _texcoords = glm::vec2(0.0f, 0.0f);
        vertex.TexCoords = _texcoords;
        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            for(unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
                indices.push_back(mesh->mFaces[i].mIndices[j]);
        }

    std::vector<Texture> diffuseMaps = loadMaterialTextures(
        scene->mMaterials[mesh->mMaterialIndex],
        aiTextureType_DIFFUSE,
        "texture_diffuse"
    );
    textures.insert(
        textures.end(), 
        diffuseMaps.begin(), diffuseMaps.end()
    );

    std::vector<Texture> specularMaps = loadMaterialTextures(
        scene->mMaterials[mesh->mMaterialIndex],
        aiTextureType_SPECULAR,
        "texture_specular"
    );
    textures.insert(
        textures.end(), 
        specularMaps.begin(), specularMaps.end()
    );

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
    {
        aiString str;
        material->GetTexture(type, i, &str);
        bool skip = false;
        for (unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true; 
                break;
            }
        }

        if (!skip)
        {
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }
    return textures;
}

unsigned int Model::TextureFromFile(const char *path, const std::string &directory, bool gamma)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << '\n';
        stbi_image_free(data);
    }

    return textureID;
}