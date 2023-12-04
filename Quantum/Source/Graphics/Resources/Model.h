#pragma once

#include "Core/Types.h"
#include "Material.h"
#include "Mesh.h"
#include <assimp/scene.h>

namespace Quantum
{
	class Model
	{
	private:
		List<Mesh> m_Meshes;
		String m_Directory;
	public:
		Model(StringView path);

		const List<Mesh>& GetMeshes() const { return m_Meshes; };
	private:
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		Ref<Material> LoadMaterial(aiMaterial* aiMaterial);
	};
}
