#pragma once

#include "Types.h"
#include "Event.h"
#include "Graphics/GraphicsContext.h"
#include <GLFW/glfw3.h>

namespace Quantum
{
	struct WindowSpecification
	{
		String Title;
		UInt32 Width, Height;
		bool VSync;
		bool Resizable;
		bool Fullscreen;
	};

	class Window
	{
	private:
		WindowSpecification m_Specification;
		GLFWwindow* m_WindowHandle;
		Scope<GraphicsContext> m_Context;

		static inline int s_WindowCount = 0;
	public:
		Window(const WindowSpecification& spec);
		~Window();

		Event<UInt32, UInt32> ResizeEvent;
		Event<> CloseEvent;
		Event<bool> FocusEvent;
		Event<bool> MinimizeEvent;
		Event<bool> MaximizeEvent;

		Event<int, int, int, int> KeyEvent;
		Event<int, int, int> MouseButtonEvent;
		Event<double, double> MouseMoveEvent;
		Event<double, double> MouseScrollEvent;

		void OnUpdate();
		void OnRender();

		WindowSpecification& GetSpecification() { return m_Specification; };
		String GetTitle() const { return m_Specification.Title; };
		Pair<UInt32, UInt32> GetSize() const { return { GetWidth(), GetHeight()}; };
		Pair<UInt32, UInt32> GetMonitorSize(GLFWmonitor* monitor = glfwGetPrimaryMonitor()) const;
		UInt32 GetWidth() const { return m_Specification.Width; };
		UInt32 GetHeight() const { return m_Specification.Height; };
		float GetAspectRatio() const;
		bool IsVSync() const { return m_Specification.VSync; };

		void SetTitle(StringView title);
		void SetSize(UInt32 width, UInt32 height);
		void SetWidth(UInt32 width);
		void SetHeight(UInt32 height);
		void SetVSync(bool enabled);
		void SetResizable(bool enabled);
		void SetFullscreen(bool enabled);
	private:
		void SetCallbacks();
	};
}
