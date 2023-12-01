#pragma once

#include "Core/Types.h"
#include "VertexArray.h"

namespace Quantum
{
	struct RendererData
	{
		Ref<VertexArray> QuadVertexArray;
	};

	class Renderer
	{
	private:
		static inline RendererData* s_Data;
	public:
		static void Initialize();
		static void Shutdown();

	};
}
