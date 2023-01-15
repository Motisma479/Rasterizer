
#include <numeric>

#include <imgui.h>
#include <Camera.hpp>

using namespace sMatrix;
using namespace sVector2;
using namespace sVector3;

void Camera::resetPosition() {
    Camera::viewPosition = {0,0,-35};
}
void Camera::resetRotation() {
    Camera::viewRotation = {0,0,0};
}

Camera::Camera(const uint width, const uint height) {
    Camera::mWidth = width;
    Camera::mHeight = height;
}

void Camera::Update(const float p_deltaTime, const CameraInputs& inputs) {
    Vector2 forward; 
    forward += Vector2{1, viewRotation.y * (float)DEG2RAD};

    if(inputs.moveForward)
        viewPosition += Vector3{forward.y, 0, forward.x} * 0.05f;

    if(inputs.moveBackward)
        viewPosition += Vector3{-forward.y, 0, -forward.x} * 0.05f;

    if(inputs.moveRight)
        viewPosition += Vector3{forward.x, 0, -forward.y} * 0.05f;

    if(inputs.moveLeft)
        viewPosition += Vector3{-forward.x, 0, forward.y} * 0.05f;

    viewRotation += Vector3{inputs.deltaY, inputs.deltaX, 0} * 0.01f;
    
}

sMatrix::Matrix Camera::GetViewMatrix(const Vector3 &view, const float pitch, const float yaw) {
    float p = pitch * DEG2RAD;
    float y = yaw * DEG2RAD;

    float cosPitch = cos(p);
    float sinPitch = sin(p);
    float cosYaw = cos(y);
    float sinYaw = sin(y);

    Vector3 xaxis = { cosYaw, 0, -sinYaw };
    Vector3 yaxis = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
    Vector3 zaxis = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };

    float viewXaxis = (xaxis.x * view.x + xaxis.y * view.y + xaxis.z * view.z);
    float viewYaxis = (yaxis.x * view.x + yaxis.y * view.y + yaxis.z * view.z);
    float viewZaxis = (zaxis.x * view.x + zaxis.y * view.y + zaxis.z * view.z);
 
    viewMatrix.matrixData[0][0] = xaxis.x;
    viewMatrix.matrixData[0][1] = xaxis.y;
    viewMatrix.matrixData[0][2] = xaxis.z;
    viewMatrix.matrixData[0][3] = -viewXaxis;

    viewMatrix.matrixData[1][0] = yaxis.x;
    viewMatrix.matrixData[1][1] = yaxis.y;
    viewMatrix.matrixData[1][2] = yaxis.z;
    viewMatrix.matrixData[1][3] = -viewYaxis;

    viewMatrix.matrixData[2][0] = zaxis.x;
    viewMatrix.matrixData[2][1] = zaxis.y;
    viewMatrix.matrixData[2][2] = zaxis.z;
    viewMatrix.matrixData[2][3] = -viewZaxis;

    viewMatrix.matrixData[3][0] = 0;
    viewMatrix.matrixData[3][1] = 0;
    viewMatrix.matrixData[3][2] = 0;
    viewMatrix.matrixData[3][3] = 1;
    return viewMatrix;
}

sMatrix::Matrix Camera::GetProjection(const float far, const float near, float FOV, float hvRatio) {
    float view = 1 / tanf(FOV * PI_NUM / 360);
    projectionMatrix.matrixData[0][0] = view * hvRatio;
    projectionMatrix.matrixData[0][1] = 0;
    projectionMatrix.matrixData[0][2] = 0;
    projectionMatrix.matrixData[0][3] = 0;

    projectionMatrix.matrixData[1][0] = 0;
    projectionMatrix.matrixData[1][1] = view;
    projectionMatrix.matrixData[1][2] = 0;
    projectionMatrix.matrixData[1][3] = 0;

    projectionMatrix.matrixData[2][0] = 0;
    projectionMatrix.matrixData[2][1] = 0;
    projectionMatrix.matrixData[2][2] = -(far / (far - near));
    projectionMatrix.matrixData[2][3] = 1;

    projectionMatrix.matrixData[3][0] = 0;
    projectionMatrix.matrixData[3][1] = 0;
    projectionMatrix.matrixData[3][2] = -((far * near) / (far - near));
    projectionMatrix.matrixData[3][3] = 0;
    

    return projectionMatrix;
}

void Camera::ShowImGuiControls() {
    //TODO
}