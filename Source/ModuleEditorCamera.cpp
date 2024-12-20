#include "ModuleEditorCamera.h"
#include "Globals.h"
#include <iostream>
#include "Application.h"
#include "ModuleOpenGL.h"
#include "ModuleProgram.h"
#include "glew.h"
#include "debugdraw.h"
#include "ModuleDebugDraw.h"
#include "ModuleLoadModel.h"
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
	float effectiveSpeed = cameraSpeed;
	if (App->GetInput()->GetKey(SDL_SCANCODE_LSHIFT) || App->GetInput()->GetKey(SDL_SCANCODE_RSHIFT)) {
		effectiveSpeed *= 5.0f; 
	}
	MoveForward(effectiveSpeed);
	MoveBackwards(effectiveSpeed);

	MoveLeft(effectiveSpeed);

	MoveRight(effectiveSpeed);

	MoveUp(effectiveSpeed);

	MoveDown();
}

void ModuleEditorCamera::MoveDown()
{
	if (App->GetInput()->GetKey(SDL_SCANCODE_E))
	{
		vec currentTranslation = currentFrustum->Up().Normalized() * cameraSpeed * deltaTime;
		currentFrustum->SetPos(currentFrustum->Pos() - currentTranslation);
		std::cout << "Move Front" << std::endl;
		std::cout << currentFrustum->Pos() << std::endl;
	}
}

void ModuleEditorCamera::MoveUp(float effectiveSpeed)
{
	if (App->GetInput()->GetKey(SDL_SCANCODE_Q))
	{
		vec currentTranslation = currentFrustum->Up().Normalized() * effectiveSpeed * deltaTime;
		currentFrustum->SetPos(currentFrustum->Pos() + currentTranslation);
		std::cout << currentFrustum->Pos() << std::endl;
	}
}

void ModuleEditorCamera::MoveRight(float effectiveSpeed)
{
	if (App->GetInput()->GetKey(SDL_SCANCODE_D))
	{
		vec currentTranslation = currentFrustum->WorldRight().Normalized() * effectiveSpeed * deltaTime;
		currentFrustum->SetPos(currentFrustum->Pos() + currentTranslation);
		std::cout << currentFrustum->Pos() << std::endl;
	}
}

void ModuleEditorCamera::MoveLeft(float effectiveSpeed)
{
	if (App->GetInput()->GetKey(SDL_SCANCODE_A))
	{
		vec currentTranslation = currentFrustum->WorldRight().Normalized() * effectiveSpeed * deltaTime;
		currentFrustum->SetPos(currentFrustum->Pos() - currentTranslation);
		std::cout << currentFrustum->Pos() << std::endl;
	}
}

void ModuleEditorCamera::MoveBackwards(float effectiveSpeed)
{

	if (App->GetInput()->GetKey(SDL_SCANCODE_S))
	{
		vec currentTranslation = currentFrustum->Front().Normalized() * effectiveSpeed * deltaTime;
		currentFrustum->SetPos(currentFrustum->Pos() - currentTranslation);
		std::cout << currentFrustum->Pos() << std::endl;
	}
}

void ModuleEditorCamera::MoveForward(float effectiveSpeed)
{
	if (App->GetInput()->GetKey(SDL_SCANCODE_W))
	{
		vec currentTranslation = currentFrustum->Front().Normalized() * effectiveSpeed * deltaTime;
		currentFrustum->SetPos(currentFrustum->Pos() + currentTranslation);
		std::cout << currentFrustum->Pos() << std::endl;
	}
}

void ModuleEditorCamera::TraslatWithMouse(int xrel, int yrel) {

	float localrotationSpeed = 5.0f;

	
	float pitchChange = -yrel * localrotationSpeed * deltaTime;
	float yawChange = -xrel * localrotationSpeed * deltaTime;

	
	float newPitch = currentPitch + pitchChange;
	if (newPitch > maxPitch) {
		pitchChange = maxPitch - currentPitch;
		newPitch = maxPitch;
	}
	else if (newPitch < -maxPitch) {
		pitchChange = -maxPitch - currentPitch;
		newPitch = -maxPitch;
	}
	currentPitch = newPitch;

	
	float newYaw = currentYaw + yawChange;
	if (newYaw > maxYaw) {
		yawChange = maxYaw - currentYaw;
		newYaw = maxYaw;
	}
	else if (newYaw < -maxYaw) {
		yawChange = -maxYaw - currentYaw;
		newYaw = -maxYaw;
	}
	currentYaw = newYaw;

	
	Quat yawRotation = Quat::RotateY(DegToRad(yawChange));
	float3 front = yawRotation * currentFrustum->Front();
	float3 up = yawRotation * currentFrustum->Up();

	float3 right = currentFrustum->WorldRight();
	Quat pitchRotation = Quat::RotateAxisAngle(right, DegToRad(pitchChange));
	front = pitchRotation * front;
	up = pitchRotation * up;

	currentFrustum->SetFront(front.Normalized());
	currentFrustum->SetUp(up.Normalized());

}

