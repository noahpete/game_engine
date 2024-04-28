#include "Camera.h"

glm::vec2 Camera::sPosition;
glm::vec2 Camera::sOffset;
float Camera::sZoom;
float Camera::sEase;


Camera::Camera()
{
    sPosition = { 0.0f, 0.0f };
    sOffset = { 0.0, 0.0 };
    sZoom = 1.0;
    sEase = 1.0;

}

Camera::~Camera()
{
}

void Camera::SetPosition(float x, float y)
{
    sPosition = { x, y };
}

void Camera::SetZoom(float zoom)
{
    sZoom = zoom;
}

float Camera::GetPositionX()
{
    return sPosition.x;
}

float Camera::GetPositionY()
{
    return sPosition.y;
}

float Camera::GetZoom()
{
    return sZoom;
}

void Camera::Reset()
{
    sPosition = { 0.0f, 0.0f };
    sOffset = { 0.0, 0.0 };
    sZoom = 1.0;
    sEase = 1.0;
}
