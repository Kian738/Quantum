#pragma once

#include "Shader.h"
#include "Core/Types.h"

namespace Quantum
{
	class ShaderLibrary
	{
	private:
		using ShaderDictionary = Dictionary<String, Ref<Shader>>;

		ShaderDictionary m_Shaders;
	public:
		bool Exists(const String& name);

		void Add(const Ref<Shader>& shader);
		void Add(const String& name, const Ref<Shader>& shader);

		void Load(StringView path);
		void Load(const String& name, StringView path);
		void LoadAll();

		void Unload(const Ref<Shader>& shader);
		void Unload(const String& name);
		void UnloadAll();

		void Reload(const String& name);
		void ReloadAll();

		Ref<Shader> Get(const String& name);
		const ShaderDictionary& GetAll() const { return m_Shaders; };
	private:
		String GetPath(StringView path);
	};
}
