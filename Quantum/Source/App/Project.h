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

	// TODO: Move to Editor and make it only be loaded from Runtime
	class Project
	{
	private:
		ProjectFile m_File;
		String m_Path;
		bool m_IsDirty = false;

		static inline Ref<Project> s_Active;
	public:
		Project(StringView directory, StringView name);
		Project(StringView path);
		~Project();

		String GetPath() const { return m_Path; };
		String GetDir() const;
		String GetContentDir() const;
		String GetAssetsDir() const;
		String GetShaderDir() const;

		ProjectFile& GetFile() { return m_File; };

		StringView GetName() const { return m_File.Name; };
		StringView GetDescription() const { return m_File.Description; };
		StringView GetVersion() const { return m_File.Version; };
		StringView GetCompany() const { return m_File.Company; };
		StringView GetEngineVersion() const { return m_File.EngineVersion; };

		void SetDirty(bool dirty = true) { m_IsDirty = dirty; };
		void SetName(StringView name) { m_File.Name = name; SetDirty(); };
		void SetDescription(StringView description) { m_File.Description = description; SetDirty(); };
		void SetVersion(StringView version) { m_File.Version = version; SetDirty(); };
		void SetCompany(StringView company) { m_File.Company = company; SetDirty(); };
		void SetEngineVersion(StringView engineVersion) { m_File.EngineVersion = engineVersion; SetDirty(); };

		void Reload();
		void Save();

		static Ref<Project> New(StringView directory, StringView name);
		static Ref<Project> Load(StringView name);

		static Ref<Project> GetActive() { return s_Active; };
	};
}
