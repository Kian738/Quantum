#include "RenderCommand.h"

#include "Core/Core.h"
#include <glad/gl.h>

namespace Quantum
{
	static void OpenGLDebugMessageCallback(GLenum, GLenum, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void*)
	{
		auto logMessage = std::format("OpenGL Debug Message ({}): {}", id, message);
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			LOG(Error, LogGraphics, logMessage);
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			LOG(Warning, LogGraphics, logMessage);
			break;
		case GL_DEBUG_SEVERITY_LOW:
			LOG(Info, LogGraphics, logMessage);
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			LOG(Debug, LogGraphics, logMessage);
			break;
		default:
			LOG(Info, LogGraphics, logMessage);
			break;
		}
	}

	void RenderCommand::Initialize()
	{
		glDebugMessageCallback(OpenGLDebugMessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_MULTISAMPLE); // TODO: Also add support for SMAA in addition to MSAA

		glEnable(GL_FRAMEBUFFER_SRGB);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	}

	void RenderCommand::SetClearColor(const Vector4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void RenderCommand::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderCommand::Draw(UInt32 count)
	{
		glDrawArrays(GL_TRIANGLES, 0, count);
	}

	void RenderCommand::DrawIndexed(UInt32 count)
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void RenderCommand::SetViewport(UInt32 x, UInt32 y, UInt32 width, UInt32 height)
	{
		glViewport(x, y, width, height);
	}
}
