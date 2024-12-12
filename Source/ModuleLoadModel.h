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
	void LoadModel( const char* filename, unsigned int program);
	void LoadMaterials(const tinygltf::Model &srcModel);
	update_status Update();
	void ProcessNode(const tinygltf::Model& model, int nodeIndex, unsigned int program);
	float4x4 GetNewModelMatrix();
	std::vector<unsigned> textures;
	std::vector<Mesh*> meshes;
	float4x4 globalTransform;
	
};

