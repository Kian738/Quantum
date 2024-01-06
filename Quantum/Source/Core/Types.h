#pragma once

#include <array>
#include <bitset>
#include <deque>
#include <fstream>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#define COALESCE(first, second) ((first) ? (first) : (second))

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

	using Quaternion = glm::quat;

	using Vector2 = glm::vec2;
	using Vector3 = glm::vec3;
	using Vector4 = glm::vec4;

	using Matrix2 = glm::mat2;
	using Matrix3 = glm::mat3;
	using Matrix4 = glm::mat4;

	using String = std::string;
	using StringView = std::string_view;
	using WString = std::wstring;
	using WStringView = std::wstring_view;

	using OFStream = std::ofstream;
	using IFStream = std::ifstream;

	using Mutex = std::mutex;

	template <class T = Mutex>
	using Lock = std::lock_guard<T>;

	template <UInt64 Bits>
	using BitSet = std::bitset<Bits>;

	template <typename T>
	using Func = std::function<T>;

	template <class KT, class T>
	using Dictionary = std::unordered_map<KT, T>;

	template <class T, UInt64 N>
	using Array = std::array<T, N>;

	template <class T>
	using Deque = std::deque<T>;

	template <class T>
	using List = std::vector<T>;

	template <class T1, class T2>
	using Pair = std::pair<T1, T2>;

	template <class T1, class T2>
	constexpr Pair<T1, T2> CreatePair(T1&& first, T2&& second)
	{
		return std::make_pair(std::forward<T1>(first), std::forward<T2>(second));
	}

	template <class T>
	using Ref = std::shared_ptr<T>;

	template <typename T, typename... Args>
	constexpr Ref<T> CreateRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <class T>
	using Scope = std::unique_ptr<T>;

	template <typename T, typename... Args>
	constexpr Scope<T> CreateScope(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}
