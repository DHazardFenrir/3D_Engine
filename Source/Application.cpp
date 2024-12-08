#pragma once
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleOpenGL.h"
#include "ModuleInput.h"
#include "ModuleEditorCamera.h"
#include "ModuleDebugDraw.h"
#include "ModuleProgram.h"
#include "ModuleEditor.h"
#include "ModuleTexture.h"
#include "ModuleHardware.h"

#include "ModuleRenderExercise.h"

using namespace std;

Application::Application()
{
	// Order matters: they will Init/start/update in this order
	modules.push_back(window = new ModuleWindow());
	modules.push_back(render = new ModuleOpenGL());
	modules.push_back(input = new ModuleInput());
	modules.push_back(camera = new ModuleEditorCamera());
	modules.push_back(draw = new ModuleDebugDraw());
	modules.push_back(program = new ModuleProgram());
	modules.push_back(text = new ModuleTexture());
	modules.push_back(exercise = new ModuleRenderExercise());
	modules.push_back(info = new ModuleHardware());
	modules.push_back(GUI = new ModuleEditor());
	
	
}

Application::~Application()
{
	for(list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
    {
        delete *it;
    }
}

bool Application::Init()
{
	bool ret = true;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init();

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PreUpdate();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->Update();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		ret = (*it)->CleanUp();

	return ret;
}

void Application::RequestBrowser(const std::string& url)
{
	ShellExecuteA(nullptr, "open", url.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
}
