#pragma once

#include "Buffers/FrameBuffer.h"
#include "Buffers/VertexArray.h"
#include "Camera/Camera.h"
#include "Core/Types.h"
#include "Resources/Mesh.h"
#include "Resources/Model.h"
#include "Shader/ShaderLibrary.h"

namespace Quantum
{
	class Renderer
	{
	private:
		static inline Ref<ShaderLibrary> s_ShaderLibrary; // TODO: Move to AssetManager
		static inline Ref<FrameBuffer> s_FrameBuffer;
	public:
		static void Initialize();
		static void Shutdown();

		static void Reset();
		static void BeginScene(const Camera& camera);
		static void EndScene();

		// TODO: Remove this and use designated draw functions and IDrawable interface
		static void Submit(const Mesh& mesh, const Matrix4& transform = Matrix4(1.0f));
		static void Submit(const Model& model, const Matrix4& transform = Matrix4(1.0f));
		
		static Ref<FrameBuffer> GetFrameBuffer() { return s_FrameBuffer; };
		static Ref<ShaderLibrary> GetShaderLibrary() { return s_ShaderLibrary; };
	private:
		static void DrawVertexArray(const Ref<VertexArray>& vertexArray);

		static void OnResize(int width, int height);
	};
}
