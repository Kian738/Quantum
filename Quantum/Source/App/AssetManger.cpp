#include "AssetManger.h"

#include "Core/Core.h"

namespace Quantum
{
	bool AssetManager::TextureExists(const String& name)
	{
		return m_Textures.find(name) != m_Textures.end();
	}

	Ref<Texture> AssetManager::LoadTexture(const String& name, const String& path)
	{
		if (TextureExists(name))
		{
			LOG(Error, LogGraphics, "Texture with name \"{}\" already exists", name);
			return nullptr;
		}

		auto texture = CreateScope<Texture>(path);
		m_Textures[name] = std::move(texture);

		LOG(Verbose, LogGraphics, "Loaded texture \"{}\"", name);
		return m_Textures[name];
	}

	Ref<Texture> AssetManager::GetTexture(const String& name)
	{
		if (!TextureExists(name))
		{
			LOG(Error, LogGraphics, "Texture with name \"{}\" does not exist", name);
			return nullptr;
		}

		return m_Textures[name];
	}
}
