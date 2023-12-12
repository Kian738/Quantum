#include "Window.h"

#include "Core.h"

DEFINE_LOG_CATEGORY_STATIC(Window);

const float c_WindowSizeRatio = 0.6667f;

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
			LOG_CHECK(glfwInit(), Fatal, LogWindow, "Failed to initialize GLFW!");
			LOG(Info, LogWindow, "Initialized GLFW version {}.{}.{}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		if (bool noSize = spec.Height == 0 || spec.Width == 0; noSize || spec.Fullscreen)
		{
			auto [width, height] = GetMonitorSize();
			if (noSize)
			{
				width *= c_WindowSizeRatio;
				height *= c_WindowSizeRatio;
			}
			m_Specification.Width = width;
			m_Specification.Height = height;
		}

		LOG(Info, LogWindow, "Creating window {} ({}x{})...", spec.Title, m_Specification.Width, m_Specification.Height);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, spec.Resizable);
		// TODO: Add suppport for decorated windows
		// TODO: Add suppport for maximized windows
		// TODO: Load size and position from config
		m_WindowHandle = glfwCreateWindow(
			m_Specification.Width,
			m_Specification.Height,
			spec.Title.c_str(),
			spec.Fullscreen ? glfwGetPrimaryMonitor() : nullptr,
			nullptr
		);
		s_WindowCount++;

		LOG_CHECK(m_WindowHandle, Error, LogWindow, "Could not create GLFW window!");

		m_Context = CreateScope<GraphicsContext>(m_WindowHandle);
		m_Context->Initialize();

		glfwSetWindowUserPointer(m_WindowHandle, this);
		SetVSync(spec.VSync);

		SetCallbacks();
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

	Pair<UInt32, UInt32> Window::GetMonitorSize(GLFWmonitor* monitor) const
	{
		auto mode = glfwGetVideoMode(monitor);
		return { mode->width, mode->height };
	}

	float Window::GetAspectRatio() const
	{
		return (float)GetWidth() / (float)GetHeight();
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

	void Window::SetResizable(bool enabled)
	{
		glfwSetWindowAttrib(m_WindowHandle, GLFW_RESIZABLE, enabled);
		m_Specification.Resizable = enabled;
	}

	void Window::SetFullscreen(bool enabled)
	{
		auto [width, height] = GetMonitorSize();
		glfwSetWindowMonitor(m_WindowHandle, enabled ? glfwGetPrimaryMonitor() : nullptr, 0, 0, width, height, GLFW_DONT_CARE);
		m_Specification.Fullscreen = enabled;
	}

	void Window::SetCallbacks()
	{
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

		glfwSetWindowFocusCallback(m_WindowHandle, [](GLFWwindow* windowHandle, int focused)
			{
				auto& window = *reinterpret_cast<Window*>(glfwGetWindowUserPointer(windowHandle));
				window.FocusEvent(focused);
			});

		glfwSetWindowIconifyCallback(m_WindowHandle, [](GLFWwindow* windowHandle, int iconified)
			{
				auto& window = *reinterpret_cast<Window*>(glfwGetWindowUserPointer(windowHandle));
				window.MinimizeEvent(iconified);
			});

		glfwSetWindowMaximizeCallback(m_WindowHandle, [](GLFWwindow* windowHandle, int maximized)
			{
				auto& window = *reinterpret_cast<Window*>(glfwGetWindowUserPointer(windowHandle));
				window.MaximizeEvent(maximized);
			});

		glfwSetKeyCallback(m_WindowHandle, [](GLFWwindow* windowHandle, int key, int scanCode, int action, int mods)
			{
				auto& window = *reinterpret_cast<Window*>(glfwGetWindowUserPointer(windowHandle));
				window.KeyEvent(key, scanCode, action, mods);
			});

		glfwSetMouseButtonCallback(m_WindowHandle, [](GLFWwindow* windowHandle, int button, int action, int mods)
			{
				auto& window = *reinterpret_cast<Window*>(glfwGetWindowUserPointer(windowHandle));
				window.MouseButtonEvent(button, action, mods);
			});

		glfwSetCursorPosCallback(m_WindowHandle, [](GLFWwindow* windowHandle, double x, double y)
			{
				auto& window = *reinterpret_cast<Window*>(glfwGetWindowUserPointer(windowHandle));
				window.MouseMoveEvent(x, y);
			});

		glfwSetScrollCallback(m_WindowHandle, [](GLFWwindow* windowHandle, double x, double y)
			{
				auto& window = *reinterpret_cast<Window*>(glfwGetWindowUserPointer(windowHandle));
				window.MouseScrollEvent(x, y);
			});
	}
}
