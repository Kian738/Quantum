#pragma once

#include <entt/entt.hpp>

namespace Quantum
{
	class Scene
	{
	private:
		entt::registry m_Registry;
	public:
		Scene();
		~Scene();

		void Update(float deltaTime);

		entt::registry& GetRegistry() { return m_Registry; };
	};
}
