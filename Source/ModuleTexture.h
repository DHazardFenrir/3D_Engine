#pragma once
#include "DirectXTex.h"
#include "Module.h"
#include "Globals.h"
#include <string>
class ModuleTexture : public Module
{
public:
	ModuleTexture();
	~ModuleTexture();

	bool Init();
	void LoadDDS(std::wstring& filePath, DirectX::ScratchImage& img);
	void LoadTGA(std::wstring& filePath, DirectX::ScratchImage& img);
	void LoadWIC(std::wstring& filePath, DirectX::ScratchImage& img);
	unsigned int ProcessTexture(const DirectX::ScratchImage& image);
	void RenderUI() override;
	unsigned int GetTexture();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

private:
	DirectX::ScratchImage image;
	std::wstring filePath = L"resources/Test-image-Baboon.ppm";
	unsigned int texture;
	
};

