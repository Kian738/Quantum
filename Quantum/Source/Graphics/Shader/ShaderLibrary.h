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
		Mutex m_Mutex;
	public:
		void Add(const Ref<Shader>& shader);
		void Add(const String& name, const Ref<Shader>& shader);

		void LoadAsync(StringView path);
		void LoadAsync(const String& name, StringView path);

		Ref<Shader> Get(const String& name);
		const ShaderDictionary& GetShaders() const { return m_Shaders; };

		bool Exists(const String& name);
	private:
		String GetPath(StringView path);
	};
}
