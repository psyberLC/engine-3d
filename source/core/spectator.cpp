#include <spectator.h>

Spectator::Spectator() 
{ 

    yaw = -90.0f;
    pitch = 0.0f;
    fov = 75.0f;
    sensitivity = 0.5f;

    width = 800;
    height = 600;

    lastX = static_cast<float>(width / 2.0f);
    lastY = static_cast<float>(height / 2.0f);

    cameraPosition = glm::vec3(500.0f, 2.0f, 500.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

}

Spectator::Spectator(float yaw, float pitch, float fov, float sensitivity,
                     unsigned int width, unsigned int height, glm::vec3 cameraPosition, 
                     glm::vec3 cameraFront, glm::vec3 cameraUp) 
{

    yaw = yaw;
    pitch = pitch;
    fov = fov;
    sensitivity = sensitivity;

    width = width;
    height = height;

    lastX = static_cast<float>(width / 2.0f);
    lastY = static_cast<float>(height / 2.0f);

    cameraPosition = cameraPosition;
    cameraFront = cameraFront;
    cameraUp = cameraUp;

}

void Spectator::processCursor(double xposIn, double yposIn)
{

    if (firstTimeMouseEvent)
    {
        lastX = xposIn;
        lastY = yposIn;
        firstTimeMouseEvent = false;
    }

    double xoffset = xposIn - lastX;
    double yoffset = lastY - yposIn;
    lastX = xposIn;
    lastY = yposIn;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    pitchCorrection();

    frontCalculation();

}

void Spectator::pitchCorrection()
{
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
}

void Spectator::frontCalculation()
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}