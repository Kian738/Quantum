#include "ConfigSection.h"
#include <SimpleIni.h>

namespace Quantum
{
	void ConfigSection::Load()
	{
		CSimpleIniA ini;
		ini.SetUnicode();
		ini.LoadFile("Config.ini");
		ini.SetLongValue(m_Name, "Test", 123);
		ini.SaveFile("Config.ini");
	}

	void ConfigSection::Save()
	{
	}
}
