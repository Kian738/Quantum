#include "RenderCommand.h"

#include <glad/gl.h>

namespace Quantum
{
	void RenderCommand::Initialize()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
	}

	void RenderCommand::SetClearColor(const Vector4D& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void RenderCommand::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderCommand::Draw(UInt32 count)
	{
		glDrawArrays(GL_TRIANGLES, 0, count);
	}

	void RenderCommand::DrawIndexed(UInt32 count)
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void RenderCommand::SetViewport(UInt32 x, UInt32 y, UInt32 width, UInt32 height)
	{
		glViewport(x, y, width, height);
	}
}
