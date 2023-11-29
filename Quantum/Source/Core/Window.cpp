#include "Window.h"

DEFINE_LOG_CATEGORY_STATIC(Window);

namespace Quantum
{
	static void GLFWErrorCallback(int error, const char* description)
	{
		LOG(Error, LogWindow, "GLFW Error ({}): {}", error, description);
	}

	Window::Window(const WindowSpecification& spec)
		: m_Specification(spec)
	{
		if (s_WindowCount == 0)
		{
			LOG_CHECK(glfwInit(), Error, LogWindow, "Could not initialize GLFW!");
			LOG(Info, LogWindow, "Initialized GLFW version {}.{}.{}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		m_WindowHandle = glfwCreateWindow(spec.Width, spec.Height, spec.Title.c_str(), nullptr, nullptr);
		s_WindowCount++;

		LOG_CHECK(m_WindowHandle, Error, LogWindow, "Could not create GLFW window!");

		glfwMakeContextCurrent(m_WindowHandle); // TODO: Move this to the renderer
		glfwSetWindowUserPointer(m_WindowHandle, &m_Specification);

		glfwSwapInterval(spec.VSync ? 1 : 0);

		glfwSetWindowSizeCallback(m_WindowHandle, [](GLFWwindow* window, int width, int height)
		{
			auto& spec = *reinterpret_cast<WindowSpecification*>(glfwGetWindowUserPointer(window));
			spec.Width = width;
			spec.Height = height;
		});
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_WindowHandle);
		s_WindowCount--;

		if (s_WindowCount == 0)
			glfwTerminate();
	}

	void Window::Tick()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_WindowHandle);
	}

	void Window::SetTitle(StringView title)
	{

	}

	void Window::SetSize(UInt32 width, UInt32 height)
	{
	}

	void Window::SetWidth(UInt32 width)
	{
		SetSize(width, GetHeight());
	}

	void Window::SetHeight(UInt32 height)
	{
		SetSize(GetWidth(), height);
	}

	void Window::SetVSync(bool enabled)
	{
	}
}
