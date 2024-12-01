#include "Globals.h"
#include "ModuleRenderExercise.h"
#include <iostream>
#include "Application.h"
#include "ModuleOpenGL.h"
#include "ModuleProgram.h"
#include "ModuleEditorCamera.h"
#include "glew.h"
#include "debugdraw.h"
#include "ModuleDebugDraw.h"
#include "MathGeoLib.h"
#include "Matx4x4.h";
#include "ModuleWindow.h"
#include "Math/float3.h"
#include <SDL.h>




ModuleRenderExercise::ModuleRenderExercise() {

}

ModuleRenderExercise::~ModuleRenderExercise()
{
	
}

bool ModuleRenderExercise::Init() 
{
    
  
	vbo = CreateTriangleVBO();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
	 vertex_shader_source = App->GetProgram()->LoadShaderSource("Shaders/default_vertex.glsl");
	 fragment_shader_source = App->GetProgram()->LoadShaderSource("Shaders/default_fragment.glsl");
	
	 if (vertex_shader_source == nullptr || fragment_shader_source == nullptr) {
		 std::cout<<"Error loading shader source.";
		 std::cout<<"Attempting to load shader: %s", vertex_shader;
		 std::cout<<"Attempting to load shader: %s", fragment_shader;
		 return false;
	 }
	 vertex_shader = App->GetProgram()->CompileShader(GL_VERTEX_SHADER, vertex_shader_source);
	 fragment_shader = App->GetProgram()->CompileShader(GL_FRAGMENT_SHADER, fragment_shader_source);

	// Creates shader program
	 shader_program = App->GetProgram()->CreateProgram(vertex_shader, fragment_shader);
	 GLint modelLoc = glGetUniformLocation(shader_program, "model");
	 GLint viewLoc = glGetUniformLocation(shader_program, "view");
	 GLint projLoc = glGetUniformLocation(shader_program, "proj");

	 if (modelLoc == -1 || viewLoc == -1 || projLoc == -1) {
		 std::cout<<"Failed to locate uniforms in Init";
		 return false;
	 }
	
	return true;
}
update_status ModuleRenderExercise::PreUpdate() 
{
	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::Update() 
{
	
  
	RenderVBO(vbo, shader_program);
    
	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::PostUpdate() 
{
	return UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp() 
{
	// Freeing memory after using shader_source 
	if (vertex_shader_source) free(vertex_shader_source);
	if (fragment_shader_source) free(fragment_shader_source);
	glDeleteProgram(shader_program);
	DestroyVBO(vbo);
	return true;
}

void ModuleRenderExercise::RenderVBO(unsigned vbo, unsigned program)
{

    // Frustum Config
   
    int width, height;

    SDL_GetWindowSize(App->GetWindow()->GetSDLWindow(), &width, &height);
    float aspectRatio = App->GetOpenGL()->GetAspectRatio();
           

         //Configuration of model matrix

        float4x4 model = float4x4::FromTRS(
            float3(0.0f, 0.0f, 5.0f),    // Moving the triangle behind on x.
            float4x4::RotateZ(0),            // No rotation
            float3(1.0f, 1.0f, 1.0f)      // Normal scale
        );

       /*  View and Projection Matrix */
        float4x4 view = App->GetCamera()->GetViewMatrix();
        //float4x4 view = float4x4::LookAt(frustum.Pos(), float3(0.0, 0.0, 0.0), frustum.Front(), frustum.Up(), float3::unitY);

        float4x4 projection = App->GetCamera()->GetProjectionMatrix();

      

        // Configure of viewport
       
       

        // Render axis and grid
        dd::axisTriad(float4x4::identity, 0.1f, 1.0f);
        dd::xzSquareGrid(-10, 10, 0.0f, 1.0f, dd::colors::Gray);
        App->GetDebugDraw()->Draw(view, projection, width, height);

        // Render triangle
        glUseProgram(program);
        
      

        // Sending uniform matrix to shaders. 
        glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE , &model[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, &projection[0][0]);
      
        // Draw Triangle
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        

        // Check for errors 
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cout << "OpenGL Error:" << error << std::endl;
        }

        

}

void ModuleRenderExercise::RenderTriangle() 
{
    
}

void ModuleRenderExercise::DestroyVBO(unsigned vbo) 
{
	glDeleteBuffers(1, &vbo);
}