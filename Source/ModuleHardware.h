#pragma once
#include "Module.h"
class ModuleHardware: public Module
{
public:
	ModuleHardware();
	~ModuleHardware();
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	void GetGPUInfo();
	bool CleanUp();
	void RenderUI();
	float sdlVersion;
	int cpus;
	float systemRam;
	const GLubyte* renderer;
	const GLubyte* vendor;
	int totalMemory = 0;
	int freeMemory = 0;
	int texFreeMemory = 0;
};

