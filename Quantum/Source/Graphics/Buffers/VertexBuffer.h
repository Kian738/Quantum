#pragma once

#include "Core/Types.h"
#include "Buffer.h"

namespace Quantum
{
	class VertexBuffer
	{
	private:
		UInt32 m_RendererID;
		BufferLayout m_Layout;
		UInt32 m_Size;
		UInt32 m_VertexCount;
	public:
		VertexBuffer(float* vertices, UInt32 size);
		~VertexBuffer();

		void Bind();
		void Unbind();

		const BufferLayout& GetLayout() const { return m_Layout; };
		void SetLayout(const BufferLayout& layout);

		UInt32 GetVertexCount() const { return m_VertexCount; };
	};
}
