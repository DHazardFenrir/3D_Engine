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
	void UIControls();
	update_status PostUpdate();
	bool CleanUp();
	void InitializeFpsLog(int size);
	void InitializeMSLog(int size);
	void UpdateMSLog(float currentMS);
	void UpdateFpsLog(float currentFPS);
	void RenderUI() override;
	const char* glsl_version = "#version 460";
	bool infoUI = true;
	bool textureInfo = true;
	bool moduleLoadUI = true;
	bool loggerUI = true;
	bool aboutUI = true;
	bool fpsUI = true;
	bool exitProgram = false;
	std::string nameEngine = "Cerberus Engine";
	std::string description = "3D Engine for UPC Master";
	std::string nameAuthor = "Dulce Maria Zapata Olivares";
	
private:
	int FPS_LOG_SIZE = 200;                
	std::vector<float> fpsLog;           
	int fpsIndex = 0;

	int MS_LOG_SIZE = 10;
	std::vector<float> msLog;
	int msLogIndex;
	
};

