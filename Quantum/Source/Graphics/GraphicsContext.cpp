#include "GraphicsContext.h"
#include "Core/Core.h"

namespace Quantum
{
	namespace Utils
	{
		static const char* GetString(GLenum name)
		{
			auto string = reinterpret_cast<const char*>(glGetString(name));
			return string ? string : "";
		}
	}

	GraphicsContext::GraphicsContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
	}

	void GraphicsContext::Initialize()
	{
		LOG(Info, LogGraphics, "Initializing Graphics Context...");

		glfwMakeContextCurrent(m_WindowHandle);
		LOG_CHECK(gladLoaderLoadGL(), Error, LogGraphics, "Failed to initialize GLAD!");

		// Print some info about the graphics card
		LOG(Info, LogGraphics, "OpenGL Info:");
		LOG(Info, LogGraphics, "  Vendor: {}", Utils::GetString(GL_VENDOR));
		LOG(Info, LogGraphics, "  Renderer: {}", Utils::GetString(GL_RENDERER));
		LOG(Info, LogGraphics, "  Version: {}", Utils::GetString(GL_VERSION));
	}

	void GraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
