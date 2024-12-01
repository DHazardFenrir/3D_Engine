#pragma once
#include "MathGeoLib.h"

class Matx4x4
{
public:
	Matx4x4() {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (i == j) {
					data[i][j] = 1.0f;  // Los elementos de la diagonal son 1
				}
				else {
					data[i][j] = 0.0f;  // Los elementos fuera de la diagonal son 0
				}
			}
		}
	}
	~Matx4x4() {}
	static Matx4x4 Identity();
	static Matx4x4 RotateX(float angle);
	static Matx4x4 RotateY(float angle);
	static Matx4x4 RotateZ(float angle);
	static Matx4x4 Translation(float x, float y, float z);
	static Matx4x4 Scale(float sx, float sy, float sz);
	static Matx4x4 ModelMatrix(vec position, vec scale, vec rotation);
	static Matx4x4 RotateXYZ(float angleX, float angleY, float angleZ);
	static Matx4x4 Perspective(float fov, float aspect, float nearPlane, float farPlane);
	static Matx4x4 BuildViewMatrix(vec position, float yaw, float pitch, float roll);
	//Mat4x4 ViewMatrix

	Matx4x4 operator*(const Matx4x4& other) const {
		Matx4x4 result;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				result.data[i][j] = 0;
				for (int k = 0; k < 4; ++k)
					result.data[i][j] += data[i][k] * other.data[k][j];
			}
		}
		return result;
	}
	float* operator[](int row) { return data[row]; }
	const float* operator[](int row) const { return data[row]; }

private:
	float data[4][4]; 
};

