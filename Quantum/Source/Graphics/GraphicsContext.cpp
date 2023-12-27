#include "GraphicsContext.h"

#include "Core/Core.h"

namespace Quantum
{
	namespace Utils
	{
		static const char* GetGLString(GLenum name)
		{
			return reinterpret_cast<const char*>(glGetString(name));
		}
	}

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

	GraphicsContext::GraphicsContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		LOG_CHECK(m_WindowHandle, Fatal, LogGraphics, "Window handle is null!");
	}

	void GraphicsContext::Initialize()
	{
		LOG(Info, LogGraphics, "Initializing Graphics Context...");

		glfwMakeContextCurrent(m_WindowHandle);
		LOG_CHECK(gladLoaderLoadGL(), Fatal, LogGraphics, "Failed to initialize GLAD!");

		LOG(Info, LogGraphics, "OpenGL Info:");
		LOG(Info, LogGraphics, "  Vendor: {}", Utils::GetGLString(GL_VENDOR));
		LOG(Info, LogGraphics, "  Renderer: {}", Utils::GetGLString(GL_RENDERER));
		LOG(Info, LogGraphics, "  Version: {}", Utils::GetGLString(GL_VERSION));

		glDebugMessageCallback(OpenGLDebugMessageCallback, nullptr);
	}

	void GraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
