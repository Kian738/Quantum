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

		void OnUpdate();
		void OnRender();

		WindowSpecification& GetSpecification() { return m_Specification; };
		String GetTitle() const { return m_Specification.Title; };
		UInt32 GetWidth() const { return m_Specification.Width; };
		UInt32 GetHeight() const { return m_Specification.Height; };
		bool IsVSync() const { return m_Specification.VSync; };

		void SetTitle(StringView title);
		void SetSize(UInt32 width, UInt32 height);
		void SetWidth(UInt32 width);
		void SetHeight(UInt32 height);
		void SetVSync(bool enabled);
	};
}
