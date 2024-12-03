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
	void RenderVBO();
	unsigned CreateTriangleVBO() 
	{
		float vtx_data[] = {
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right 0
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right 1
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left 2
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 3
		};
		unsigned  vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);  // set vbo active 
		glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);

		return vbo;
	}

	unsigned CreateVAO() {
		
		

		unsigned vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		return vao;
	}

	unsigned CreateEBO() {
		
		unsigned int indices[] = {  // note that we start from 0!
			 0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};
		unsigned ebo;
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		return ebo;
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
	unsigned ebo;
	Frustum frustum;
	
	
};

