#include "ModuleHardware.h"
#include "Application.h"
#include "imgui.h"

ModuleHardware::ModuleHardware() 
{

}

ModuleHardware::~ModuleHardware() 
{

}
bool ModuleHardware::Init()
{
    cpus = SDL_GetCPUCount();
    systemRam = SDL_GetSystemRAM();
    GetGPUInfo();
   
    return true;
}

update_status ModuleHardware::PreUpdate()
{
   
    return UPDATE_CONTINUE;
}

update_status ModuleHardware::Update()
{

   
       
    GetVRAM();
    
  
    return UPDATE_CONTINUE;
}

update_status ModuleHardware::PostUpdate()
{
    return UPDATE_CONTINUE;
}

void ModuleHardware::GetGPUInfo()
{
     renderer = glGetString(GL_RENDERER);
     vendor = glGetString(GL_VENDOR);
    printf("GPU: %s\n", renderer);
    printf("Marca del GPU: %s\n", vendor);

   
    
}

void ModuleHardware::GetVRAM()
{
    printf("VRAM total: %d KB\n", totalMemory);
    printf("VRAM disponible: %d KB\n", freeMemory);
    printf("VRAM utilizada: %d KB\n", totalMemory - freeMemory);
    if (glewIsExtensionSupported("GL_NVX_gpu_memory_info")) {
        glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &totalMemory);
        glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &freeMemory);

       
    }
    else if (glewIsExtensionSupported("GL_ATI_meminfo")) {

        glGetIntegerv(GL_TEXTURE_FREE_MEMORY_ATI, &texFreeMemory);
        printf("Memoria libre para texturas (AMD): %d KB\n", texFreeMemory);
    }
    else {
        printf("No se encontraron extensiones para obtener información de VRAM.\n");
    }
}

bool ModuleHardware::CleanUp()
{
    return true;
}

void ModuleHardware::RenderUI()
{
	if (ImGui::CollapsingHeader("System")) 
	{
		if (ImGui::BeginTabBar("System"))
		{
			
			if (ImGui::BeginTabItem("System Info"))
			{
				ImGui::Text("GPU: %s\n", renderer);
				ImGui::Text("GPU Brand: %s\n", vendor);
				ImGui::Text("Total VRAM: %d KB\n", totalMemory);
                ImGui::Text("Available VRAM : % d KB\n", freeMemory);
                ImGui::Text("Used VRAM: %d KB\n", totalMemory - freeMemory);
                ImGui::Text("Free memory for textures (NVIDIA): %d KB\n", texFreeMemory);
				ImGui::EndTabItem();
			}

			

			ImGui::EndTabBar(); 
		}
	}
}
