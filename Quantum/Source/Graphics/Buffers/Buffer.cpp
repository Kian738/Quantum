#include "Buffer.h"

namespace Quantum
{
	void UnknownShaderTypeWarning(ShaderDataType type)
	{
		LOG_CHECK(false, Warning, LogGraphics, "Received unknown ShaderDataType: {}", static_cast<int>(type));
	}

	BufferElement::BufferElement(ShaderDataType type, const String& name, bool normalized)
		: Type(type)
		, Name(name)
		, Size(GetTypeSize(type))
		, Offset(0)
		, Normalized(normalized)
	{
	}

	UInt32 BufferElement::GetComponentCount() const
	{
		switch (Type)
		{
		case ShaderDataType::Int:
			return 1;
		case ShaderDataType::Int2:
			return 2;
		case ShaderDataType::Int3:
			return 3;
		case ShaderDataType::Int4:
			return 4;
		case ShaderDataType::Float:
			return 1;
		case ShaderDataType::Float2:
			return 2;
		case ShaderDataType::Float3:
			return 3;
		case ShaderDataType::Float4:
			return 4;
		case ShaderDataType::Mat3:
			return 3 * 3;
		case ShaderDataType::Mat4:
			return 4 * 4;
		case ShaderDataType::Bool:
			return 1;
		}

		UnknownShaderTypeWarning(Type);
		return 0;
	}

	UInt32 BufferElement::GetTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Int:
			return 4;
		case ShaderDataType::Int2:
			return 4 * 2;
		case ShaderDataType::Int3:
			return 4 * 3;
		case ShaderDataType::Int4:
			return 4 * 4;
		case ShaderDataType::Float:
			return 4;
		case ShaderDataType::Float2:
			return 4 * 2;
		case ShaderDataType::Float3:
			return 4 * 3;
		case ShaderDataType::Float4:
			return 4 * 4;
		case ShaderDataType::Mat3:
			return 4 * 3 * 3;
		case ShaderDataType::Mat4:
			return 4 * 4 * 4;
		case ShaderDataType::Bool:
			return 1;
		}

		UnknownShaderTypeWarning(type);
		return 0;
	}

	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
		: m_Elements(elements)
	{
		ComputeOffsetAndStride();
	}

	void BufferLayout::ComputeOffsetAndStride()
	{
		m_Stride = 0;

		auto offset = 0u;
		for (auto& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}
}
