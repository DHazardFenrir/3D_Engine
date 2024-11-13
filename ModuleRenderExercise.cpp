#include "Globals.h"
#include "ModuleRenderExercise.h"

#include "Application.h"
#include "ModuleOpenGL.h"
#include "ModuleProgram.h"
#include "GL/glew.h"
#include "debugdraw.h"
#include "ModuleDebugDraw.h"
#include "MathGeoLib.h"
#include "ModuleWindow.h"
#include <SDL.h>


ModuleRenderExercise::ModuleRenderExercise() {

}

ModuleRenderExercise::~ModuleRenderExercise()
{
	
}

bool ModuleRenderExercise::Init() 
{
	
  
	vbo = CreateTriangleVBO();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);  // set vbo active 
    
	 vertex_shader_source = App->GetProgram()->LoadShaderSource("default_vertex.glsl");
	 fragment_shader_source = App->GetProgram()->LoadShaderSource("default_fragment.glsl");
	
	 if (vertex_shader_source == nullptr || fragment_shader_source == nullptr) {
		 ENGINELOG("Error loading shader source.");
		 ENGINELOG("Attempting to load shader: %s", vertex_shader);
		 ENGINELOG("Attempting to load shader: %s", fragment_shader);
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
		 ENGINELOG("Failed to locate uniforms in Init");
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
        Frustum frustum;
        float aspectRatio = App->GetOpenGL()->GetAspectRatio();
        frustum.type = FrustumType::PerspectiveFrustum;
        frustum.pos = float3::zero;
        frustum.front = -float3::unitZ;
        frustum.up = float3::unitY;
        frustum.nearPlaneDistance = 0.1f;
        frustum.farPlaneDistance = 100.0f;
        frustum.verticalFov = math::pi / 4.0f;
        frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov * 0.5f) * frustum.AspectRatio());

        // Configuration of model matrix
        float4x4 model = float4x4::FromTRS(
            float3(0.0f, 0.0f, 5.0f),    // Moving the triangle behind on z.
            float4x4::identity,            // No rotation
            float3(1.0f, 1.0f, 1.0f)      // Normal scale
        );

        // Configuration of camera
        float3 cameraPos = float3(0.0f, 1.0f, 3.0f);  // Moving the camera position, 1 unit up and 3 on z
        float3 target = float3(5.0f, 0.0f, -5.0f);    // Position of triangle. 
        float3 up = float3::unitY;

        // View and Projection Matrix
        float4x4 view = float4x4::LookAt(cameraPos, target, float3::unitY, frustum.up);
        float4x4 projection = frustum.ProjectionMatrix();

        // Transpose all matrix
        float4x4 modelGL = model.Transposed();
        float4x4 viewGL = view.Transposed();
        float4x4 projectionGL = projection.Transposed();

        // Configure of viewport
        int width, height;
        
        SDL_GetWindowSize(App->GetWindow()->GetSDLWindow(), &width, &height);
       

        // Render axis and grid
        dd::axisTriad(float4x4::identity, 0.1f, 1.0f);
        dd::xzSquareGrid(-10, 10, 0.0f, 1.0f, dd::colors::Gray);
        App->GetDebugDraw()->Draw(view, projection, width, height);

        // Render triangle
        glUseProgram(program);
        
      

        // Sending uniform matrix to shaders. 
        glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &modelGL[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &viewGL[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, &projectionGL[0][0]);

        // Draw Triangle
        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

       

        // Check for errors 
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            ENGINELOG("OpenGL Error: %d", error);
        }
}

void ModuleRenderExercise::RenderTriangle() 
{
   
}

void ModuleRenderExercise::DestroyVBO(unsigned vbo) 
{
	glDeleteBuffers(1, &vbo);
}