#pragma once

#include "Camera.h"
#include "Core/Types.h"

namespace Quantum
{
	class CameraController
	{
	private:
		Scope<Camera> m_Camera;
		Vector3D m_CameraPosition;

		float m_AspectRatio;
		float m_ZoomLevel;
		float m_Fov, m_Near, m_Far;

		bool m_IsPerspective;

		float m_CameraSpeed = 1.0f;
		float m_RotationSpeed = 0.1f;

		float m_ZoomSpeed = 0.1f;
		float m_MinZoom = 0.1f, m_MaxZoom = 4.0f;

		float m_FovSpeed = 1.0f;
		float m_MinFov = 1.0f, m_MaxFov = 179.0f;
	public:
		CameraController(bool isPerspective = true,
			float aspectRatio = 16.0f / 9.0f,
			float fov = 45.0f,
			float near = 0.1f,
			float far = 1000.0f
		);

		void OnUpdate(float delta);

		Camera& GetCamera() { return *m_Camera; };
		const Camera& GetCamera() const { return *m_Camera; };

		const float GetAspectRatio() const { return m_AspectRatio; };
		const float GetZoomLevel() const { return m_ZoomLevel; };
		const float GetFov() const { return m_Fov; };

		void SetPosition(const Vector3D& position);
		void SetRotation(const Quaternion& rotation);
		void SetPerspective(bool isPerspective);
	private:
		Matrix4D ComputePerspectiveProjection();
		Matrix4D ComputeOrthographicProjection();
		void ResetProjection();
	};
}
