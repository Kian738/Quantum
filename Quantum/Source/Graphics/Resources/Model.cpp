#include "Model.h"

#include "Core/Core.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

DEFINE_LOG_CATEGORY_STATIC(ModelLoader);

namespace Quantum
{
	Model::Model(StringView path)
	{
		LOG(Debug, LogModelLoader, "Loading model: {}", path);

		auto fullPath = FileSystemUtils::CombinePath(Project::GetActive()->GetAssetsDir(), path);
		m_Directory = FileSystemUtils::GetParentDir(fullPath);

		Assimp::Importer importer;

		auto scene = importer.ReadFile(fullPath, aiProcess_Triangulate | aiProcess_FlipUVs);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			LOG(Error, LogModelLoader, "Failed to load model: {}", importer.GetErrorString());
			return;
		}

		ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene, const Matrix4& parentTransform)
	{
		auto transform = parentTransform * GetMatrix4DFromAssimp(node->mTransformation);

		auto meshCount = node->mNumMeshes;
		m_Meshes.reserve(meshCount);
		for (auto i = 0u; i < meshCount; i++)
		{
			auto mesh = scene->mMeshes[node->mMeshes[i]];
			m_Meshes.emplace_back(ProcessMesh(mesh, scene, transform));
		}

		for (auto i = 0u; i < node->mNumChildren; i++)
			ProcessNode(node->mChildren[i], scene);
	}

	Ref<Mesh> Model::ProcessMesh(aiMesh* mesh, const aiScene* scene, const Matrix4& transform)
	{
		List<Vertex> vertices;
		List<UInt32> indices;
		Ref<Material> material;

		for (auto i = 0ull; i < mesh->mNumVertices; i++)
		{
			Vertex vertex{};

			auto aiVertex = mesh->mVertices[i];
			vertex.Position = { aiVertex.x, aiVertex.y, aiVertex.z };

			if (mesh->HasNormals())
			{
				auto aiNormal = mesh->mNormals[i];
				vertex.Normal = { aiNormal.x, aiNormal.y, aiNormal.z };
			}

			if (mesh->HasTextureCoords(0))
			{
				auto aiTexCoord = mesh->mTextureCoords[0][i];
				vertex.TexCoord = { aiTexCoord.x, aiTexCoord.y };
			}

			vertices.emplace_back(vertex);
		}

		for (auto i = 0ull; i < mesh->mNumFaces; i++)
		{
			auto& aiFace = mesh->mFaces[i];
			for (auto j = 0u; j < aiFace.mNumIndices; j++)
				indices.emplace_back(aiFace.mIndices[j]);
		}

		if (auto materialIdx = mesh->mMaterialIndex; materialIdx >= 0)
		{
			auto aiMaterial = scene->mMaterials[materialIdx];
			material = LoadMaterial(aiMaterial);
		}

		return CreateRef<Mesh>(vertices, indices, material, transform);
	}

	Ref<Material> Model::LoadMaterial(aiMaterial* aiMaterial)
	{
		auto material = CreateRef<Material>();

		if (aiColor3D aiColor; aiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, aiColor) == AI_SUCCESS)
			material->SetDiffuseMap(Texture::FromColor({ aiColor.r, aiColor.g, aiColor.b }));

		float shininess;
		aiMaterial->Get(AI_MATKEY_SHININESS, shininess);
		material->SetShininess(COALESCE(shininess, 32.0f));
		
		constexpr auto textureTypeCount = 4u;
		Array<TextureType, textureTypeCount> textureTypes = { TextureType::Diffuse, TextureType::Specular, TextureType::Normal, TextureType::Emissive };
		Array<aiTextureType, textureTypeCount> aiTextureTypes = { aiTextureType_DIFFUSE, aiTextureType_SPECULAR, aiTextureType_NORMALS, aiTextureType_EMISSIVE };
		for (auto i = 0u; i < textureTypeCount; i++)
		{
			auto type = textureTypes[i];
			auto aiType = aiTextureTypes[i];
			for (auto j = 0u; j < aiMaterial->GetTextureCount(aiType); j++)
			{
				aiString localPath;
				aiMaterial->GetTexture(aiType, j, &localPath);

				auto path = FileSystemUtils::CombinePath(m_Directory, localPath.C_Str());
				auto texture = AssetManager::LoadTexture(path);
				material->SetTexture(type, texture);
			}
		}

		return material;
	}

	Matrix4 Model::GetMatrix4DFromAssimp(const aiMatrix4x4& matrix)
	{
		Matrix4 result{};
		result[0][0] = matrix.a1; result[0][1] = matrix.b1; result[0][2] = matrix.c1; result[0][3] = matrix.d1;
		result[1][0] = matrix.a2; result[1][1] = matrix.b2; result[1][2] = matrix.c2; result[1][3] = matrix.d2;
		result[2][0] = matrix.a3; result[2][1] = matrix.b3; result[2][2] = matrix.c3; result[2][3] = matrix.d3;
		result[3][0] = matrix.a4; result[3][1] = matrix.b4; result[3][2] = matrix.c4; result[3][3] = matrix.d4;
		return result;
	}
}
