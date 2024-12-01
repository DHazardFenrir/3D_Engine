#pragma once
#include "Module.h"
#include "MathGeoLib.h"
#include "Globals.h"
#include "SDL.h"

typedef unsigned __int8 Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();
	bool GetKey(SDL_Scancode scancode);
	bool GetMouse(SDL_EventType  mouseScan);
	bool Init();
	float GetMouseWheelMotion() const;

	const float2& GetMouseMotion() const;
	const float2& GetMousePosition() const;
	update_status Update();

	bool CleanUp();
	
	float mouseX = 0;
	float mouseY = 0;
private:
	const Uint8 *keyboard = NULL;
	const Uint32 *mouse = NULL;
	float mouseWheel = 0;
	float2 mouseMotion = { 0, 0 };
	float2 mousePos = { 0, 0 };
	bool mouseWarped = false;
	
};