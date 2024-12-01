#include "Mat4x4.h"


Mat4x4 Mat4x4::Identity() {
    return Mat4x4();
}

Mat4x4 Mat4x4::RotateX(float angle) {
    Mat4x4 result = Mat4x4::Identity();
    float c = cos(angle);
    float s = sin(angle);
    result[1][1] = c;
    result[1][2] = -s;
    result[2][1] = s;
    result[2][2] = c;
    return result;
}

Mat4x4 Mat4x4::RotateY(float angle) {
    Mat4x4 result = Mat4x4::Identity();
    float c = cos(angle);
    float s = sin(angle);
    result[0][0] = c;
    result[0][2] = s;
    result[2][0] = -s;
    result[2][2] = c;
    return result;
}

Mat4x4 Mat4x4::RotateZ(float angle) {
    Mat4x4 result = Mat4x4::Identity();
    float c = cos(angle);
    float s = sin(angle);
    result[0][0] = c;
    result[0][1] = -s;
    result[1][0] = s;
    result[1][1] = c;
    return result;
}

Mat4x4 Mat4x4::Translation(float x, float y, float z) {
    Mat4x4 result = Mat4x4::Identity();
    result[0][3] = x;
    result[1][3] = y;
    result[2][3] = z;
    return result;
}
Mat4x4 Mat4x4::Scale(float x, float y, float z) {
    Mat4x4 result = Mat4x4::Identity();
    result[0][0] = x;
    result[1][1] = y;
    result[2][2] = z;
    return result;
}
Mat4x4 Mat4x4::RotateXYZ(float pitch, float yaw, float roll) {
    Mat4x4 rotateX = Mat4x4::RotateX(pitch);
    Mat4x4 rotateY = Mat4x4::RotateY(yaw);
    Mat4x4 rotateZ = Mat4x4::RotateZ(roll);

    
    return rotateX * rotateY * rotateZ;
}

Mat4x4 Mat4x4::Perspective(float fov, float aspect, float nearPlane, float farPlane) {
    Mat4x4 result = {};

    float tanHalfFOV = tan(fov / 2.0f);
    float range = farPlane - nearPlane;

    result[0][0] = 1.0f / (aspect * tanHalfFOV);
    result[1][1] = 1.0f / tanHalfFOV;
    result[2][2] = -(farPlane + nearPlane) / range;
    result[2][3] = -1.0f;
    result[3][2] = -(2.0f * farPlane * nearPlane) / range;
    result[3][3] = 0.0f;

    return result;
}
Mat4x4 Mat4x4::ModelMatrix(vec translation,vec rotation,vec scale) {
    // Crear matrices individuales
    Mat4x4 translationMatrix = Mat4x4::Translation(translation.x, translation.y, translation.z);
    Mat4x4 rotationMatrix = Mat4x4::RotateXYZ(rotation.x, rotation.y, rotation.z);
    Mat4x4 scaleMatrix = Mat4x4::Scale(scale.x, scale.y, scale.z);

    // Multiplicar en el orden adecuado (S * R * T)
    return translationMatrix * rotationMatrix * scaleMatrix;
}