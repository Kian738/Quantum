#pragma once

#include "Buffers/VertexArray.h"
#include "Core/Types.h"
#include "Shader/ShaderLibrary.h"

namespace Quantum
{
	struct SceneData
	{
		Matrix4D ViewProjectionMatrix;
	};

	class Renderer
	{
	private:
		static inline SceneData* s_SceneData;
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
