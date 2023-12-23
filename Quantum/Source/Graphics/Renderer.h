#pragma once

#include "Buffers/VertexArray.h"
#include "Camera/Camera.h"
#include "Core/Types.h"
#include "Resources/Mesh.h"
#include "Resources/Model.h"
#include "Shader/ShaderLibrary.h"

namespace Quantum
{
	struct SceneData
	{
		Matrix4 ViewProjectionMatrix;
	};

	class Renderer
	{
	private:
		static inline SceneData* s_SceneData;
		static inline Ref<ShaderLibrary> s_ShaderLibrary; // TODO: Move to AssetManager
	public:
		static void Initialize();
		static void Shutdown();

		static void Clear();
		static void BeginScene(const Camera& camera);
		static void EndScene();

		// TODO: Remove this and use designated draw functions and IDrawable interface
		static void Submit(const Mesh& mesh, const Matrix4& transform = Matrix4(1.0f));
		static void Submit(const Model& model, const Matrix4& transform = Matrix4(1.0f));

		static Ref<ShaderLibrary> GetShaderLibrary() { return s_ShaderLibrary; };
	private:
		static void OnWindowResize(UInt32 width, UInt32 height);

		static void DrawVertexArray(const Ref<VertexArray>& vertexArray);
	};
}
