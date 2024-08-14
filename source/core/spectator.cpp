#include <spectator.h>

Spectator::Spectator() 
{ 

    Spectator::yaw = -90.0f;
    Spectator::pitch = 0.0f;
    Spectator::fov = 75.0f;
    Spectator::sensitivity = 0.5f;

    Spectator::width = 800;
    Spectator::height = 600;

    Spectator::lastX = static_cast<float>(Spectator::width / 2.0f);
    Spectator::lastY = static_cast<float>(Spectator::height / 2.0f);

    Spectator::cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    Spectator::cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    Spectator::cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

}

Spectator::Spectator(float yaw, float pitch, float fov, float sensitivity,
                     unsigned int width, unsigned int height, glm::vec3 cameraPosition, 
                     glm::vec3 cameraFront, glm::vec3 cameraUp) 
{

    Spectator::yaw = yaw;
    Spectator::pitch = pitch;
    Spectator::fov = fov;
    Spectator::sensitivity = sensitivity;

    Spectator::width = width;
    Spectator::height = height;

    Spectator::lastX = static_cast<float>(Spectator::width / 2.0f);
    Spectator::lastY = static_cast<float>(Spectator::height / 2.0f);

    Spectator::cameraPosition = cameraPosition;
    Spectator::cameraFront = cameraFront;
    Spectator::cameraUp = cameraUp;

}

void Spectator::processCursor(double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstTimeMouseEvent)
    {
        Spectator::lastX = xpos;
        Spectator::lastY = ypos;
        Spectator::firstTimeMouseEvent = false;
    }

    float xoffset = xpos - Spectator::lastX;
    float yoffset = Spectator::lastY - ypos;
    Spectator::lastX = xpos;
    Spectator::lastY = ypos;

    xoffset *= Spectator::sensitivity;
    yoffset *= Spectator::sensitivity;

    Spectator::yaw += xoffset;
    Spectator::pitch += yoffset;

    if (Spectator::pitch > 89.0f)
        Spectator::pitch = 89.0f;
    if (Spectator::pitch < -89.0f)
        Spectator::pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(Spectator::yaw)) * cos(glm::radians(Spectator::pitch));
    front.y = sin(glm::radians(Spectator::pitch));
    front.z = sin(glm::radians(Spectator::yaw)) * cos(glm::radians(Spectator::pitch));
    Spectator::cameraFront = glm::normalize(front);
}