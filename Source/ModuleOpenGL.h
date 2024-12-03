#pragma once
#include "Module.h"
#include "Globals.h"
#include <string>

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleOpenGL : public Module
{
public:
	ModuleOpenGL();
	~ModuleOpenGL();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void* context = nullptr;
	void WindowResized(unsigned width, unsigned height);
	float GetAspectRatio() const;
	
private:
	
};
