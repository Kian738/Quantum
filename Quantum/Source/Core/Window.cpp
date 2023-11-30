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
		LOG(Info, LogWindow, "Creating window {} ({}x{})...", spec.Title, spec.Width, spec.Height)

		if (s_WindowCount == 0)
		{
			LOG_CHECK(glfwInit(), Error, LogWindow, "Could not initialize GLFW!");
			LOG(Info, LogWindow, "Initialized GLFW version {}.{}.{}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, spec.Resizable);
		m_WindowHandle = glfwCreateWindow(
			spec.Width,
			spec.Height,
			spec.Title.c_str(),
			spec.Fullscreen ? glfwGetPrimaryMonitor() : nullptr,
			nullptr
		); // TODO: Add suppport for decorated windows
		s_WindowCount++;

		LOG_CHECK(m_WindowHandle, Error, LogWindow, "Could not create GLFW window!");

		m_Context = CreateScope<GraphicsContext>(m_WindowHandle);
		m_Context->Initialize();

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

		glfwSetWindowCloseCallback(m_WindowHandle, [](GLFWwindow* windowHandle)
			{
			auto& window = *reinterpret_cast<Window*>(glfwGetWindowUserPointer(windowHandle));
			window.CloseEvent();
		});
	}

	Window::~Window()
	{
		LOG(Info, LogWindow, "Destroying window {}...", m_Specification.Title);

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
