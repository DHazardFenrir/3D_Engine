#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL.h>
#include "ModuleEditor.h"
#include "ModuleWindow.h"
#include "ModuleOpenGL.h"
#include "Application.h"
#include "Globals.h"
#include <iostream>
#include "glew.h"

ModuleEditor::ModuleEditor() {

}

ModuleEditor::~ModuleEditor() {

}

bool ModuleEditor::Init() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.Fonts->AddFontDefault();
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(App->GetWindow()->GetSDLWindow(), App->GetOpenGL()->context);
	ImGui_ImplOpenGL3_Init(glsl_version);
	
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	
	
	return true;
}

update_status ModuleEditor::PreUpdate() {
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	 return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update() {
	
	
	// Build UI
	ImGui::Begin("Demo Window");
	ImGui::Text("Hello, world!");
	ImGui::End();
	

	// Render ImGui data
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate() {
	// Render main window
	SDL_GL_SwapWindow(App->GetWindow()->window);
	
	
	
	return UPDATE_CONTINUE;

	
}

bool ModuleEditor::CleanUp() 
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	return true;
}