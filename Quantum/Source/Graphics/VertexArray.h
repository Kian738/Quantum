#pragma once

#include "Core/Core.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Quantum
{
	class VertexArray
	{
	private:
		UInt32 m_RendererID;
		List<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	public:
		VertexArray();
		~VertexArray();

		void Bind();
		void Unbind();

		void AddBuffer(const Ref<VertexBuffer>& vertexBuffer);
		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer);

		UInt32 GetVertexCount() const;
		const List<Ref<VertexBuffer>>& GetBuffers() const { return m_VertexBuffers; };
		const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; };
	};
}
