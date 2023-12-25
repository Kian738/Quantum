#include "RenderCommand.h"

#include <glad/gl.h>

namespace Quantum
{
	void RenderCommand::Initialize()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_MULTISAMPLE);

		glEnable(GL_FRAMEBUFFER_SRGB);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	}

	void RenderCommand::SetClearColor(const Vector4& color)
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
