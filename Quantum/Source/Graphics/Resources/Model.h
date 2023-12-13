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
		void ProcessNode(aiNode* node, const aiScene* scene, const Matrix4D& parentTransform = Matrix4D(1.0f));
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, const Matrix4D& transform);
		Ref<Material> LoadMaterial(aiMaterial* aiMaterial);

		static Matrix4D GetMatrixFromAssimp(const aiMatrix4x4& matrix);
	};
}