void ModuleEditorCamera::RotateWithArrows() {

	if (App->GetInput()->GetKey(SDL_SCANCODE_UP)) {

		float pitchChange = rotationSpeed * deltaTime;
		if (currentPitch + pitchChange <= maxPitch) {
			currentPitch += pitchChange;
			SetRotation(float3x3::RotateX(pitchChange));
		}
	}

	if (App->GetInput()->GetKey(SDL_SCANCODE_DOWN)) {
		float pitchChange = -rotationSpeed * deltaTime;
		if (currentPitch + pitchChange >= -maxPitch) {
			currentPitch += pitchChange;
			SetRotation(float3x3::RotateX(pitchChange));
		}



	}

	if (App->GetInput()->GetKey(SDL_SCANCODE_LEFT)) {
		float yawChange = rotationSpeed * deltaTime;
		if (currentYaw + yawChange <= maxYaw) {
			currentYaw += yawChange;
			SetRotation(Quat::RotateY(yawChange));
		}



	}


	if (App->GetInput()->GetKey(SDL_SCANCODE_RIGHT)) {
		float yawChange = -rotationSpeed * deltaTime;
		if (currentYaw + yawChange >= -maxYaw) {
			currentYaw += yawChange;
			SetRotation(Quat::RotateY(yawChange));



		}
	}
}

	bool ModuleEditorCamera::Init() {



		float aspectRatio = App->GetOpenGL()->GetAspectRatio();
		currentFrustum->SetKind(FrustumSpaceGL, FrustumRightHanded);
		currentFrustum->SetPos({ 0.0, 2.0, 10.0 });

		currentFrustum->SetFront(-float3::unitZ);
		currentFrustum->SetUp(float3::unitY);


		currentFrustum->SetViewPlaneDistances(nearPlane, farPlane);
		currentFrustum->SetVerticalFovAndAspectRatio(verticalFov, aspectRatio);
		return true;
	}

	update_status ModuleEditorCamera::PreUpdate() {
		return UPDATE_CONTINUE;
	}

	update_status ModuleEditorCamera::Update() {

		ImGuiIO& io = ImGui::GetIO();


		if (io.WantCaptureMouse || io.WantCaptureKeyboard) {
			return UPDATE_CONTINUE;
		}
		static uint64_t previousFrame = SDL_GetPerformanceCounter();
		uint64_t currentFrame = SDL_GetPerformanceCounter();

		deltaTime = (double)(currentFrame - previousFrame) / SDL_GetPerformanceFrequency();
		fps = 1.0 / deltaTime;

		previousFrame = currentFrame;

		FocusCamera();

		if (App->GetInput()->WarpMouse())
		{
			TraslateWithKeys();
			RotateWithArrows();

			OrbitCamera();

			MouseZoom();


			RotateAndPanCamera();

		}



		return UPDATE_CONTINUE;
	}


void ModuleEditorCamera::OrbitCamera()
{
	if (App->GetInput()->GetKey(SDL_SCANCODE_LALT))
	{
		Orbit(App->GetInput()->mouseX, App->GetInput()->mouseY, 10.0f);
	}
}

void ModuleEditorCamera::FocusCamera()
{
	if (App->GetInput()->GetKey(SDL_SCANCODE_F))
	{
		Focus();
	}
}

void ModuleEditorCamera::RotateAndPanCamera()
{
	if (App->GetInput()->buttonLeft)
	{
		TraslatWithMouse(App->GetInput()->mouseX, App->GetInput()->mouseY);
	}
	if (App->GetInput()->buttonRight) {
		Pan(App->GetInput()->mouseX, App->GetInput()->mouseY);
	}
}

void ModuleEditorCamera::MouseZoom()
{
	float mouseWheelMotion = App->GetInput()->GetMouseWheelMotion();
	if (mouseWheelMotion != 0.0f && App->GetInput()->wheelPress)
	{
		std::cout << mouseWheelMotion << std::endl;
		Zoom(mouseWheelMotion * 0.5f);

		App->GetInput()->ResetMouse();
	}
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

void ModuleEditorCamera::UpdateProjectionMatrix(float aspectRatio)
{
	 currentFrustum->SetVerticalFovAndAspectRatio(verticalFov, aspectRatio);
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
	UpdateProjectionMatrix(aspectRatio);
}

void ModuleEditorCamera::SetPlaneDistance(float nearPlane, float farPlane)
{
	currentFrustum->SetViewPlaneDistances(nearPlane, farPlane);
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
	
	float aspectRatio = (float)width / (float)height;
	SetAspectRatio(aspectRatio);
	
	
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
void ModuleEditorCamera::Orbit(float xrel, float yrel, float radius)
{
	if (!App->GetInput()->WarpMouse()) return; 
	float yaw = -xrel * rotationOrbit * deltaTime;
	float pitch = -yrel * rotationOrbit * deltaTime;

	float3 modelPos = App->GetModuleLoad()->GetModelTranslation();
	Quat yawRotation = Quat::RotateY(DegToRad(yaw));
	Quat pitchRotation = Quat::RotateAxisAngle(currentFrustum->WorldRight(), DegToRad(pitch));

	float3 direction = (currentFrustum->Pos() - modelPos).Normalized();
	direction = yawRotation * pitchRotation * direction;

	currentFrustum->SetPos(modelPos + direction * radius);
	LookAt(modelPos.x, modelPos.y, modelPos.z);
}
void ModuleEditorCamera::Rotate(const float3x3& rotationMatrix)
{
	vec oldFront = currentFrustum->Front().Normalized();
	vec oldUp = currentFrustum->Up().Normalized();
	currentFrustum->SetFront(rotationMatrix * oldFront);
	currentFrustum->SetUp(rotationMatrix * oldUp);
}

void ModuleEditorCamera::Focus()
{
	float3 modelPos = App->GetModuleLoad()->GetModelTranslation();
	float3 direction = (currentFrustum->Pos() - modelPos).Normalized();

	
	currentFrustum->SetPos(modelPos + direction * focusDistance);
	LookAt(modelPos.x, modelPos.y, modelPos.z);
}


