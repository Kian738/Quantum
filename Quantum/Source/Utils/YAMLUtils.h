#pragma once

#include "Core/Types.h"
#include <yaml-cpp/yaml.h>

namespace Quantum
{
	class YAMLUtils
	{
	public:
		static YAML::Node Merge(const YAML::Node& a, const YAML::Node& b, bool& isDirty);
		static bool MergeTo(YAML::Node& target, const YAML::Node& source);
	};
}
