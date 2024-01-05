#pragma once

#include "Core/Types.h"
#include <glad/gl.h>

namespace Quantum
{
	enum class TextureWrapAxis : UInt32
	{
		Horizontal = GL_TEXTURE_WRAP_S,
		Vertical = GL_TEXTURE_WRAP_T
	};

	class Texture
	{
	private:
		UInt32 m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
		UInt32 m_Width, m_Height, m_BPP;
	public:
		Texture(UInt32 width, UInt32 height, UInt32 channels, void* data = nullptr);
		Texture(const String& path);
		~Texture();

		void Bind(UInt32 slot = 0);
		void Unbind();

		UInt32 GetWidth() const { return m_Width; }
		UInt32 GetHeight() const { return m_Height; }

		void SetData(void* data);
		void SetWrapMode(TextureWrapAxis axis, GLenum mode);
		
		static Ref<Texture> FromColor(const Vector3& color);
		static Ref<Texture> FromColor(const Vector4& color);
	private:
		void Initialize(UInt32 channels);

		static UInt32 GetColorData(const Vector3& color);
		static UInt32 GetColorData(const Vector4& color);
	};
}
