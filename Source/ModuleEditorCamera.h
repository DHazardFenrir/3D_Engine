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
	void TraslatWithMouse(int xrel, int yrel);
	void RotateWithMouse();
	void RotateWithArrows();
	bool Init();
	void Pan(int xrel, int yrel);
	//Frustum* GetFrustum();
	float4x4 GetProjectionMatrix() const;
	float4x4 GetViewMatrix() const;
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	void Zoom(float amount);
	inline float DegToRad(float degrees) {
		return degrees * 0.0174532925f; // Grados a radianes
	}
	 bool CleanUp()override;

private:
	Frustum frustum = Frustum();
	Frustum* currentFrustum = nullptr;
	float cameraSpeed = 5.0f;
	double deltaTime = 0;
	double fps = 0;
	Uint64 startFrame = 0;
	Uint64 lastFrame = 0;
	float rotationSpeed = 0.5f;
	float focusDistance = 0.0f;
	
};

