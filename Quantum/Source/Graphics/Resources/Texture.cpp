#include "Texture.h"

#include "Core/Core.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include <stb_image.h>

namespace Quantum
{
	Texture::Texture(UInt32 width, UInt32 height, void* data)
		: m_Path("")
		, m_Width(width)
		, m_Height(height)
	{
		Initialize(4);

		if (data)
			SetData(data);
	}

	Texture::Texture(const String& path)
		: m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		auto data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		LOG_CHECK(data, Error, LogGraphics, "Failed to load image: {}", path);

		m_Width = width;
		m_Height = height;
		m_BPP = m_Width * m_Height * channels;

		Initialize(channels);

		SetData(data);

		stbi_image_free(data);
	}

	Texture::~Texture()
	{
		Unbind();
		glDeleteTextures(1, &m_RendererID);
	}

	void Texture::Bind(UInt32 slot)
	{
		glBindTextureUnit(slot, m_RendererID);
	}

	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::SetData(void* data)
	{
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
		// TODO: Maybe generate mipmaps here?
	}

	void Texture::SetWrapMode(TextureWrapAxis axis, GLenum mode)
	{
		glTextureParameteri(m_RendererID, static_cast<GLenum>(axis), mode);
	}

	Ref<Texture> Texture::FromColor(const Vector4D& color)
	{
		auto colorData = GetColorData(color);
		return CreateRef<Texture>(1, 1, &colorData);
	}

	void Texture::Initialize(UInt32 channels)
	{
		m_BPP = m_Width * m_Height * channels;

		switch (channels)
		{
		case 3:
			m_InternalFormat = GL_RGB8;
			m_DataFormat = GL_RGB;
			break;
		case 4:
			m_InternalFormat = GL_RGBA8;
			m_DataFormat = GL_RGBA;
			break;
		}

		LOG_CHECK(m_InternalFormat & m_DataFormat, Error, LogGraphics, "Texture format not supported");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	UInt32 Texture::GetColorData(const Vector4D& color)
	{
		return
			static_cast<UInt32>(color.x * 255.0f) << 24 |
			static_cast<UInt32>(color.y * 255.0f) << 16 |
			static_cast<UInt32>(color.z * 255.0f) << 8 |
			static_cast<UInt32>(color.w * 255.0f);
	}
}
