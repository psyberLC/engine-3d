#ifndef SPECTATOR_H
#define SPECTATOR_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Spectator
{
    public:

        float yaw;
        float pitch;
        float fov;
        float sensitivity;

        unsigned int width;
        unsigned int height;
        unsigned int lastX;
        unsigned int lastY;

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
};
#endif