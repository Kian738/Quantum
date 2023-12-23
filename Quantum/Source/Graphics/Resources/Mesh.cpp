#include "Mesh.h"

namespace Quantum
{
	Mesh::Mesh(const List<Vertex>& vertices, const List<UInt32>& indices, const Ref<Material>& material, const Matrix4& transform)
		: m_Vertices(vertices)
		, m_Indices(indices)
		, m_Material(material)
		, m_Transform(transform)
	{
		m_VertexArray = CreateRef<VertexArray>();

		m_VertexBuffer = CreateRef<VertexBuffer>(
			reinterpret_cast<float*>(m_Vertices.data()),
			m_Vertices.size() * sizeof(Vertex)
		);
		m_VertexBuffer->SetLayout(Vertex::GetLayout());
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		m_IndexBuffer = CreateRef<IndexBuffer>(
			m_Indices.data(),
			m_Indices.size()
		);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_VertexArray->Unbind();
	}
}
