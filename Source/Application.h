#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleOpenGL;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleEditorCamera;
class ModuleDebugDraw;
class ModuleRenderExercise;
class ModuleProgram;


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

private:

    ModuleOpenGL* render = nullptr;
    ModuleWindow* window = nullptr;
    ModuleInput* input = nullptr;
    ModuleProgram* program = nullptr;
    ModuleRenderExercise* exercise = nullptr;
    ModuleDebugDraw* draw = nullptr;
    ModuleEditorCamera* camera = nullptr;
    std::list<Module*> modules;

};

extern Application* App;
