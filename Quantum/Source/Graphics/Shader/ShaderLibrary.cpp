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
		Lock<> lock(m_ShaderMutex);
		LOG_CHECK(!Exists(name), Warning, LogGraphics, "Shader \"{}\" already exists", name);
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Load(StringView path)
	{
		Add(CreateRef<Shader>(GetPath(path)));
	}

	void ShaderLibrary::Load(const String& name, StringView path)
	{
		Add(name, CreateRef<Shader>(GetPath(path)));
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
