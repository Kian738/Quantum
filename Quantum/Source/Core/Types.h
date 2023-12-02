#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

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

	using Vector2D = glm::vec2;
	using Vector3D = glm::vec3;
	using Vector4D = glm::vec4;

	using Matrix2D = glm::mat2;
	using Matrix3D = glm::mat3;
	using Matrix4D = glm::mat4;

	using String = std::string;
	using StringView = std::string_view;
	using WString = std::wstring;
	using WStringView = std::wstring_view;

	template <class KT, class T>
	using Dictionary = std::unordered_map<KT, T>;

	template <class T>
	using List = std::vector<T>;

	template <class T1, class T2>
	using Pair = std::pair<T1, T2>;

	template <class T>
	using Ref = std::shared_ptr<T>;

	template <typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <class T>
	using Scope = std::unique_ptr<T>;

	template <typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}
