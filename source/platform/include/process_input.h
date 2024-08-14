#ifndef PROCESS_INPUT_H
#define PROCESS_INPUT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

void processInput(GLFWwindow *window, glm::vec3& cameraPosition, glm::vec3& cameraFront, glm::vec3& cameraUp, float speed, float deltaTime);

#endif