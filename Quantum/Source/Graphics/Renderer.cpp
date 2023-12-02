#include "Renderer.h"

#include "RenderCommand.h"

namespace Quantum
{
	void Renderer::Initialize()
	{
		RenderCommand::Initialize();

		s_SceneData = new SceneData;

		// TODO: Remove from here
		s_Data = new RendererData;
		s_Data->QuadVertexArray = CreateRef<VertexArray>();

		float squareVertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		auto squareVertexBuffer = CreateRef<VertexBuffer>(squareVertices, sizeof(squareVertices));
		squareVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		});
		s_Data->QuadVertexArray->AddBuffer(squareVertexBuffer);

		UInt32 squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		auto squareIndexBuffer = CreateRef<IndexBuffer>(squareIndices, sizeof(squareIndices) / sizeof(UInt32));
		s_Data->QuadVertexArray->SetIndexBuffer(squareIndexBuffer);
		// TODO: To here

		s_ShaderLibrary = CreateRef<ShaderLibrary>();
		s_ShaderLibrary->Load("Material");
	}

	void Renderer::Shutdown()
	{
		delete s_Data;
	}

	void Renderer::BeginScene(const Camera& camera)
	{
		for (auto& [name, shader] : s_ShaderLibrary->GetShaders())
		{
			shader->Bind();

			shader->SetMat4("u_ViewProjection", camera.GetViewProjection());
			shader->SetFloat3("u_CameraPosition", camera.GetPosition());
		}
	}

	void Renderer::EndScene()
	{
		// TODO: Figure out what to do here
	}

	void Renderer::DrawVertexArray(const Ref<VertexArray>& vertexArray)
	{
		vertexArray->Bind();

		if (auto indexBuffer = vertexArray->GetIndexBuffer(); indexBuffer)
			RenderCommand::DrawIndexed(indexBuffer->GetCount());
		else
			RenderCommand::Draw(vertexArray->GetVertexCount());
	}
}
