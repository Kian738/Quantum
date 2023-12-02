#pragma once

#include "Core/Types.h"

namespace Quantum
{
	class RenderCommand
	{
	public:
		static void Initialize();

		static void SetClearColor(const Vector4D& color);
		static void Clear();

		static void Draw(UInt32 count);
		static void DrawIndexed(UInt32 count);

		static void SetViewport(UInt32 x, UInt32 y, UInt32 width, UInt32 height);
	};
}
