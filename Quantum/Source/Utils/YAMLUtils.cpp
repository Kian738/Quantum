#include "YAMLUtils.h"

namespace Quantum
{
    YAML::Node YAMLUtils::Merge(const YAML::Node& a, const YAML::Node& b, bool& isDirty)
    {
        if (!b.IsMap())
            return b.IsNull() ? a : b;

        if (!a.IsMap())
        {
            isDirty = true;
            return b;
        }

        if (!b.size())
            return a;

        auto result = YAML::Node(YAML::NodeType::Map);
        for (auto it : a)
        {
            if (it.first.IsScalar())
                if (auto temp = b[it.first.Scalar()]; temp)
                {
                    result[it.first] = Merge(it.second, temp, isDirty);
                    continue;
                }
            result[it.first] = it.second;
        }

        for (auto it : b)
            if (!(it.first.IsScalar() || result[it.first.Scalar()]))
            {
                isDirty = true;
                result[it.first] = it.second;
            }

        return result;
	}

    bool YAMLUtils::MergeTo(YAML::Node& target, const YAML::Node& source)
    {
        bool isDirty = false;
        target = Merge(target, source, isDirty);
        return isDirty;
    }
}
