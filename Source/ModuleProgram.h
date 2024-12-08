#pragma once
#include "Module.h"
#include "Globals.h"
#include "glew.h"
class ModuleProgram : public Module
{
public:
	ModuleProgram();
	~ModuleProgram();
	unsigned CreateProgram(unsigned vtx_shader, unsigned frg_shader);
	unsigned CompileShader(unsigned type, const char* source);
	char* LoadShaderSource(const char* shader_file_name);
	
	bool Init();


};

