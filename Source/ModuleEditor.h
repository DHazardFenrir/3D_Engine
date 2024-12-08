#pragma once
#include "Module.h"
      
class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor();
	bool Init();
	bool ShouldProcessMouse() const;
	bool ShouldProcessKeyboard() const;
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void InitializeFpsLog(int size);
	void InitializeMSLog(int size);
	void UpdateMSLog(float currentMS);
	void UpdateFpsLog(float currentFPS);
	void RenderUI() override;
	const char* glsl_version = "#version 460";
	bool show_demo_window = true;
	bool show_another_window = false;
	std::string nameEngine = "Cerberus Engine";
	std::string description = "3D Engine for UPC Master";
	std::string nameAuthor = "Damian Zapata";
	int FPS_LOG_SIZE = 200;                
	std::vector<float> fpsLog;           
	int fpsIndex = 0;

	int MS_LOG_SIZE = 10;
	std::vector<float> msLog;
	int msLogIndex;
	
};

