#pragma once

#include "Core/Types.h"
#include "Shader/ShaderLibrary.h"
#include "VertexArray.h"

namespace Quantum
{
	struct SceneData
	{
		Matrix4D ViewProjectionMatrix;
	};

	struct RendererData
	{
		Ref<VertexArray> QuadVertexArray;
	};

	class Renderer
	{
	private:
		static inline SceneData* s_SceneData;
		static inline RendererData* s_Data;
		static inline Ref<ShaderLibrary> s_ShaderLibrary;
	public:
		static void Initialize();
		static void Shutdown();

		static void BeginScene(const Camera& camera);
		static void EndScene();

		// TODO: Add submit function
	private:
		static void DrawVertexArray(const Ref<VertexArray>& vertexArray);
	};
}
