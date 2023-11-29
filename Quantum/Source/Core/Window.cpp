#include "Window.h"
#include "Core.h"

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
		glfwSetWindowUserPointer(m_WindowHandle, this);

		SetVSync(spec.VSync);

		glfwSetWindowSizeCallback(m_WindowHandle, [](GLFWwindow* windowHandle, int width, int height)
		{
			auto& window = *reinterpret_cast<Window*>(glfwGetWindowUserPointer(windowHandle));

			auto& spec = window.GetSpecification();
			spec.Width = width;
			spec.Height = height;

			window.ResizeEvent(width, height);
		});
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_WindowHandle);
		s_WindowCount--;

		if (s_WindowCount == 0)
			glfwTerminate();
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
	}

	void Window::OnRender()
	{
		m_Context->SwapBuffers();
	}

	void Window::SetTitle(StringView title)
	{
		glfwSetWindowTitle(m_WindowHandle, title.data());
		m_Specification.Title = title;
	}

	void Window::SetSize(UInt32 width, UInt32 height)
	{
		glfwSetWindowSize(m_WindowHandle, width, height);
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
		glfwSwapInterval(enabled ? 1 : 0);
		m_Specification.VSync = enabled;
	}
}
