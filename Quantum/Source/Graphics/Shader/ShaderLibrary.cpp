#include "ShaderLibrary.h"

#include "Core/Core.h"

namespace Quantum
{
	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		Add(shader->GetName(), shader);
	}

	void ShaderLibrary::Add(const String& name, const Ref<Shader>& shader)
	{
		LOG_CHECK(!Exists(name), Warning, LogGraphics, "Shader \"{}\" already exists", name);
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(StringView path)
	{
		auto shader = CreateRef<Shader>(GetPath(path));
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const String& name, StringView path)
	{
		auto shader = CreateRef<Shader>(GetPath(path));
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const String& name)
	{
		LOG_CHECK(Exists(name), Warning, LogGraphics, "Shader \"{}\" does not exist", name);
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const String& name)
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

	String ShaderLibrary::GetPath(StringView path)
	{
		return FileSystemUtils::CombinePath(Project::GetActive()->GetShaderDir(), path);
	}
}
