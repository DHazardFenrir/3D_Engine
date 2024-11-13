#include "ModuleProgram.h"
#include "Globals.h"
#include "Application.h"



ModuleProgram::ModuleProgram() {
  
}
ModuleProgram::~ModuleProgram() {
	
}

bool ModuleProgram::Init() {
	return true;
}

unsigned ModuleProgram::CreateProgram(unsigned vtx_shader, unsigned frg_shader) 
{
    unsigned program_id = glCreateProgram();
    glAttachShader(program_id, vtx_shader);
    glAttachShader(program_id, frg_shader);
    glLinkProgram(program_id);
    int res;
    glGetProgramiv(program_id, GL_LINK_STATUS, &res);
    if (res == GL_FALSE)
    {
        int len = 0;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &len);
        if (len > 0)
        {
            int written = 0;
            char* info = (char*)malloc(len);
            glGetProgramInfoLog(program_id, len, &written, info);
            ENGINELOG("Program Log Info: %s", info);
            free(info);
        }
        glDeleteProgram(program_id);
       
    }
    glDeleteShader(vtx_shader);
    glDeleteShader(frg_shader);
    return program_id;
}

unsigned ModuleProgram::CompileShader(unsigned type, const char* source) 
{
    unsigned shader_id = glCreateShader(type);
    glShaderSource(shader_id, 1, &source, 0);
    glCompileShader(shader_id);
    int res = GL_FALSE;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &res);
    if (res == GL_FALSE)
    {
        int len = 0;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len);
        if (len > 0)
        {
            int written = 0;
            char* info = (char*)malloc(len);
            glGetShaderInfoLog(shader_id, len, &written, info);
            ENGINELOG("Log Info: %s", info);
            free(info);
        }
    }
    return shader_id;
}

char* ModuleProgram::LoadShaderSource(const char* shader_file_name) 
{
    char* data = nullptr;
    FILE* file = nullptr;

    // Usar fopen_s para abrir el archivo
    if (fopen_s(&file, shader_file_name, "rb") == 0)
    {
        fseek(file, 0, SEEK_END);
        int size = ftell(file);
        data = (char*)malloc(size + 1);
        fseek(file, 0, SEEK_SET);
        fread(data, 1, size, file);
        data[size] = 0; // Null-terminate
        fclose(file);
    }
    else
    {
        ENGINELOG("Failed to open shader file: %s", shader_file_name); //failed log
    }
    return data;
}