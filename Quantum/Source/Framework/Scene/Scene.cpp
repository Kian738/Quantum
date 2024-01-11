#include "Scene.h"

namespace Quantum
{
	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::Update(float deltaTime)
	{
		{
			auto view = m_Registry.view<ScriptComponent>();
		}
	}
}