#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Quantum
{
	class GraphicsContext
	{
	private:
		GLFWwindow* m_WindowHandle;
	public:
		GraphicsContext(GLFWwindow* windowHandle);

		void Initialize();
		void SwapBuffers();
	};
}
