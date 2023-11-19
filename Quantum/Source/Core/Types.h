#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <utility>

namespace Quantum
{
	using Int8 = signed char;
	using Int16 = short;
	using Int32 = int;
	using Int64 = long long;
	using UInt8 = unsigned char;
	using UInt16 = unsigned short;
	using UInt32 = unsigned int;
	using UInt64 = unsigned long long;

	using String = std::string;
	using StringView = std::string_view;
	using WString = std::wstring;
	using WStringView = std::wstring_view;

	template<class KT, class T>
	using Dictionary = std::unordered_map<KT, T>;

	template<class T>
	using List = std::vector<T>;

	template<class T1, class T2>
	using Pair = std::pair<T1, T2>;
}
