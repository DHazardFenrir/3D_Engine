#include "ModuleEditorCamera.h"
#include "Globals.h"
#include <iostream>
#include "Application.h"
#include "ModuleOpenGL.h"
#include "ModuleProgram.h"
#include "glew.h"
#include "debugdraw.h"
#include "ModuleDebugDraw.h"
#include "MathGeoLib.h"
#include "ModuleWindow.h"
#include "Math/float3.h"
#include "imgui.h"
#include <SDL.h>


ModuleEditorCamera::ModuleEditorCamera() 
{
	

}
ModuleEditorCamera::~ModuleEditorCamera() {

}

void ModuleEditorCamera::TraslateWithKeys() {

	if (App->GetInput()->GetKey(SDL_SCANCODE_W)) 
	{
		vec currentTranslation = currentFrustum->Front().Normalized() * cameraSpeed * deltaTime;
		currentFrustum->SetPos(currentFrustum->Pos() +  currentTranslation);
		std::cout << currentFrustum->Pos() << std::endl;
	}

	if (App->GetInput()->GetKey(SDL_SCANCODE_S))
	{
		vec currentTranslation = currentFrustum->Front().Normalized() * cameraSpeed * deltaTime;
		currentFrustum->SetPos(currentFrustum->Pos() - currentTranslation);
		std::cout << currentFrustum->Pos() << std::endl;
	}

	if (App->GetInput()->GetKey(SDL_SCANCODE_A))
	{
		vec currentTranslation = currentFrustum->WorldRight().Normalized() * cameraSpeed * deltaTime;
		currentFrustum->SetPos(currentFrustum->Pos() - currentTranslation);
		std::cout << currentFrustum->Pos() << std::endl;
	}

	if (App->GetInput()->GetKey(SDL_SCANCODE_D))
	{
		vec currentTranslation = currentFrustum->WorldRight().Normalized() * cameraSpeed * deltaTime;
		currentFrustum->SetPos(currentFrustum->Pos() + currentTranslation);
		std::cout << currentFrustum->Pos() << std::endl;
	}

	if (App->GetInput()->GetKey(SDL_SCANCODE_Q))
	{
		vec currentTranslation = currentFrustum->Up().Normalized() * cameraSpeed * deltaTime;
		currentFrustum->SetPos(currentFrustum->Pos() + currentTranslation);
		std::cout << currentFrustum->Pos() << std::endl;
	}

	if (App->GetInput()->GetKey(SDL_SCANCODE_E))
	{
		vec currentTranslation = currentFrustum->Up().Normalized() * cameraSpeed * deltaTime;
		currentFrustum->SetPos(currentFrustum->Pos() - currentTranslation);
		std::cout << "Move Front" << std::endl;
		std::cout << currentFrustum->Pos() << std::endl;
	}
}

void ModuleEditorCamera::TraslatWithMouse(int xrel, int yrel) {

	float rotationSpeed = 5.0f;

	float pitch = -yrel * rotationSpeed * deltaTime;  
	float yaw = -xrel * rotationSpeed * deltaTime;    

	
	Quat yawRotation = Quat::RotateY(DegToRad(yaw));
	float3 front = yawRotation * currentFrustum->Front();
	float3 up = yawRotation * currentFrustum->Up();

	
	float3 right = currentFrustum->WorldRight();
	Quat pitchRotation = Quat::RotateAxisAngle(right, DegToRad(pitch));
	front = pitchRotation * front;
	up = pitchRotation * up;

	
	currentFrustum->SetFront(front.Normalized());
	currentFrustum->SetUp(up.Normalized());
	

}

void ModuleEditorCamera::RotateWithArrows() {
	
	if (App->GetInput()->GetKey(SDL_SCANCODE_UP)) {
		
			float pitch = rotationSpeed * deltaTime;
			//float3x3 rotationMatrix = float3x3::RotateX(pitch);
			SetRotation(float3x3::RotateX(pitch));
			/*currentFrustum->SetFront(rotationMatrix * currentFrustum->Front());
			currentFrustum->SetUp(rotationMatrix * currentFrustum->Up());*/

			
		
		
		
		
	}

	if(App->GetInput()->GetKey(SDL_SCANCODE_DOWN)) {
		float pitch = -rotationSpeed * deltaTime;
		 SetRotation(float3x3::RotateX(pitch));

		

	}

	if (App->GetInput()->GetKey(SDL_SCANCODE_LEFT)) {
		float yaw = rotationSpeed * deltaTime;
		SetRotation(Quat::RotateY(yaw));

		
		
	}


	if (App->GetInput()->GetKey(SDL_SCANCODE_RIGHT)) {
		float yaw = -rotationSpeed * deltaTime;
		SetRotation( Quat::RotateY(yaw));

		
		
	}
}

