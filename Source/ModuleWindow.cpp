#include "Globals.h"
#include <iostream>
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleEditorCamera.h"

ModuleWindow::ModuleWindow()
{
}

// Destructor
ModuleWindow::~ModuleWindow()
{
	
}

// Called before render is available
bool ModuleWindow::Init()
{
	std::cout<<"Init SDL window & surface";
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout<<"SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError();
		ret = false;
	}
	else
	{
		//Create window
		SDL_DisplayMode displayMode;
		if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0)
		{
			std::cout << "Could not get display mode! SDL_Error: %s\n", SDL_GetError();
			ret = false;
		}
		Uint32 flags = SDL_WINDOW_SHOWN |  SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

		int width = displayMode.w;
		int height = displayMode.h;
		if(FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | flags);

		if(window == NULL)
		{
			std::cout<<"Window could not be created! SDL_Error: %s\n", SDL_GetError();
			ret = false;
		}
		else
		{
			//Get window surface
			
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	std::cout<<"Destroying SDL window and quitting all SDL systems";

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	
	SDL_Quit();
	return true;
}

void ModuleWindow::SetFullScreen(bool fullscreen)
{
	if (fullscreen) {
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP); 
	}
	else {
		SDL_SetWindowFullscreen(window, 0); 
	}
}



