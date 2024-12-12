
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
			                //texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
			 
			 
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
		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// texture coord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		return vao;
	}

	unsigned CreateEBO() {
		
		unsigned int indices[] = {  // note that we start from 0!
		  0, 3, 1, // Primer triángulo (CCW)
			1, 3, 2  // Segundo triángulo (CCW)
		};
		unsigned ebo;
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		return ebo;
	}
	void DestroyVBO(unsigned vbo);
	void DestroyVAO(unsigned vao);
	void DestroyEBO(unsigned ebo);
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

