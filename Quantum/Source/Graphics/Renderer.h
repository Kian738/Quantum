#pragma once

#include "Core/Types.h"
#include "VertexArray.h"

namespace Quantum
{
	struct RendererData
	{
		Ref<VertexArray> QuadVertexArray;
	};

	struct SceneData
	{
		Matrix4D ViewProjectionMatrix;
	};

	class Renderer
	{
	private:
		static inline SceneData* s_SceneData;
		static inline RendererData* s_Data;
	public:
		static void Initialize();
		static void Shutdown();

		static void BeginScene();
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray);
	private:
		static void DrawVertexArray(const Ref<VertexArray>& vertexArray);
	};
}
