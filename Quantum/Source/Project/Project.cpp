#include "Project.h"

namespace Quantum
{
	Project::Project(StringView path)
		: m_Path(path)
	{

	}

	void Project::Save()
	{

	}

	Ref<Project> Project::New(StringView directory, StringView name)
	{
		FileSystemUtils::CreateDir(directory);

		auto path = FileSystemUtils::CombinePath(directory, name, "yaml");
		std::ofstream file(path);
		file.close();

		s_Active = CreateRef<Project>(path);
		return s_Active;
	}

	Ref<Project> Project::Load(StringView path)
	{
		s_Active = CreateRef<Project>(path);
		return s_Active;
	}
}
