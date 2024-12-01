#include "Globals.h"
#include <iostream>
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleOpenGL.h"
#include "SDL.h"

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
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                return UPDATE_STOP;
            case SDL_WINDOWEVENT:
                if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    App->GetOpenGL()->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
                break;
            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_LALT || sdlEvent.key.keysym.sym == SDLK_RALT) {
                    std::cout << "Alt presionado" << std::endl;
                }
                
                break;
            case SDL_MOUSEMOTION:
                if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                    // Solo rotar si el botón izquierdo está presionado
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
                std::cout << "Mouse Wheeling" << std::endl;
                std::cout << mouseWheel << std::endl;
                break;

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


