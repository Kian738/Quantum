#pragma once

#include "Core/Types.h"
#include "Graphics/Resources/Texture.h"

namespace Quantum
{
	class AssetManager
	{
	private:
		static inline Dictionary<String, Ref<Texture>> m_Textures;
	public:
		static bool TextureExists(const String& name);
		static Ref<Texture> LoadTexture(const String& name, const String& path);
		static Ref<Texture> GetTexture(const String& name);
	};
}
