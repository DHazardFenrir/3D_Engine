#include "Globals.h"
#include <iostream>
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleOpenGL.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "glew.h"

ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

bool ModuleInput::GetKey(SDL_Scancode scancode) {
    return keyboard[scancode];
}
bool ModuleInput::GetMouse(SDL_EventType mouseScan) {
    return mouse[mouseScan];
}
// Called before render is available
bool ModuleInput::Init()
{
	std::cout<<"Init SDL input event system";
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
    std::cout<< "SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError();
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
    SDL_Event sdlEvent;


    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                return UPDATE_STOP;
            case SDL_WINDOWEVENT:
                if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    App->GetOpenGL()->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
                if (SDL_GetWindowFlags(App->GetWindow()->GetSDLWindow()) & SDL_WINDOW_MINIMIZED)
                {
                    SDL_Delay(10);
                    continue;
                }
                break;
            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_LALT || sdlEvent.key.keysym.sym == SDLK_RALT) {
                    std::cout << "Alt presionado" << std::endl;
                }
                
                break;

            case SDL_MOUSEMOTION:
                if (SDL_GetMouseState(NULL, NULL)) {
                    HandleButtonMouse(sdlEvent);
                    float xrel = sdlEvent.motion.xrel;
                    float yrel = sdlEvent.motion.yrel;
                    std::cout << xrel << std::endl;
                    std::cout << yrel << std::endl;
                    mouseX = xrel;
                    mouseY = yrel;
                }
                else {
                    mouseX = 0;
                    mouseY = 0;
                }
                 
                
                break;

            case SDL_MOUSEWHEEL:
                if (sdlEvent.wheel.direction == SDL_MOUSEWHEEL_FLIPPED)
                {
                    mouseWheel = (float)sdlEvent.wheel.x;
                    
                }
                else
                {
                    mouseWheel = (float)sdlEvent.wheel.y;
                  
                }
                
                wheelPress = true;
               
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
                {
                    std::cout << "click mouse right" << std::endl;
                }
            case SDL_KEYUP:
                if (sdlEvent.key.keysym.sym == SDLK_LALT || sdlEvent.key.keysym.sym == SDLK_RALT) {
                    std::cout << "Alt liberado" << std::endl;
                }
                break;
                
                
               
        }

       
    }

    keyboard = SDL_GetKeyboardState(NULL);
    
  


    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	std::cout<<"Quitting SDL input event subsystem";
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

float ModuleInput::GetMouseWheelMotion() const {
    return mouseWheel;
}

void ModuleInput::ResetMouse() {
    mouseWheel = 0.0f;
    wheelPress = false;
}

bool ModuleInput::HandleButtonMouse(SDL_Event sdlEvents) {
    bool right = sdlEvents.motion.state & SDL_BUTTON_RMASK;
    bool left = sdlEvents.motion.state & SDL_BUTTON_LMASK;

    if (right) {
        buttonLeft = false;
        buttonRight = right;
        return buttonRight;
    }
    else if (left) {
        buttonRight = false;
        buttonLeft = left;
        return buttonLeft;
    }
  
    return false;
}




