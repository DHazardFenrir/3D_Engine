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
	float pitch = yrel * rotationSpeed; // Rotación alrededor del eje X
	float yaw = xrel * rotationSpeed;   // Rotación alrededor del eje Y

	// Rotar la dirección de la cámara
	float3 front = currentFrustum->Front();
	float3 up = currentFrustum->Up();

	// Aplicar rotación Yaw (alrededor del eje Y, arriba)
	Quat yawRotation = Quat::RotateY(DegToRad(yaw));
	front = yawRotation.Mul(front).Normalized();
	up = yawRotation.Mul(up).Normalized();

	// Aplicar rotación Pitch (alrededor del eje X, derecha)
	float3 right = currentFrustum->WorldRight();
	Quat pitchRotation = Quat::RotateAxisAngle(right, DegToRad(pitch));
	front = pitchRotation.Mul(front).Normalized();
	up = pitchRotation.Mul(up).Normalized();

	// Actualizar el Frustum con los nuevos vectores
	currentFrustum->SetFront(front);
	currentFrustum->SetUp(up);
	

}

void ModuleEditorCamera::RotateWithArrows() {
	 // Velocidad de rotación

	// Detecta la entrada de las teclas
	if (App->GetInput()->GetKey(SDL_SCANCODE_UP)) {
		float pitch = rotationSpeed * deltaTime;
		float3x3 rotationMatrix = float3x3::RotateX(pitch);

		currentFrustum->SetFront(rotationMatrix * currentFrustum->Front());
		currentFrustum->SetUp(  rotationMatrix * currentFrustum->Up());
		
	}

	if(App->GetInput()->GetKey(SDL_SCANCODE_DOWN)) {
		float pitch = -rotationSpeed * deltaTime;
		float3x3 rotationMatrix = float3x3::RotateX(pitch);

		currentFrustum->SetFront(rotationMatrix * currentFrustum->Front());
		currentFrustum->SetUp(rotationMatrix * currentFrustum->Up());

	}

	if (App->GetInput()->GetKey(SDL_SCANCODE_LEFT)) {
		float yaw = rotationSpeed * deltaTime;

		// Crea una matriz de rotación alrededor del eje Y (mundo)
		float3 worldUp = float3::unitY; // Eje Y del mundo
		Quat rotationQuat = Quat::RotateY(yaw);

		// Aplica la rotación al frente de la cámara
		float3 newFront = rotationQuat * currentFrustum->Front();
		float3 newUp = rotationQuat * currentFrustum->Up();

		// Actualiza el frustum
		currentFrustum->SetFront(newFront.Normalized());
		currentFrustum->SetUp(newUp.Normalized());
	}


	if (App->GetInput()->GetKey(SDL_SCANCODE_RIGHT)) {
		float yaw = -rotationSpeed * deltaTime;

		// Crea una matriz de rotación alrededor del eje Y (mundo)
		float3 worldUp = float3::unitY; // Eje Y del mundo
		Quat rotationQuat = Quat::RotateY(yaw);

		// Aplica la rotación al frente de la cámara
		float3 newFront = rotationQuat * currentFrustum->Front();
		float3 newUp = rotationQuat * currentFrustum->Up();

		// Actualiza el frustum
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
	TraslatWithMouse(App->GetInput()->mouseX, App->GetInput()->mouseY);
	float mouseMotion = App->GetInput()->GetMouseWheelMotion();
	if (mouseMotion < -FLT_EPSILON || mouseMotion > FLT_EPSILON)
	{
		Zoom(mouseMotion * 0.01f);
		std::cout << "Mous2" << std::endl;
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

}