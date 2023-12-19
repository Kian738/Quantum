#include "Renderer.h"

#include "RenderCommand.h"

namespace Quantum
{
	void Renderer::Initialize()
	{
		LOG(Info, LogGraphics, "Initializing Renderer...");

		RenderCommand::Initialize();

		s_SceneData = new SceneData;

		GEngine->GetWindow().ResizeEvent += [](UInt32 width, UInt32 height) { Renderer::OnWindowResize(width, height); };

		s_ShaderLibrary = CreateRef<ShaderLibrary>();
		s_ShaderLibrary->Load("Material");
	}

	void Renderer::Shutdown()
	{
		LOG(Info, LogGraphics, "Shutting down Renderer...");

		s_ShaderLibrary->UnloadAll();

		delete s_SceneData;
		s_SceneData = nullptr;
	}

	void Renderer::Clear()
	{
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();
	}

	void Renderer::BeginScene(const Camera& camera)
	{
		for (auto& [name, shader] : s_ShaderLibrary->GetAll())
		{
			shader->Bind();

			shader->SetMat4("u_ViewProjection", camera.GetViewProjection());
			shader->SetFloat3("u_CameraPosition", camera.GetPosition());
		}
	}

	void Renderer::EndScene()
	{
		for (auto& [name, shader] : s_ShaderLibrary->GetAll())
			shader->Unbind();
	}

	void Renderer::Submit(const Ref<Mesh>& mesh, const Matrix4D& transform)
	{
		static auto shader = s_ShaderLibrary->Get("Material");
		mesh->GetMaterial()->Bind(shader);
		shader->SetMat4("u_Transform", transform);
		auto transformNormal = glm::transpose(glm::inverse(Matrix3D(transform)));
		shader->SetMat3("u_TransformNormal", transformNormal);

		DrawVertexArray(mesh->GetVertexArray());
	}

	void Renderer::Submit(const Ref<Model>& model, const Matrix4D& transform)
	{
		auto& meshes = model->GetMeshes();
		for (auto& mesh : meshes)
		{
			const auto& meshTransform = mesh->GetTransform();
			auto finalTransform = transform * meshTransform;
			Submit(mesh, finalTransform);
		}
	}

	void Renderer::OnWindowResize(UInt32 width, UInt32 height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
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
