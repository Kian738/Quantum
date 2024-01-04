#include "AssetManager.h"

#include "Core/Core.h"

namespace Quantum
{
	bool AssetManager::TextureExists(const String& name)
	{
		return m_Textures.find(name) != m_Textures.end();
	}

	// TODO: Load from /Assets
	Ref<Texture> AssetManager::LoadTexture(const String& path)
	{
		auto name = FileSystemUtils::GetFileName(path);

		if (TextureExists(name))
		{
			LOG(Warning, LogGraphics, "Texture with name \"{}\" already exists... Returning existing.", name);
			return m_Textures[name];
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
