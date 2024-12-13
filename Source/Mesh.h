
#ifndef MESH_H
#define MESH_H
#include "MathGeoLib.h"
#include <vector>
#include <glew.h>
#include <windows.h>
#include "MathGeoLib.h"
namespace tinygltf {
	class Model; class Mesh; class Primitive; class Node;
 }
class Mesh
{
public:
	Mesh();
	~Mesh();
	void Load(const tinygltf::Model& model, const tinygltf::Mesh& mesh);
	void LoadEBO(const tinygltf::Model& model, const tinygltf::Mesh& mesh);
	void Render(unsigned int program, const std::vector<unsigned>& textures);
	void CreateVAO();
	void CleanUp();


	unsigned int VAO;
	unsigned int VBO;
	unsigned int TexVBO;
	unsigned int EBO;
	unsigned int vertexCount;
	unsigned int indCount;
	unsigned int materialIndex =0;
};

#endif // MESH_H