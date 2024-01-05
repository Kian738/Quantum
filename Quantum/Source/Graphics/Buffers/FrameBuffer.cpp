#include "FrameBuffer.h"

#include "Core/Core.h"
#include <glad/gl.h>

namespace Quantum
{
	FrameBuffer::FrameBuffer(UInt32 width, UInt32 height)
		: m_RendererID(0)
		, m_ColorAttachment(0)
		, m_DepthAttachment(0)
	{
		Resize(width, height);
	}

	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
	}

	void FrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	}

	void FrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::BindAsTexture(UInt32 slot)
	{
		glBindTextureUnit(slot, m_ColorAttachment);
	}

	void FrameBuffer::Resize(UInt32 width, UInt32 height)
	{
		if (width == 0 || height == 0)
			return;

		if (m_RendererID)
		{
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(1, &m_ColorAttachment);
			glDeleteTextures(1, &m_DepthAttachment);
		}

		glGenFramebuffers(1, &m_RendererID);
		Bind();

		static auto samples = GEngineConfig["Graphics"]["Rendering"]["Samples"].as<UInt32>(8);
		if (samples > 1) // TODO: Simplify this
		{
			glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &m_ColorAttachment);
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_ColorAttachment);

			glTexStorage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_SRGB8_ALPHA8, width, height, GL_FALSE);
			
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

			glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &m_DepthAttachment);
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_DepthAttachment);

			glTexStorage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_DEPTH24_STENCIL8, width, height, GL_FALSE);

			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_ColorAttachment, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, m_DepthAttachment, 0);
		}
		else
		{
			glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
			glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);

			glTexStorage2D(GL_TEXTURE_2D, 1, GL_SRGB8_ALPHA8, width, height);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);

			glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
			glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);

			glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, width, height);

			glBindTexture(GL_TEXTURE_2D, 0);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);
		}

		Unbind();
	}
}
