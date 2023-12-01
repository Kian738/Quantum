#pragma once

#include "Core/Types.h"

namespace Quantum
{
	class IndexBuffer
	{
	private:
		UInt32 m_RendererID, m_Count;
	public:
		IndexBuffer(UInt32* indices, UInt32 count);
		~IndexBuffer();

		void Bind();
		void Unbind();

		UInt32 GetCount() const { return m_Count; };
	};
}
