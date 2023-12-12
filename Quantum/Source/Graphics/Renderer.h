#pragma once

#include "Buffers/VertexArray.h"
#include "Core/Types.h"
#include "Resources/Mesh.h"
#include "Resources/Model.h"
#include "Shader/ShaderLibrary.h"

namespace Quantum
{
	struct SceneData
	{
		Matrix4D ViewProjectionMatrix;
	};

	// TODO: Implement resizing
	class Renderer
	{
	private:
		static inline SceneData* s_SceneData;
		static inline Ref<ShaderLibrary> s_ShaderLibrary; // TODO: Move to AssetManager
	public:
		static void Initialize();
		static void Shutdown();

		static void OnWindowResize(UInt32 width, UInt32 height);

		static void BeginScene(const Camera& camera);
		static void EndScene();

		// TODO: Remove this and use designated draw functions and IDrawable interface
		static void Submit(const Mesh& mesh, const Matrix4D& transform = Matrix4D(1.0f));
		static void Submit(const Model& model, const Matrix4D& transform = Matrix4D(1.0f));
	private:
		static void DrawVertexArray(const Ref<VertexArray>& vertexArray);
	};
}
