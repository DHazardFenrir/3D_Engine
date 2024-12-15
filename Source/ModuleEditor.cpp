#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL.h>
#include "ModuleEditor.h"
#include "ModuleWindow.h"
#include "ModuleOpenGL.h"
#include "Application.h"
#include "ModuleHardware.h"
#include "ModuleTexture.h"
#include "Logger.h"
#include "Globals.h"
#include <iostream>
#include "glew.h"
#include "ModuleLoadModel.h"

ModuleEditor::ModuleEditor() {

}

ModuleEditor::~ModuleEditor() {
	
}

bool ModuleEditor::Init() {
	InitializeFpsLog(200);
	InitializeMSLog(10);
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.Fonts->AddFontDefault();
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(App->GetWindow()->GetSDLWindow(), App->GetOpenGL()->context);
	ImGui_ImplOpenGL3_Init(glsl_version);
	
	
	

	
	
	return true;
}

update_status ModuleEditor::PreUpdate() {
	

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	 return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update() {

	{
	
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		if (aboutUI) 
		{
			ImGui::Begin("About Window");
			{
				
					RenderUI();
				
			}
			ImGui::End();

		}
		
		if (fpsUI) 
		{
			ImGui::Begin("Framerate & Miliseconds Window");
			{
				float currentFPS = io.Framerate;

				UpdateFpsLog(currentFPS);

				ImGui::Text("Application average (%.1f FPS)", currentFPS);
				ImGui::PlotHistogram(
					"Framerate",
					fpsLog.data(),
					FPS_LOG_SIZE,
					fpsIndex,
					nullptr,
					0.0f,
					*std::max_element(fpsLog.begin(), fpsLog.end()),
					ImVec2(0, 80)
				);

				float currentMS = 1000.0f / currentFPS;

				UpdateMSLog(currentMS);

				ImGui::Text("Application average %.3f ms/frame", currentMS);
				ImGui::PlotHistogram(
					"Miliseconds",
					msLog.data(),
					MS_LOG_SIZE,
					msLogIndex,
					nullptr,
					0.0f,
					*std::max_element(msLog.begin(), msLog.end()),
					ImVec2(0, 80)
				);
			}
			ImGui::End();
		}
		
		

		
			
		
		
		
	}

	UIControls();


	if (infoUI)
		App->GetInfo()->RenderUI();

	if (textureInfo)
		App->GetTxt()->RenderUI();

	if (moduleLoadUI)
		App->GetModuleLoad()->RenderUI();

	if (loggerUI)
		App->GetLogger()->LogConsole();

	if(exitProgram)
		App->Exit();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		return UPDATE_CONTINUE;
	}

void ModuleEditor::UIControls()
{
	if (ImGui::Begin("UI Controls"))
	{
		ImGui::Checkbox("Render Hardware Info UI", &infoUI);
		ImGui::Checkbox("Render Texture UI", &textureInfo);
		ImGui::Checkbox("Render Module Load UI", &moduleLoadUI);
		ImGui::Checkbox("Render Logger UI", &loggerUI);
		ImGui::Checkbox("Render About Window  UI", &aboutUI);
		ImGui::Checkbox("Render FPS Window  UI", &fpsUI);
		ImGui::Checkbox("Exit Program", &exitProgram);
	}
	ImGui::End();
}



update_status ModuleEditor::PostUpdate() {
	// Render main window
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	
	return UPDATE_CONTINUE;

	
}

bool ModuleEditor::CleanUp() 
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	fpsLog.clear();
	msLog.clear();
	fpsLog.shrink_to_fit();
	msLog.shrink_to_fit();
	return true;
}

void ModuleEditor::InitializeFpsLog(int size)
{
	FPS_LOG_SIZE = size;
	if (fpsLog.size() != FPS_LOG_SIZE) {
		fpsLog.resize(FPS_LOG_SIZE, 0.0f);
	}
}

void ModuleEditor::InitializeMSLog(int size)
{
	MS_LOG_SIZE = size;
	if (msLog.size() != MS_LOG_SIZE) {
		msLog.resize(MS_LOG_SIZE, 0.0f);
	}
}

void ModuleEditor::UpdateMSLog(float currentMS)
{
	msLog[msLogIndex] = currentMS;
	msLogIndex = (msLogIndex + 1) % MS_LOG_SIZE;
}

void ModuleEditor::UpdateFpsLog(float currentFPS)
{
	fpsLog[fpsIndex] = currentFPS;
	fpsIndex = (fpsIndex + 1) % FPS_LOG_SIZE;
}

void ModuleEditor::RenderUI()
{
	if (ImGui::CollapsingHeader("About")) 
	{
		if (ImGui::BeginTabBar("AboutTabs"))
		{
			if (ImGui::BeginTabItem("General Info"))
			{
				ImGui::Text("Name of Engine: %s", nameEngine.c_str());
				ImGui::Text("Description : %s", description.c_str());
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Author Info"))
			{
				ImGui::Text("Name of Author: %s", nameAuthor.c_str());
				ImGui::Text("Contact: example@example.com");
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Links"))
			{
				if (ImGui::Button("Visit GitHub"))
					App->RequestBrowser("https://github.com/DHazardFenrir/3D_Engine");

				if (ImGui::Button("Report an Issue"))
					App->RequestBrowser("https://github.com/DHazardFenrir/3D_Engine/issues");

				if (ImGui::Button("Documentation"))
					App->RequestBrowser("https://github.com/DHazardFenrir/3D_Engine/wiki");

				if (ImGui::Button("Download latest"))
					App->RequestBrowser("https://github.com/DHazardFenrir/3D_Engine");
				
				

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar(); 
		}
	}
	
}
