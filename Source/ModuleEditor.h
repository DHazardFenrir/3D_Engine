#pragma once
#include "Module.h"

class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor();
	bool Init();

	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	const char* glsl_version = "#version 460";
	bool show_demo_window = true;
};

