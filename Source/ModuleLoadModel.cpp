
#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_EXTERNAL_IMAGE 
#define TINYGLTF_IMPLEMENTATION
#include "tiny_gltf.h"
#include "ModuleLoadModel.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "SDL.h"
#include "MathGeoLib.h"


ModuleLoadModel::ModuleLoadModel() 
{

}

ModuleLoadModel::~ModuleLoadModel() 
{

}
void ModuleLoadModel::LoadModel(const char* fileName, unsigned int program)
{
    tinygltf::TinyGLTF gltfContext;
    tinygltf::Model model;
    std::string error, warning;

    bool loadOk = gltfContext.LoadASCIIFromFile(&model, &error, &warning, fileName);
    if (!loadOk) {
        printf("Error loading %s: %s\n", fileName, error.c_str());
    }
    else {
        LoadMaterials(model);
        for (int i = 0; i < model.nodes.size(); ++i) {
            ProcessNode(model, i, program);
        }
    }
    
    
}

	


void ModuleLoadModel::LoadMaterials(const tinygltf::Model &srcModel)
{

   
    for (const auto& srcMaterial : srcModel.materials)
    {
        unsigned int textureId = 0;
        if (srcMaterial.pbrMetallicRoughness.baseColorTexture.index >= 0)
        {
            const tinygltf::Texture& texture = srcModel.textures[srcMaterial.pbrMetallicRoughness.baseColorTexture.index];
            const tinygltf::Image& image = srcModel.images[texture.source];
            textureId = (App->GetTxt()->Load(image.uri));
        }
        textures.push_back(textureId);
    }
}

update_status ModuleLoadModel::Update()
{
    
    
        return UPDATE_CONTINUE;
    

}

void ModuleLoadModel::ProcessNode(const tinygltf::Model& model, int nodeIndex, unsigned int program)
{
    const tinygltf::Node& node = model.nodes[nodeIndex];
    if (node.name != "RootNode") 
    {
        float4x4 localTransform = float4x4::identity;

        if (!node.matrix.empty()) {
            localTransform.Set(
                node.matrix[0], node.matrix[1], node.matrix[2], node.matrix[3],
                node.matrix[4], node.matrix[5], node.matrix[6], node.matrix[7],
                node.matrix[8], node.matrix[9], node.matrix[10], node.matrix[11],
                node.matrix[12], node.matrix[13], node.matrix[14], node.matrix[15]
            );
        }
        else {

            float3 translation = float3::zero;
            if (!node.translation.empty()) {
                translation = float3(node.translation[0], node.translation[1], node.translation[2]);
            }

            Quat rotation = Quat::identity;
            if (!node.rotation.empty()) {
                rotation = Quat(node.rotation[0], node.rotation[1], node.rotation[2], node.rotation[3]);
            }

            float3 scale = float3::one;
            if (!node.scale.empty()) {
                scale = float3(node.scale[0], node.scale[1], node.scale[2]);
            }

            localTransform = float4x4::FromTRS(translation, rotation, scale);
        }
        globalTransform = localTransform;
        
        


        if (node.mesh >= 0) 
        {
            const tinygltf::Mesh& mesh = model.meshes[node.mesh];
            for (const auto& primitive : mesh.primitives) {
                Mesh* meshInstance = new Mesh;
                meshInstance->Load(model,mesh);
                meshInstance->LoadEBO(model, mesh);
                meshInstance->CreateVAO();
                
                meshes.push_back(meshInstance);
               
            }
        }


    }
    

    for (int childIndex : node.children) {
        ProcessNode(model, childIndex, program);
    }
}

float4x4 ModuleLoadModel::GetNewModelMatrix()
{
    return globalTransform;
}







