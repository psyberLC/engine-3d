#ifndef SPECTATOR_H
#define SPECTATOR_H

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_loader.h>

class Spectator
{
    public:

        double yaw;
        float pitch;
        float fov;
        float sensitivity;

        unsigned int width;
        unsigned int height;
        float lastX;
        float lastY;

        glm::vec3 cameraPosition;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;

        Spectator();
        Spectator(float yaw, float pitch, float fov, float sensitivity,
                  unsigned int width, unsigned int height, glm::vec3 cameraPosition, 
                  glm::vec3 cameraFront, glm::vec3 cameraUp);

        void processCursor(double xposIn, double yposIn);

    private:

        bool firstTimeMouseEvent = true;

        void pitchCorrection(float& pitch);
        void frontCalculation();

};
#endif