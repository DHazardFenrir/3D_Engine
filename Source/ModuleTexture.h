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
	void LoadDDS(const std::string& filePath, DirectX::ScratchImage& img);
	void LoadTGA(const std::string& filePath, DirectX::ScratchImage& img);
	void LoadWIC(const std::string& filePath, DirectX::ScratchImage& img);
	unsigned int ProcessTexture(const DirectX::ScratchImage& image);
	unsigned int Load(const std::string&);
	std::wstring stringToWString(const std::string& str);
	void RenderUI() override;
	unsigned int GetTexture();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

private:
	DirectX::ScratchImage image;
	const std::string filePath = "resources/Test-image-Baboon.ppm";
	unsigned int texture;
	unsigned int textureID;
	const DirectX::Image* mip;
	
};

