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
		Lock lock(m_Mutex);
		LOG_CHECK(!Exists(name), Warning, LogGraphics, "Shader \"{}\" already exists", name);
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::LoadAsync(StringView path)
	{
		AsyncHelper::Run([=]
			{
				auto shader = CreateRef<Shader>(GetPath(path));
				Add(shader);
			});
	}

	void ShaderLibrary::LoadAsync(const String& name, StringView path)
	{
		AsyncHelper::Run([=]
			{
				auto shader = CreateRef<Shader>(GetPath(path));
				Add(name, shader);
			});
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
