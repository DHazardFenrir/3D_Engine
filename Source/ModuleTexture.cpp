#include "ModuleTexture.h"
#include "DirectXTex.h"
#include "imgui.h"
#include "glew.h"
#include <iostream>
#include <locale>
#include <codecvt>

ModuleTexture::ModuleTexture()
{

}

ModuleTexture::~ModuleTexture() {
    
        
    
}

bool ModuleTexture::Init() {
   
    
	return true;
}

update_status ModuleTexture::PreUpdate() {

	return UPDATE_CONTINUE;
}

update_status ModuleTexture::Update() {

	return UPDATE_CONTINUE;
}

update_status ModuleTexture::PostUpdate() {

	return UPDATE_CONTINUE;
}

bool ModuleTexture::CleanUp() {
    
    glDeleteTextures(1, &textureID);
    image.Release();
	return true;
}

void ModuleTexture::LoadDDS(const std::string& filePath, DirectX::ScratchImage& img)
{
    
    std::wstring wideFileName = stringToWString(filePath);
    HRESULT hr = DirectX::LoadFromDDSFile(wideFileName.c_str(), DirectX::DDS_FLAGS_NONE, nullptr, img);
    const DirectX::TexMetadata& metadata = img.GetMetadata();

    if (FAILED(hr)) 
    {
        std::cout << "Failed to load DDS file" << std::endl;
        std::cout << "Trying to load TGA" << std::endl;
        LoadTGA(filePath, img);
    }


    
}

void ModuleTexture::LoadTGA(const std::string& filePath, DirectX::ScratchImage& img)
{
    std::wstring wideFileName = stringToWString(filePath);
    std::cout << "Loading TGA..." << std::endl;
    HRESULT hr = DirectX::LoadFromTGAFile(wideFileName.c_str(), nullptr, img);
    const DirectX::TexMetadata& metadata = image.GetMetadata();

    if (FAILED(hr)) {
        std::cout << "Failed to load TGA.." << std::endl;
        std::cout << "Trying to Load WIC..." << std::endl;
        LoadWIC(filePath, img);
    }
    
}

void ModuleTexture::LoadWIC(const std::string& filePath, DirectX::ScratchImage& img)
{
        DirectX::TexMetadata tempMetaData = img.GetMetadata();
        std::wstring wideFileName = stringToWString(filePath);
        HRESULT hr = DirectX::LoadFromWICFile(wideFileName.c_str(), DirectX::WIC_FLAGS_NONE, &tempMetaData, img);

        if (FAILED(hr)) {
            std::cerr << "Error loading image with WIC" << std::endl;

        }
        else {
            std::cout << "Image loaded successfully using WIC!" << std::endl;

        }

    
}


unsigned int ModuleTexture::GetTexture() {

    return texture;
}

unsigned int ModuleTexture::ProcessTexture(const DirectX::ScratchImage& image) 
{
    const DirectX::TexMetadata& metadata = image.GetMetadata();
    GLenum internalFormat = 0;
    GLenum format = 0;
    GLenum type = 0;

    switch (metadata.format) {
    case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
    case DXGI_FORMAT_R8G8B8A8_UNORM:
        internalFormat = GL_RGBA8;
        format = GL_RGBA;
        type = GL_UNSIGNED_BYTE;
        break;

    case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
    case DXGI_FORMAT_B8G8R8A8_UNORM:
        internalFormat = GL_RGBA8;
        format = GL_BGRA;
        type = GL_UNSIGNED_BYTE;
        break;

    case DXGI_FORMAT_B5G6R5_UNORM:
        internalFormat = GL_RGB8;
        format = GL_BGR;
        type = GL_UNSIGNED_BYTE;
        break;

    default:
        std::cout << "No compatible format " << metadata.format << std::endl;
        std::cout << "Texture in hex (hex): 0x" << std::hex << metadata.format << std::dec << std::endl;
        return 0;
    }

    
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    if (metadata.mipLevels > 1) {
        std::cout << "Texture contains mipmaps" << std::endl;
        for (size_t i = 0; i < metadata.mipLevels; ++i) {
            const DirectX::Image* mip = image.GetImage(i, 0, 0);
            glTexImage2D(GL_TEXTURE_2D, i, internalFormat, mip->width, mip->height, 0, format, type, mip->pixels);
        }
    }
    else {
        const DirectX::Image* mip = image.GetImage(0, 0, 0); 
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, mip->width, mip->height, 0, format, type, mip->pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        
    }

    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (textureID == 0) {
        std::cerr << "Texture loading failed, texture ID is 0!" << std::endl;
    }
    return textureID;
}

unsigned int ModuleTexture::Load(const std::string& filePath)
{
    image.Release();
    LoadDDS(filePath, image);
    return ProcessTexture(image);
}

std::wstring ModuleTexture::stringToWString(const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
   
}

void ModuleTexture::RenderUI()
{
    if (ImGui::CollapsingHeader("Texture Info"))
    {
        if (ImGui::BeginTabBar("Texture"))
        {
            // Pesta�a "General Info"
            if (ImGui::BeginTabItem("Texture Display"))
            {
                ImGui::Text("Texture Format: %d \n", image.GetMetadata().format);
                ImGui::Text("Texture Width: %d\n", image.GetMetadata().width);
                ImGui::Text("Texture Height: %d\n", image.GetMetadata().height);
                ImGui::Text("Texture Dimension : %d\n", image.GetMetadata().dimension);
                ImGui::Text("Mip Levels: %d", image.GetMetadata().mipLevels);
                ImGui::Text("Array Size: %d", image.GetMetadata().arraySize);
                ImGui::EndTabItem();
            }



            ImGui::EndTabBar();
        }
    }
}


