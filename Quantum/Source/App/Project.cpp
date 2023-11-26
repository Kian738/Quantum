#include "Project.h"
#include "yaml-cpp/yaml.h"

namespace Quantum
{
	Project::Project(StringView directory, StringView name)
	{
		FileSystemUtils::CreateDir(directory);
		m_Path = FileSystemUtils::CombinePath(directory, name, "qproj");
		std::ofstream file(m_Path);
		file.close();

		m_File.Name = name;
		m_File.EngineVersion = "1.0"; // TODO: Get engine version from somewhere

		Save();
	}

	Project::Project(StringView path)
		: m_Path(path)
	{
		Reload();
	}

	Project::~Project()
	{
		Save();
	}

	String Project::GetDir() const
	{
		static auto dir = StringUtils::BeforeLast(m_Path, "\\");
		return dir;
	}

	String Project::GetContentDir() const
	{
		static auto contentDir = FileSystemUtils::CombinePath(GetDir(), "Content");
		return contentDir;
	}

	void Project::Reload()
	{
		auto project = YAML::LoadFile(m_Path);
		m_File.Name = project["Name"].as<String>();
		m_File.Description = project["Description"].as<String>();
		m_File.Version = project["Version"].as<String>();
		m_File.Company = project["Company"].as<String>();
		m_File.EngineVersion = project["EngineVersion"].as<String>();
	}

	void Project::Save()
	{
		YAML::Emitter project;
		project << YAML::BeginMap;
		project << YAML::Key << "Name" << YAML::Value << m_File.Name;
		project << YAML::Key << "Description" << YAML::Value << m_File.Description;
		project << YAML::Key << "Version" << YAML::Value << m_File.Version;
		project << YAML::Key << "Company" << YAML::Value << m_File.Company;
		project << YAML::Key << "EngineVersion" << YAML::Value << m_File.EngineVersion;
		project << YAML::EndMap;

		FileSystemUtils::CreateParentDir(m_Path);
		std::ofstream file(m_Path);
		file << project.c_str();
		file.close();
	}

	Ref<Project> Project::New(StringView directory, StringView name)
	{
		s_Active = CreateRef<Project>(directory, name);
		return s_Active;
	}

	Ref<Project> Project::Load(StringView name)
	{
		auto path = FileSystemUtils::CombinePath(Environment::GetWorkingDir(), name, "qproj");
		s_Active = CreateRef<Project>(path);
		return s_Active;
	}
}
