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
	bool IsTexture(const char* extension);
	bool buttonLeft;
	bool buttonRight;
	bool HandleButtonMouse(SDL_Event sdlEvents);
	void LoadNewModel(const char* fileName);
	void LoadNewTexture(const char* dir);
	
	update_status Update();

	void ProcessDropFile(const char* dropFile);

	bool CleanUp();
	
	float mouseX = 0;
	float mouseY = 0;
	bool wheelPress = false;
private:
	const Uint8 *keyboard = NULL;
	const Uint32 *mouse = NULL;
	float mouseWheel = 0;
	char* dropped_filedir;
	std::vector<const char*> extensions = { ".png", ".ppm", ".jpg", ".tga", ".dds", "jpeg", ".bpm"};
	char* result = nullptr;
	char* test = nullptr;
	bool mouseWarped = false;
	
};