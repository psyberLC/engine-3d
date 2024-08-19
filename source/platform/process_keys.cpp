#include <process_keys.h>

void processKeys(GLFWwindow *window, glm::vec3& cameraPosition, glm::vec3& cameraFront, glm::vec3& cameraUp, float speed, float deltaTime) {

    const float cameraSpeed = speed * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPosition += cameraSpeed * glm::normalize(glm::vec3(cameraFront.x, 0.0, cameraFront.z));
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPosition -= cameraSpeed * glm::normalize(glm::vec3(cameraFront.x, 0.0, cameraFront.z));

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPosition += cameraUp * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraPosition -= cameraUp * cameraSpeed;

}