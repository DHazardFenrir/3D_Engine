
#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_EXTERNAL_IMAGE 
#include "tiny_gltf.h"
#include "Mesh.h"
#include "MathGeoLib.h"
#include "SDL.h"

Mesh::Mesh() : VAO(0), VBO(0), EBO(0) {};
Mesh::~Mesh() {};

void Mesh::Load(const tinygltf::Model& model, const tinygltf::Mesh& mesh)
{
	for (const auto& primitive : mesh.primitives) 
	{
		const auto& itPos = primitive.attributes.find("POSITION");
		if (itPos != primitive.attributes.end())
		{
			const tinygltf::Accessor & posAcc = model.accessors[itPos->second];
			SDL_assert(posAcc.type == TINYGLTF_TYPE_VEC3);
			SDL_assert(posAcc.componentType == GL_FLOAT);
			const tinygltf::BufferView & posView = model.bufferViews[posAcc.bufferView];
			const tinygltf::Buffer& posBuffer = model.buffers[posView.buffer];
			const unsigned char* bufferPos = &(posBuffer.data[posAcc.byteOffset + posView.byteOffset]);
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * posAcc.count, nullptr, GL_STATIC_DRAW);
			float3* ptr = reinterpret_cast<float3*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
			for (size_t i = 0; i < posAcc.count; ++i)
			{
				ptr[i] = *reinterpret_cast<const float3*>(bufferPos);
				
				bufferPos += posView.byteStride == 0 ? sizeof(float) * 3 : posView.byteStride;

			}
			glUnmapBuffer(GL_ARRAY_BUFFER);
		}

	}

	for (const auto& primitive : mesh.primitives)
	{
		const auto& itTex = primitive.attributes.find("TEXCOORD_0");
		const tinygltf::Accessor& texAcc = model.accessors[itTex->second];
		SDL_assert(texAcc.type == TINYGLTF_TYPE_VEC2);
		SDL_assert(texAcc.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
		vertexCount = texAcc.count;
		const tinygltf::BufferView& texView = model.bufferViews[texAcc.bufferView];
		const tinygltf::Buffer& texBuffer = model.buffers[texView.buffer];
		const unsigned char* bufferTex = &(texBuffer.data[texAcc.byteOffset + texView.byteOffset]);
		glGenBuffers(1, &TexVBO);
		glBindBuffer(GL_ARRAY_BUFFER, TexVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * texAcc.count, nullptr, GL_STATIC_DRAW);

		float2* ptr = reinterpret_cast<float2*>(glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(float) * 3 * vertexCount, GL_MAP_WRITE_BIT));
		for (size_t i = 0; i < texAcc.count; ++i) {
			ptr[i] = *reinterpret_cast<const float2*>(bufferTex);
			bufferTex += texView.byteStride == 0 ? sizeof(float) * 2 : texView.byteStride;
		}
			glUnmapBuffer(GL_ARRAY_BUFFER);
		}

	}
	
	


	


void Mesh::LoadEBO(const tinygltf::Model& model, const tinygltf::Mesh& mesh)
{
	for (const auto& primitive : mesh.primitives) 
	{
		if (primitive.indices >= 0) 
		{
			const tinygltf::Accessor& indAcc = model.accessors[primitive.indices];
			const tinygltf::BufferView& indView = model.bufferViews[indAcc.bufferView];
			const unsigned char* buffer = &(model.buffers[indView.buffer].data[indAcc.byteOffset +
				indView.byteOffset]);
			glGenBuffers(1, &EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indAcc.count, nullptr, GL_STATIC_DRAW);
			unsigned int* ptr = reinterpret_cast<unsigned int*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));

			
			indCount = indAcc.count;
			if (indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_INT)
			{
				const int32_t* bufferInd = reinterpret_cast<const int32_t*>(buffer);
				for (int32_t i = 0; i < indCount; ++i) ptr[i] = bufferInd[i];
			}
			if (indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_SHORT)
			{
				const unsigned short* bufferInd = reinterpret_cast<const unsigned short*>(buffer);
				for (unsigned short i = 0; i < indCount; ++i) ptr[i] = bufferInd[i];
			}
			if (indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_BYTE)
			{
				const GLbyte* bufferInd = reinterpret_cast<const GLbyte*>(buffer);
				for (GLbyte i = 0; i < indCount; ++i) ptr[i] = bufferInd[i];
			}
			
			glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		}
	}
	
}






void Mesh::Render(unsigned int program, const std::vector<unsigned>& textures)
{
	
	glUseProgram(program);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[materialIndex]);
	glUniform1i(glGetUniformLocation(program, "diffuse"), 0);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indCount, GL_UNSIGNED_INT, nullptr);
	
	
	
}



void Mesh::CreateVAO()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	
	glBindBuffer(GL_ARRAY_BUFFER, TexVBO);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBindVertexArray(0);
}

void Mesh::CleanUp()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &TexVBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
}

