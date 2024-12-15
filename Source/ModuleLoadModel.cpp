
#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_EXTERNAL_IMAGE 
#define TINYGLTF_IMPLEMENTATION
#include "tiny_gltf.h"
#include "ModuleLoadModel.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "SDL.h"
#include "Mesh.h"
#include "MathGeoLib.h"
#include "imgui.h"


ModuleLoadModel::ModuleLoadModel() 
{

}

ModuleLoadModel::~ModuleLoadModel() 
{

}
void ModuleLoadModel::LoadModel(const char* fileName, unsigned int program)
{
    ClearMeshes();
    tinygltf::TinyGLTF gltfContext;
    tinygltf::Model model;
    std::string error, warning;
    std::string path = fileName;
    std::ostringstream errorMsg;
    GetBasePath(path);
    bool loadOk = gltfContext.LoadASCIIFromFile(&model, &error, &warning, fileName);
    if (!loadOk) {
        errorMsg << "Error loading %s: %s\n" << fileName << error.c_str();
        App->GetLogger()->Log(LOGERROR, errorMsg.str());
        
    }
    else {
        LoadMaterials(model);
        for (int i = 0; i < model.nodes.size(); ++i) {
            float4x4 parentTransform = float4x4::identity;
            ProcessNode(model, i, program, parentTransform);
        }
    }
    
    
}

	


void ModuleLoadModel::LoadMaterials(const tinygltf::Model &srcModel)
{
    textures.clear();
   
    for (const auto& srcMaterial : srcModel.materials)
    {
        unsigned int textureId = 0;
        std::ostringstream textPath;
        std::ostringstream baseChain;
        if (srcMaterial.pbrMetallicRoughness.baseColorTexture.index >= 0)
        {
            const tinygltf::Texture& texture = srcModel.textures[srcMaterial.pbrMetallicRoughness.baseColorTexture.index];
            const tinygltf::Image& image = srcModel.images[texture.source];
            size_t lastSeparator = basePath.rfind('\\');
            if (lastSeparator != std::string::npos) {
                std::string tempPath;
                tempPath = basePath.substr(0, lastSeparator);  
                baseChain << "Directory: " << basePath;
                App->GetLogger()->Log(LOGMessage, baseChain.str());
                textureId = (App->GetTxt()->Load(basePath+ '\\' + image.uri));
                textPath << "Texture is: " << basePath + '\\'+ image.uri << std::endl;
                App->GetLogger()->Log(LOGMessage, textPath.str());
            }
            else 
            {
                textureId = (App->GetTxt()->Load(basePath + '/' + image.uri));
                textPath << "Texture is: " << basePath + '/' + image.uri << std::endl;
                App->GetLogger()->Log(LOGMessage, textPath.str());
            }
            
        }
        textures.push_back(textureId);
    }
}

update_status ModuleLoadModel::Update()
{
    
    
        return UPDATE_CONTINUE;
    

}

bool ModuleLoadModel::CleanUp()
{
    ClearMeshes();
    return true;
}

void ModuleLoadModel::ClearMeshes()
{
    if (meshes.size() > 0) 
    {
        for (Mesh* mesh : meshes) {
            mesh->CleanUp();
            delete mesh;
        }
        meshes.clear();
    }
    
}

void ModuleLoadModel::GetBasePath( std::string& fileName)
{
    std::ostringstream sucess;
    
    size_t lastSeparator = fileName.rfind('/');  

    if (lastSeparator != std::string::npos) {
        basePath = fileName.substr(0, lastSeparator);  
        sucess << "Directory: " << basePath;
        App->GetLogger()->Log(LOGMessage, sucess.str());
    }
    else {
        sucess << "No directory separator found!";
        App->GetLogger()->Log(LOGERROR, sucess.str());
    }

   lastSeparator = fileName.rfind('\\');

   if (lastSeparator != std::string::npos) {
       basePath = fileName.substr(0, lastSeparator);  
       sucess << "Directory: " << basePath;
       App->GetLogger()->Log(LOGMessage, sucess.str());
   }
   else {
       sucess << "No directory separator found!";
       App->GetLogger()->Log(LOGERROR, sucess.str());
   }
}


void ModuleLoadModel::ProcessNode(const tinygltf::Model& model, int nodeIndex, unsigned int program, float4x4 parentTransform)
{
    const tinygltf::Node& node = model.nodes[nodeIndex];
    if (node.name != "RootNode" || node.name.empty())
    {
        float4x4 localTransform = float4x4::identity;

        if (!node.matrix.empty()) {
            float scaleX = node.matrix[0];
            float scaleY = node.matrix[5];
            float scaleZ = node.matrix[10];

            if (fabs(scaleX) < 1e-6f) scaleX = 1.0f;
            if (fabs(scaleY) < 1e-6f) scaleY = 1.0f;
            if (fabs(scaleZ) < 1e-6f) scaleZ = 1.0f;
           
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
        globalTransform = parentTransform *localTransform;
       
        bool isDuckModel = false;
        if (node.mesh >= 0) {
            const tinygltf::Mesh& mesh = model.meshes[node.mesh];
            if (mesh.name == "LOD3spShape") { 
                isDuckModel = true;
            }
        }

      
        if (isDuckModel) {
            float scaleFactor = 0.01f; 
            globalTransform = globalTransform * float4x4::Scale(scaleFactor, scaleFactor, scaleFactor);
        }

        




        if (node.mesh >= 0)
        {
            const tinygltf::Mesh& mesh = model.meshes[node.mesh];
            for (const auto& primitive : mesh.primitives) {
                Mesh* meshInstance = new Mesh;
                meshInstance->Load(model, mesh);
                meshInstance->LoadEBO(model, mesh);
                meshInstance->CreateVAO();

                meshes.push_back(meshInstance);

            }
        }


    }


    for (int childIndex : node.children) {
        ProcessNode(model, childIndex, program, parentTransform);
    }
}

float4x4 ModuleLoadModel::GetNewModelMatrix()
{
    return globalTransform;
}

void ModuleLoadModel::RenderUI()
{
   

    if (ImGui::CollapsingHeader("Model Info"))
    {
        if (ImGui::BeginTabBar("Model "))
        {
            
            if (ImGui::BeginTabItem("Model Display"))
            {
                ImGui::Text("Model Information:");
                ImGui::Text("Total Materials: %lu", textures.size());
                ImGui::Text("Model Path: %s", basePath.c_str());
                ImGui::Text("Number of Meshes: %lu", meshes.size());

                ImGui::EndTabItem();
            }



            ImGui::EndTabBar();
        }
    }
}

float3 ModuleLoadModel::GetModelTranslation()
{
    return globalTransform.TranslatePart();
}







