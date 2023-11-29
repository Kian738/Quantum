#pragma once

#include "Core/Core.h"

namespace Quantum
{
	struct ProjectFile
	{
		String Name;
		String Description;
		String Version;
		String Company;
		String EngineVersion;
	};

	class Project
	{
	private:
		ProjectFile m_File;
		String m_Path;

		inline static Ref<Project> s_Active;
	public:
		Project(StringView directory, StringView name);
		Project(StringView path);
		~Project();

		String GetPath() const { return m_Path; };
		String GetDir() const;
		String GetContentDir() const;

		ProjectFile& GetFile() { return m_File; };

		StringView GetName() const { return m_File.Name; };
		StringView GetDescription() const { return m_File.Description; };
		StringView GetVersion() const { return m_File.Version; };
		StringView GetCompany() const { return m_File.Company; };
		StringView GetEngineVersion() const { return m_File.EngineVersion; };

		void SetName(StringView name) { m_File.Name = name; };
		void SetDescription(StringView description) { m_File.Description = description; };
		void SetVersion(StringView version) { m_File.Version = version; };
		void SetCompany(StringView company) { m_File.Company = company; };
		void SetEngineVersion(StringView engineVersion) { m_File.EngineVersion = engineVersion; };

		void Reload();
		void Save();

		static Ref<Project> New(StringView directory, StringView name);
		static Ref<Project> Load(StringView name);

		static Ref<Project> GetActive() { return s_Active; };
	};
}
