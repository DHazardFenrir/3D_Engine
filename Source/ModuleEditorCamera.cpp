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
			float3x3 rotationMatrix = float3x3::RotateX(pitch);

			currentFrustum->SetFront(rotationMatrix * currentFrustum->Front());
			currentFrustum->SetUp(rotationMatrix * currentFrustum->Up());

			std::cout << currentFrustum->Up() << std::endl;
			std::cout << currentFrustum->Front() << std::endl;
		
		
		
		
	}

	if(App->GetInput()->GetKey(SDL_SCANCODE_DOWN)) {
		float pitch = -rotationSpeed * deltaTime;
		float3x3 rotationMatrix = float3x3::RotateX(pitch);

		currentFrustum->SetFront(rotationMatrix * currentFrustum->Front());
		currentFrustum->SetUp(rotationMatrix * currentFrustum->Up());

	}

	if (App->GetInput()->GetKey(SDL_SCANCODE_LEFT)) {
		float yaw = rotationSpeed * deltaTime;

		
		float3 worldUp = float3::unitY; 
		Quat rotationQuat = Quat::RotateY(yaw);

		
		float3 newFront = rotationQuat * currentFrustum->Front();
		float3 newUp = rotationQuat * currentFrustum->Up();

		
		currentFrustum->SetFront(newFront.Normalized());
		currentFrustum->SetUp(newUp.Normalized());
	}


	if (App->GetInput()->GetKey(SDL_SCANCODE_RIGHT)) {
		float yaw = -rotationSpeed * deltaTime;

		
		float3 worldUp = float3::unitY; 
		Quat rotationQuat = Quat::RotateY(yaw);

		
		float3 newFront = rotationQuat * currentFrustum->Front();
		float3 newUp = rotationQuat * currentFrustum->Up();

		
		currentFrustum->SetFront(newFront.Normalized());
		currentFrustum->SetUp(newUp.Normalized());
	}
}

bool ModuleEditorCamera::Init() {

	
	
	float aspectRatio = App->GetOpenGL()->GetAspectRatio();
	currentFrustum = &frustum;
	currentFrustum->SetKind(FrustumSpaceGL, FrustumRightHanded);
	currentFrustum->SetPos({ 0.0, 2.0, 10.0 });

	currentFrustum->SetFront(-float3::unitZ);
	currentFrustum->SetUp(float3::unitY);


	currentFrustum->SetViewPlaneDistances(0.1f, 100.0f);
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
	
	
	float mouseMotion = App->GetInput()->GetMouseWheelMotion();
	if (mouseMotion != 0.0f && App->GetInput()->wheelPross)
	{
		std::cout << mouseMotion << std::endl;
		Zoom(mouseMotion * 0.5f);
		
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

void ModuleEditorCamera::Zoom(float amount) {
	//vec currentTranslation = currentFrustum->Front().Normalized() * cameraSpeed * deltaTime;
	currentFrustum->SetPos(currentFrustum->Pos() + currentFrustum->Front().Normalized()* amount);
   
	std::cout << currentFrustum->Pos() << std::endl;
}

void ModuleEditorCamera::Pan(int xrel, int yrel) {
	float panSpeed = 0.1f;
	float3 right = currentFrustum->WorldRight();
	float3 up = currentFrustum->Up();

	float3 deltaX = -right * (xrel * panSpeed * deltaTime);
	float3 deltaY = up * (yrel * panSpeed * deltaTime);

	currentFrustum->SetPos(currentFrustum->Pos() + (deltaX + deltaY));
}