#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"
#include "Logger.h"
class ModuleOpenGL;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleEditorCamera;
class ModuleDebugDraw;
class ModuleRenderExercise;
class ModuleProgram;
class ModuleEditor;
class ModuleTexture;
class ModuleHardware;
class ModuleLoadModel;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

    
    ModuleWindow* GetWindow() { return window; }
    ModuleOpenGL* GetOpenGL() { return render; }
    ModuleInput*  GetInput() { return input; }
    ModuleProgram* GetProgram() { return program; }
    ModuleDebugDraw* GetDebugDraw() { return draw; }
    ModuleEditorCamera* GetCamera() { return camera; }
    ModuleEditor* GetGUI() { return  GUI; }
    ModuleTexture* GetTxt() { return text; }
    ModuleHardware* GetInfo() { return info; }
    ModuleLoadModel* GetModuleLoad() { return mesh; }
    ModuleRenderExercise* GetRender() { return exercise; }
    Logger* GetLogger() { return &logger; }
    void RequestBrowser(const std::string& url);
    void Exit();
    bool ShouldExit();

private:

    ModuleOpenGL* render = nullptr;
    ModuleWindow* window = nullptr;
    ModuleInput* input = nullptr;
    ModuleProgram* program = nullptr;
    ModuleRenderExercise* exercise = nullptr;
    ModuleDebugDraw* draw = nullptr;
    ModuleEditorCamera* camera = nullptr;
    ModuleEditor* GUI = nullptr;
    ModuleTexture* text = nullptr;
    ModuleHardware* info = nullptr;
    ModuleLoadModel* mesh = nullptr;
    Logger logger;
    std::list<Module*> modules;
    bool shouldExit = false;

};

extern Application* App;
