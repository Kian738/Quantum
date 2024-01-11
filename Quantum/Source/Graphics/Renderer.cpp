#include "Renderer.h"

#include "RenderCommand.h"

namespace Quantum
{
	// TODO: Reenable framebuffer
	void Renderer::Initialize()
	{
		LOG(Info, LogGraphics, "Initializing Renderer...");

		RenderCommand::Initialize();

		s_ShaderLibrary = CreateRef<ShaderLibrary>();
		s_ShaderLibrary->Load("Material");

		auto& window = GEngine->GetWindow();

		auto [width, height] = window.GetSize(); // TODO: Rather get viewport size than window size
		s_FrameBuffer = CreateRef<FrameBuffer>(width, height);

		window.ResizeEvent += [](int width, int height) { OnResize(width, height); };
	}

	void Renderer::Shutdown()
	{
		LOG(Info, LogGraphics, "Shutting down Renderer...");

		s_ShaderLibrary->UnloadAll();
	}

	void Renderer::Reset()
	{
		RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		RenderCommand::Clear();
	}

	void Renderer::BeginScene(const Camera& camera)
	{
		s_FrameBuffer->Bind();
		Reset();
		for (auto& [name, shader] : s_ShaderLibrary->GetAll())
		{
			shader->Bind();
			shader->SetMat4("u_ViewProjection", camera.GetViewProjection());
		}
	}

	void Renderer::EndScene()
	{
		s_FrameBuffer->Unbind();
		for (auto& [name, shader] : s_ShaderLibrary->GetAll())
			shader->Unbind();
		s_FrameBuffer->BindTexture();
	}

	void Renderer::Submit(const Mesh& mesh, const Matrix4& transform)
	{
		static auto shader = s_ShaderLibrary->Get("Material");
		mesh.GetMaterial()->Bind(shader);

		shader->SetMat4("u_Transform", transform);

		auto transformNormal = glm::transpose(glm::inverse(Matrix3(transform)));
		shader->SetMat3("u_TransformNormal", transformNormal);

		DrawVertexArray(mesh.GetVertexArray());
	}

	void Renderer::Submit(const Model& model, const Matrix4& transform)
	{
		auto& meshes = model.GetMeshes();
		for (auto& mesh : meshes)
		{
			const auto& meshTransform = mesh->GetTransform();
			auto finalTransform = transform * meshTransform;
			Submit(*mesh, finalTransform);
		}
	}

	void Renderer::DrawVertexArray(const Ref<VertexArray>& vertexArray)
	{
		vertexArray->Bind();

		if (auto indexBuffer = vertexArray->GetIndexBuffer(); indexBuffer)
			RenderCommand::DrawIndexed(indexBuffer->GetCount());
		else
			RenderCommand::Draw(vertexArray->GetVertexCount());

		vertexArray->Unbind();
	}

	void Renderer::OnResize(int width, int height)
	{
		RenderCommand::SetViewport(0, 0, width, height);

		// TODO: s_FrameBuffer->Resize(width, height); // TODO: Most probably wrong
	}
}
