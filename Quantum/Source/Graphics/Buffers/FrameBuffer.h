#pragma once

#include "Core/Types.h"

namespace Quantum
{
	class FrameBuffer
	{
	private:
		UInt32 m_RendererID;
		UInt32 m_ColorAttachment;
		UInt32 m_DepthAttachment;
	public:
		FrameBuffer(UInt32 width, UInt32 height);
		~FrameBuffer();

		void Bind();
		void Unbind();

		void BindAsTexture(UInt32 slot = 0);

		void Resize(UInt32 width, UInt32 height);

		UInt32 GetRendererID() const { return m_RendererID; };
		UInt32 GetColorAttachment() const { return m_ColorAttachment; };
		UInt32 GetDepthAttachment() const { return m_DepthAttachment; };
	};
}
