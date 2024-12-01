#include "Matx4x4.h"

Matx4x4 Matx4x4::Identity() {
    return Matx4x4();
}

Matx4x4 Matx4x4::RotateX(float angle) {
    Matx4x4 result = Matx4x4::Identity();
    float c = cos(angle);
    float s = sin(angle);
    result[1][1] = c;
    result[1][2] = -s;
    result[2][1] = s;
    result[2][2] = c;
    return result;
}

Matx4x4 Matx4x4::RotateY(float angle) {
    Matx4x4 result = Matx4x4::Identity();
    float c = cos(angle);
    float s = sin(angle);
    result[0][0] = c;
    result[0][2] = s;
    result[2][0] = -s;
    result[2][2] = c;
    return result;
}

Matx4x4 Matx4x4::RotateZ(float angle) {
    Matx4x4 result = Matx4x4::Identity();
    float c = cos(angle);
    float s = sin(angle);
    result[0][0] = c;
    result[0][1] = -s;
    result[1][0] = s;
    result[1][1] = c;
    return result;
}

Matx4x4 Matx4x4::Translation(float x, float y, float z) {
    Matx4x4 result = Matx4x4::Identity();
    result[0][3] = x;
    result[1][3] = y;
    result[2][3] = z;
    return result;
}
Matx4x4 Matx4x4::Scale(float x, float y, float z) {
    Matx4x4 result = Matx4x4::Identity();
    result[0][0] = x;
    result[1][1] = y;
    result[2][2] = z;
    return result;
}
Matx4x4 Matx4x4::RotateXYZ(float pitch, float yaw, float roll) {
    Matx4x4 rotateX = Matx4x4::RotateX(pitch);
    Matx4x4 rotateY = Matx4x4::RotateY(yaw);
    Matx4x4 rotateZ = Matx4x4::RotateZ(roll);

    
    return rotateX * rotateY * rotateZ;
}

Matx4x4 Matx4x4::Perspective(float fov, float aspect, float nearPlane, float farPlane) {
    Matx4x4 result = Matx4x4::Identity();

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
Matx4x4 Matx4x4::ModelMatrix(vec translation,vec rotation,vec scale) {
    // Crear matrices individuales
    Matx4x4 translationMatrix = Matx4x4::Translation(translation.x, translation.y, translation.z);
    Matx4x4 rotationMatrix = Matx4x4::RotateXYZ(rotation.x, rotation.y, rotation.z);
    Matx4x4 scaleMatrix = Matx4x4::Scale(scale.x, scale.y, scale.z);

    // Multiplicar en el orden adecuado (S * R * T)
    return scaleMatrix * rotationMatrix * translationMatrix;
}

Matx4x4 Matx4x4::BuildViewMatrix(vec position, float yaw, float pitch, float roll) {
    Matx4x4 rotation = Matx4x4::RotateZ(roll) *
        Matx4x4::RotateX(pitch) *
        Matx4x4::RotateY(yaw);

    Matx4x4 translation = Matx4x4::Translation(-position.x, -position.y, -position.z);

    return rotation * translation;
}