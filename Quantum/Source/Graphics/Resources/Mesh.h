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
	public:
		Mesh(const List<Vertex>& vertices, const List<UInt32>& indices, const Ref<Material>& material = nullptr);

		Ref<Material> GetMaterial() const { return m_Material; };
		Ref<VertexArray> GetVertexArray() const { return m_VertexArray; };
	};
}
