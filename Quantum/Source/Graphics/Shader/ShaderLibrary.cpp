#include "ShaderLibrary.h"

#include "Core/Core.h"

namespace Quantum
{
	bool ShaderLibrary::Exists(const String& name)
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		Add(shader->GetName(), shader);
	}

	void ShaderLibrary::Add(const String& name, const Ref<Shader>& shader)
	{
		LOG_CHECK(!Exists(name), Warning, LogGraphics, "Shader \"{}\" already exists", name);
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Load(StringView path)
	{
		Add(CreateRef<Shader>(GetPath(path)));
	}

	void ShaderLibrary::LoadAll()
	{
		LOG(Debug, LogGraphics, "Loading all shaders...");

		const auto shaderFiles = FileSystemUtils::GetFiles(Project::GetActive()->GetShaderDir(), "glsl");
		for (auto& file : shaderFiles)
			Load(file);
	}

	void ShaderLibrary::Unload(const Ref<Shader>& shader)
	{
		shader->Unbind();

		auto it = std::find_if(
			m_Shaders.begin(),
			m_Shaders.end(),
			[shader](auto& pair) { return pair.second == shader; }
		);

		if (it != m_Shaders.end())
			m_Shaders.erase(it);
	}

	void ShaderLibrary::Unload(const String& name)
	{
		if (auto shader = Get(name); shader)
			Unload(shader);
	}

	void ShaderLibrary::UnloadAll()
	{
		LOG(Debug, LogGraphics, "Unloading all shaders...");

		for (auto it = m_Shaders.begin(); it != m_Shaders.end(); it = m_Shaders.begin())
			Unload(it->second);
	}

	void ShaderLibrary::Reload(const Ref<Shader>& shader)
	{
		auto name = shader->GetName();

		Unload(shader);
		Load(name);
	}

	void ShaderLibrary::Reload(const String& name)
	{
		if (auto shader = Get(name); shader)
			Reload(shader);
	}

	void ShaderLibrary::ReloadAll()
	{
		LOG(Debug, LogGraphics, "Reloading all shaders...");

		auto shaders = m_Shaders;
		for (auto& [name, shader] : shaders)
			Reload(shader);
	}

	Ref<Shader> ShaderLibrary::Get(const String& name)
	{
		if (Exists(name))
			return m_Shaders[name];

		LOG(Warning, LogGraphics, "Shader \"{}\" does not exist", name);
		return nullptr;
	}

	String ShaderLibrary::GetPath(StringView path)
	{
		return FileSystemUtils::CombinePath(Project::GetActive()->GetShaderDir(), path);
	}
}
