#pragma once

#ifndef SPECTATOR_H
#define SPECTATOR_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

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

        void yawCorrection();
        void pitchCorrection();
        void frontCalculation();

};
#endif