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
		List<Ref<Mesh>> m_Meshes;
		String m_Directory;
	public:
		Model(StringView path);

		const List<Ref<Mesh>>& GetMeshes() const { return m_Meshes; };
	private:
		void ProcessNode(aiNode* node, const aiScene* scene, const Matrix4D& parentTransform = Matrix4D(1.0f));
		Ref<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene, const Matrix4D& transform);
		Ref<Material> LoadMaterial(aiMaterial* aiMaterial);

		static Matrix4D GetMatrix4DFromAssimp(const aiMatrix4x4& matrix);
	};
}
