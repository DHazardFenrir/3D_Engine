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
	void ResetMouse();
	bool buttonLeft;
	bool buttonRight;
	bool HandleButtonMouse(SDL_Event sdlEvents);
	
	
	update_status Update();

	bool CleanUp();
	
	float mouseX = 0;
	float mouseY = 0;
	bool wheelPross = false;
private:
	const Uint8 *keyboard = NULL;
	const Uint32 *mouse = NULL;
	float mouseWheel = 0;
	
	bool mouseWarped = false;
	
};