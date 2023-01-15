#pragma once

#include <Math++.hpp>

struct CameraInputs
{
    float deltaX;
    float deltaY;

    bool moveForward;
    bool moveBackward;
    bool moveRight;
    bool moveLeft;

    // ... and more if needed
};

class Camera
{
public:
    Camera() {};
    Camera(const uint p_width, const uint p_height);

    void Update(const float p_deltaTime, const CameraInputs& p_inputs);
    void ShowImGuiControls();

    void resetPosition();
    void resetRotation();

    uint mWidth, mHeight;

    float FOV = 90.f;

    sMatrix::Matrix GetViewMatrix(const sVector3::Vector3 &view, const float pitch, const float yaw);
    sMatrix::Matrix GetProjection(const float far, const float near, float FOV, float hvRatio);

    sMatrix::Matrix projectionMatrix = {};
    sMatrix::Matrix viewMatrix = {};
    
    sVector3::Vector3 viewPosition = {0, 0, -35};
    sVector3::Vector3 viewRotation = {};
};