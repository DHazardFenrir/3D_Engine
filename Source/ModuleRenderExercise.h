#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib.h"
#include "Math/float3.h"
#include <cmath>
#include "glew.h"


class ModuleRenderExercise : public Module
{
public:
	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void RenderVBO(unsigned vbo, unsigned program);
	unsigned CreateTriangleVBO() 
	{
		float vtx_data[] = {
		-1.0f, -1.0f, 0.0f, // V�rtice 1
		 1.0f, -1.0f, 0.0f, // V�rtice 2
		 0.0f,  1.0f, 0.0f  // V�rtice 3
		};
		unsigned  vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);  // set vbo active 
		glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);

		return vbo;
	}
	void DestroyVBO(unsigned vbo);
	void RenderTriangle();
	float ToRadians(float degrees) {
		return degrees * (3.1416/ 180.0f);
	}

private:
	char* vertex_shader_source;
	char* fragment_shader_source;
	unsigned int vertex_shader = 0;
	unsigned int fragment_shader =0;
	unsigned int shader_program;
	unsigned  vbo;
	unsigned vao;
	Frustum frustum;
	
	
};

