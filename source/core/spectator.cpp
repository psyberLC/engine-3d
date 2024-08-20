#include <spectator.h>

Spectator::Spectator() 
{ 

    this->yaw = -90.0f;
    this->pitch = 0.0f;
    this->fov = 75.0f;
    this->sensitivity = 0.5f;

    this->width = 800;
    this->height = 600;

    this->lastX = static_cast<float>(width / 2.0f);
    this->lastY = static_cast<float>(height / 2.0f);

    this->cameraPosition = glm::vec3(50.0f, 2.0f, 50.0f);
    this->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

}

Spectator::Spectator(float yaw, float pitch, float fov, float sensitivity,
                     unsigned int width, unsigned int height, glm::vec3 cameraPosition, 
                     glm::vec3 cameraFront, glm::vec3 cameraUp) 
{

    this->yaw = yaw;
    this->pitch = pitch;
    this->fov = fov;
    this->sensitivity = sensitivity;

    this->width = width;
    this->height = height;

    this->lastX = static_cast<float>(width / 2.0f);
    this->lastY = static_cast<float>(height / 2.0f);

    this->cameraPosition = cameraPosition;
    this->cameraFront = cameraFront;
    this->cameraUp = cameraUp;

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