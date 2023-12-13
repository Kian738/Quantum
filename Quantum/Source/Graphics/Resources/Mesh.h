#pragma once

#include "Core/Types.h"
#include "Graphics/Buffers/VertexArray.h"
#include "Material.h"
#include "Vertex.h"

namespace Quantum
{
	class Mesh
	{
	private:
		List<Vertex> m_Vertices;
		List<UInt32> m_Indices;
		Ref<Material> m_Material;

		Ref<VertexArray> m_VertexArray;
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;

		Matrix4D m_Transform;
	public:
		Mesh(const List<Vertex>& vertices, const List<UInt32>& indices, const Ref<Material>& material = nullptr, const Matrix4D& transform = Matrix4D(1.0f));

		Ref<Material> GetMaterial() const { return m_Material; };
		Ref<VertexArray> GetVertexArray() const { return m_VertexArray; };
		const Matrix4D& GetTransform() const { return m_Transform; };
	};
}
