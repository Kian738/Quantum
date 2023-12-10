#include "GraphicsContext.h"

#include "Core/Core.h"

namespace Quantum
{
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
		auto version = glGetString(GL_VENDOR);
		LOG(Info, LogGraphics, "  Vendor: {}", reinterpret_cast<const char*>(version));
		LOG(Info, LogGraphics, "  Vendor: {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		/*LOG(Info, LogGraphics, "  Renderer: {}", glGetString(GL_RENDERER));
		LOG(Info, LogGraphics, "  Version: {}", glGetString(GL_VERSION));*/
	}

	void GraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
