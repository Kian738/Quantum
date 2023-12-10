#include "Renderer.h"

#include "RenderCommand.h"

namespace Quantum
{
	void Renderer::Initialize()
	{
		RenderCommand::Initialize();

		s_SceneData = new SceneData;

		s_ShaderLibrary = CreateRef<ShaderLibrary>();
		s_ShaderLibrary->Load("Material");
	}

	void Renderer::Shutdown()
	{
		delete s_SceneData;
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
		for (auto& [name, shader] : s_ShaderLibrary->GetShaders())
			shader->Unbind();
	}

	void Renderer::Submit(const Mesh& mesh, const Matrix4D& transform)
	{
		static auto shader = s_ShaderLibrary->Get("Material");
		mesh.GetMaterial()->Bind(shader);
		shader->SetMat4("u_Transform", transform);
		auto transformNormal = glm::transpose(glm::inverse(Matrix3D(transform)));
		shader->SetMat3("u_TransformNormal", transformNormal);

		DrawVertexArray(mesh.GetVertexArray());
	}

	void Renderer::Submit(const Model& model, const Matrix4D& transform)
	{
		for (auto& mesh : model.GetMeshes())
			Submit(mesh, transform);
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
