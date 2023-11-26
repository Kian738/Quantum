#pragma once

#include "Core/Core.h"

namespace Quantum
{
	struct WindowSpecification
	{
		String Title;
		UInt32 Width, Height;
		bool VSync;

		WindowSpecification(StringView title = "Quantum Engine", UInt32 width = 1280, UInt32 height = 720, bool vSync = false)
			: Title(title)
			, Width(width)
			, Height(height)
			, VSync(vSync)
		{
		}
	};

	class Window
	{
	private:
		WindowSpecification m_Specification;
	public:
		Window(const WindowSpecification& spec);
		~Window();

		void OnUpdate();

		String GetTitle() const { return m_Specification.Title; };
		UInt32 GetWidth() const { return m_Specification.Width; };
		UInt32 GetHeight() const { return m_Specification.Height; };
		bool IsVSync() const { return m_Specification.VSync; };

		void SetTitle(StringView title);
		void SetWidth(UInt32 width);
		void SetHeight(UInt32 height);
		void SetVSync(bool enabled);
	};
}
