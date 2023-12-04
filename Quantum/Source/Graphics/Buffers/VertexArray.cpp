#include "VertexArray.h"

#include <glad/gl.h>

namespace Quantum
{
	static GLenum ShaderTypeToGLType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:
			return GL_INT;
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
		case ShaderDataType::Mat3:
		case ShaderDataType::Mat4:
			return GL_FLOAT;
		case ShaderDataType::Bool:
			return GL_BOOL;
		}
		
		UnknownShaderTypeWarning(type);
		return 0;
	}

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		LOG_CHECK(vertexBuffer->GetLayout().GetElements().size(), Error, LogGraphics, "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		auto index = 0u;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderTypeToGLType(element.Type),
				element.Normalized,
				layout.GetStride(),
				reinterpret_cast<const void*>(element.Offset)
			);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

	UInt32 VertexArray::GetVertexCount() const
	{
		if (m_IndexBuffer)
			return m_IndexBuffer->GetCount();
		else
		{
			auto count = 0u;
			for (const auto& buffer : m_VertexBuffers)
				count += buffer->GetVertexCount();
			return count;
		}
	}
}
