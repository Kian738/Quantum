#pragma once

#include "Core/Core.h"

namespace Quantum
{

	enum class ShaderDataType
	{
		None,
		Int, Int2, Int3, Int4,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Bool
	};

	void UnknownShaderTypeWarning(ShaderDataType type);

	struct BufferElement
	{
		ShaderDataType Type;
		String Name;
		UInt32 Size;
		UInt32 Offset;
		bool Normalized;

		BufferElement(ShaderDataType type, const String& name, bool normalized = false);

		UInt32 GetComponentCount() const;
	private:
		static UInt32 GetTypeSize(ShaderDataType type);
	};

	class BufferLayout
	{
	private:
		UInt32 m_Stride;
		List<BufferElement> m_Elements;
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferElement>& elements);

		UInt32 GetStride() const { return m_Stride; };
		const List<BufferElement>& GetElements() const { return m_Elements; };

		List<BufferElement>::iterator begin() { return m_Elements.begin(); };
		List<BufferElement>::iterator end() { return m_Elements.end(); };
		List<BufferElement>::const_iterator begin() const { return m_Elements.begin(); };
		List<BufferElement>::const_iterator end() const { return m_Elements.end(); };
	private:
		void ComputeOffsetAndStride();
	};
}
