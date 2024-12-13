#pragma once
#include "Module.h"
#include "Mesh.h"
#include <vector>
#include <iostream>


class ModuleLoadModel: public Module
{
public:
	ModuleLoadModel();
	~ModuleLoadModel();
	void LoadModel( const char* fileName, unsigned int program);
	void LoadMaterials(const tinygltf::Model &srcModel);
	update_status Update();
	bool CleanUp();
	void ClearMeshes();
	void GetBasePath(std::string& fileName);
	void ProcessNode(const tinygltf::Model& model, int nodeIndex, unsigned int program, float4x4 parentTransform);
	float4x4 GetNewModelMatrix();
	std::vector<unsigned> textures;
	std::vector<Mesh*> meshes;
	std::string basePath;
	float4x4 globalTransform;
	
};

