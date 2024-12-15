#pragma once
#include "Globals.h"
#include <iostream>
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleOpenGL.h"
#include "MathGeoLib.h"
#include "Math/float3.h"
#include "SDL.h"
class ModuleEditorCamera : public Module
{
public:
	ModuleEditorCamera();
	~ModuleEditorCamera();
	void TraslateWithKeys();
	void MoveDown();
	void MoveUp(float effectiveSpeed);
	void MoveRight(float effectiveSpeed);
	void MoveLeft(float effectiveSpeed);
	void MoveBackwards(float effectiveSpeed);
	void MoveForward(float effectiveSpeed);
	void TraslatWithMouse(int xrel, int yrel);
	void RotateWithArrows();
	bool Init();
	void Pan(int xrel, int yrel);
	void SetFov(float fov);
	void SetAspectRatio(float aspectRatio);
	void SetPlaneDistance(float nearPlane, float farPlane);
	void SetPosition(float x, float y, float z);
	void SetRotation(const float3x3 rotationMtx);
	void SetRotation(const Quat rotationMtx);
	void ResizeWindow(int width, int height);
	void LookAt(float x, float y, float z);
	void Orbit(float xrel, float yrel, float radius);
	void Rotate(const float3x3& rotationMatrix);
	void Focus();
	float4x4 GetProjectionMatrix() const;
	void UpdateProjectionMatrix(float aspectRatio);
	float4x4 GetViewMatrix() const;
	update_status PreUpdate();
	update_status Update();
	void OrbitCamera();
	void FocusCamera();
	void RotateAndPanCamera();
	void MouseZoom();
	update_status PostUpdate();
	void Zoom(float amount);
	inline float DegToRad(float degrees) {
		return degrees * 0.0174532925f; // Grados a radianes
	}
	bool CleanUp();
	

private:
	Frustum frustum = Frustum();
	Frustum* currentFrustum = &frustum;
	float cameraSpeed = 2.0f;
	double deltaTime = 0;
	double fps = 0;
	Uint64 startFrame = 0;
	Uint64 lastFrame = 0;
	float rotationSpeed = 0.5f;
	float panSpeed = 0.1;
	vec cameraPosition;
	float nearPlane = 0.1f;
	float farPlane = 100.0f;
	float verticalFov = math::pi / 4.0f;
	float rotationOrbit = 2.0f;
	float focusDistance = 5.0f;

	float currentPitch = 0.0f; 
	float currentYaw = 0.0f;   
	const float maxPitch = 45.0f; 
	const float maxYaw = 45.0f;   
};

