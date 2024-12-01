#pragma once
#include "DirectXTex.h"
#include "Module.h"
#include "Globals.h"
class ModuleTexture : public Module
{
	ModuleTexture();
	~ModuleTexture();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

private:
	DirectX::ScratchImage image;
};
