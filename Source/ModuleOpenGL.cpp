#include "Globals.h"
#include <iostream>
#include "Application.h"
#include "ModuleOpenGL.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "glew.h"

ModuleOpenGL::ModuleOpenGL() : context(nullptr)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);  // desired version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);    // we want a double buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // we want to have a depth buffer with 24 bits
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);    // we want to have a stencil buffer with 8 bits
    SDL_GL_SetSwapInterval(1);
    
}

// Destructor
ModuleOpenGL::~ModuleOpenGL()
{
}

// Called before render is available
bool ModuleOpenGL::Init()
{
	std::cout<<"Creating Renderer context";
    std::cout<<"Creating OpenGL context";

    // Create OpenGL context and assign it to the private context variable
    context = SDL_GL_CreateContext(App->GetWindow()->GetSDLWindow());
    if (context == nullptr)
    {
        std::cout<<"OpenGL context could not be created! SDL Error: %s\n", SDL_GetError();
        return false;
    }

    // Initialize GLEW
    GLenum err = glewInit();
    SDL_GL_MakeCurrent(App->GetWindow()->GetSDLWindow(), context);
    SDL_GL_SetSwapInterval(1);
    if (err != GLEW_OK)
    {
        std::cout<<"Error initializing GLEW! %s\n", glewGetErrorString(err);
        return false;
    }
    std::cout<<"Using Glew %s", glewGetString(GLEW_VERSION);

    // Log OpenGL information
    std::cout<<"Vendor: %s", glGetString(GL_VENDOR);
    std::cout<<"Renderer: %s", glGetString(GL_RENDERER);
    std::cout<<"OpenGL version supported %s", glGetString(GL_VERSION);
    std::cout<<"GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION);
   
    glEnable(GL_DEPTH_TEST);    // Enable depth test
    glEnable(GL_CULL_FACE);     // Enable cull backward faces
    glFrontFace(GL_CCW);        // Front faces will be counter clockwise

	return true;
}

update_status ModuleOpenGL::PreUpdate()
{
    int width, height;
    SDL_GetWindowSize(App->GetWindow()->GetSDLWindow(), &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleOpenGL::Update()
{

	return UPDATE_CONTINUE;
}

update_status ModuleOpenGL::PostUpdate()
{
    // Swap window buffers to display the rendered frame
    SDL_GL_SwapWindow(App->GetWindow()->GetSDLWindow());
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleOpenGL::CleanUp()
{
	std::cout<<"Destroying renderer";

	//Destroy window
    std::cout<<"Destroying OpenGL context";

    // Destroy OpenGL context if it exists
    if (context != nullptr)
    {
        SDL_GL_DeleteContext(context);
        context = nullptr;
    }

	return true;
}

void ModuleOpenGL::WindowResized(unsigned width, unsigned height)
{
    // Update viewport when window is resized
    glViewport(0, 0, width, height);
}

float ModuleOpenGL::GetAspectRatio() const
{
    int width, height;
    SDL_GetWindowSize(App->GetWindow()->GetSDLWindow(), &width, &height);
    return (float)(width) / (float)(height);
}