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
		AppContext(const char* projectPath);
		virtual ~AppContext() = default;

		virtual void Initialize() {};
		virtual void Update(double delta) {};
		virtual void Render() {};
		virtual void Shutdown() {};

		String GetProjectPath() const { return m_ProjectPath; };
	};
}