bool ModuleEditorCamera::Init() {

	
	
	float aspectRatio = App->GetOpenGL()->GetAspectRatio();
	currentFrustum = &frustum;
	currentFrustum->SetKind(FrustumSpaceGL, FrustumRightHanded);
	currentFrustum->SetPos({ 0.0, 2.0, 10.0 });

	currentFrustum->SetFront(-float3::unitZ);
	currentFrustum->SetUp(float3::unitY);


	currentFrustum->SetViewPlaneDistances(0.1f, 1000.0f);
	currentFrustum->SetVerticalFovAndAspectRatio(math::pi / 4.0f, aspectRatio);
	return true;
}

update_status ModuleEditorCamera::PreUpdate() {
	 return UPDATE_CONTINUE;
}

update_status ModuleEditorCamera::Update() {
	static uint64_t previousFrame = SDL_GetPerformanceCounter();
    uint64_t currentFrame = SDL_GetPerformanceCounter();

    deltaTime = (double)(currentFrame - previousFrame) / SDL_GetPerformanceFrequency();
    fps = 1.0 / deltaTime;

    previousFrame = currentFrame;

	TraslateWithKeys();
	RotateWithArrows();
	
	
	float mouseWheelMotion = App->GetInput()->GetMouseWheelMotion();
	if (mouseWheelMotion != 0.0f && App->GetInput()->wheelPress)
	{
		std::cout << mouseWheelMotion << std::endl;
		Zoom(mouseWheelMotion * 0.5f);
		
		App->GetInput()->ResetMouse();
	}
	
	
	if (App->GetInput()->buttonLeft) 
	{
		TraslatWithMouse(App->GetInput()->mouseX, App->GetInput()->mouseY);
	}
	if (App->GetInput()->buttonRight) {
		Pan(App->GetInput()->mouseX, App->GetInput()->mouseY);
	}
		
		
	
	return UPDATE_CONTINUE;
}

update_status ModuleEditorCamera::PostUpdate() {
	return UPDATE_CONTINUE;
}

bool ModuleEditorCamera::CleanUp() {

	return true;
}

float4x4 ModuleEditorCamera::GetViewMatrix() const {

	return currentFrustum->ViewMatrix();
}

float4x4 ModuleEditorCamera::GetProjectionMatrix() const {

	return currentFrustum->ProjectionMatrix();
}

void ModuleEditorCamera::Zoom(float amount) 
{
	currentFrustum->SetPos(currentFrustum->Pos() + currentFrustum->Front().Normalized()* amount);
   
	std::cout << currentFrustum->Pos() << std::endl;
}

void ModuleEditorCamera::Pan(int xrel, int yrel) 
{
	
	float3 right = currentFrustum->WorldRight();
	float3 up = currentFrustum->Up();

	float3 deltaX = -right * (xrel * panSpeed * deltaTime);
	float3 deltaY = up * (yrel * panSpeed * deltaTime);

	currentFrustum->SetPos(currentFrustum->Pos() + (deltaX + deltaY));
}

void ModuleEditorCamera::SetFov(float fov)
{
	currentFrustum->SetHorizontalFovAndAspectRatio(fov / 4.0f, currentFrustum->AspectRatio());
}

void ModuleEditorCamera::SetAspectRatio(float aspectRatio)
{
	currentFrustum->SetVerticalFovAndAspectRatio(currentFrustum->VerticalFov(), aspectRatio);
}

void ModuleEditorCamera::SetPlaneDistance(float near, float far)
{
	currentFrustum->SetViewPlaneDistances(near, far);
}

void ModuleEditorCamera::SetPosition(float x, float y, float z)
{
	currentFrustum->SetPos({ x,y,z });
}

void ModuleEditorCamera::SetRotation(const float3x3 rotationMtx)
{
	currentFrustum->SetFront(rotationMtx * currentFrustum->Front());
	currentFrustum->SetUp(rotationMtx * currentFrustum->Up());
}

void ModuleEditorCamera::SetRotation(const Quat rotationQuat) {
	
	float3 newFront = rotationQuat * currentFrustum->Front();
	float3 newUp = rotationQuat * currentFrustum->Up();


	currentFrustum->SetFront(newFront.Normalized());
	currentFrustum->SetUp(newUp.Normalized());
}

void ModuleEditorCamera::ResizeWindow(int width, int height)
{
	SetAspectRatio((float)width / (float(height)));
}

void ModuleEditorCamera::LookAt(float x, float y, float z)
{
	vec direction = vec(x, y, z) - currentFrustum->Pos();
	direction.Normalize();
	vec up = vec::unitY;

	// Special case for when looking straight up
	if (direction.Cross(up).IsZero())
	{
		up = vec::unitZ;
	}

	Rotate(float3x3::LookAt(currentFrustum->Front().Normalized(), direction, currentFrustum->Up().Normalized(), up));
	
	
	

}
void ModuleEditorCamera::Rotate(const float3x3& rotationMatrix)
{
	vec oldFront = currentFrustum->Front().Normalized();
	vec oldUp = currentFrustum->Up().Normalized();
	currentFrustum->SetFront(rotationMatrix * oldFront);
	currentFrustum->SetUp(rotationMatrix * oldUp);
}


