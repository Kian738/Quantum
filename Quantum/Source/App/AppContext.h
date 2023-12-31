#pragma once

#include "Core/Types.h"
#include "Framework/Scene.h"

namespace Quantum
{
	class AppContext
	{
	private:
		String m_ProjectPath;
		Scope<Scene> m_Scene;
	public:
		AppContext() = delete;
		AppContext(const char* projectPath)
			: m_ProjectPath(projectPath)
		{};
		virtual ~AppContext() = default;

		virtual void Initialize() {};
		virtual void Update(float deltaTime) {};
		virtual void Render() {};
		virtual void RenderImGui() {};
		virtual void Shutdown() {};

		StringView GetProjectPath() const { return m_ProjectPath; };
	};
}
