#pragma once

#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <shader.h>

class Cubemap
{
    public:

        Cubemap();
        ~Cubemap();

        void drawCubemap();

    private:

        unsigned int VAO, VBO, skyboxTextureID;

        void setSkyboxModel();
        void setSkyboxTextures();

};

#endif
