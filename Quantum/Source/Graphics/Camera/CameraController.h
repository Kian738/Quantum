#pragma once

#include "Camera.h"
#include "Core/Types.h"

#undef near
#undef far

namespace Quantum
{
	class CameraController
	{
	private:
		Scope<Camera> m_Camera;

		float m_AspectRatio;
		float m_ZoomLevel;
		float m_Fov, m_Near, m_Far;

		bool m_IsPerspective;

		float m_CameraSpeed = 1.0f;
		float m_MinCameraSpeed = 0.1f, m_MaxCameraSpeed = 8.0f;

		float m_RotationSpeed = 10.0f;

		float m_ZoomSpeed = 0.1f;
		float m_MinZoom = 0.1f, m_MaxZoom = 4.0f;

		float m_FovSpeed = 1.0f;
		float m_MinFov = 1.0f, m_MaxFov = 179.0f;
	public:
		CameraController(
			const Vector3& position = { 0.0f, 0.0f, 0.0f },
			const Quaternion& rotation = { 0.0f, 0.0f, 0.0f, 1.0f },
			bool isPerspective = true,
			float aspectRatio = 0.0f,
			float fov = 45.0f,
			float near = 0.1f,
			float far = 1000.0f
		);

		void OnUpdate(float deltaTime);

		Camera& GetCamera() { return *m_Camera; };
		const Camera& GetCamera() const { return *m_Camera; };

		const float GetAspectRatio() const { return m_AspectRatio; };
		const float GetZoomLevel() const { return m_ZoomLevel; };
		const float GetFov() const { return m_Fov; };

		void SetZoomLevel(float zoomLevel);
		void SetFov(float fov);

		void SetPerspective(bool isPerspective);
		void SetAspectRatio(float aspectRatio);
		void SetPosition(const Vector3& position);
		void SetRotation(const Quaternion& rotation);
	private:
		void OnWindowResize(int width, int height);

		Matrix4 ComputeProjection();
		Matrix4 ComputePerspectiveProjection();
		Matrix4 ComputeOrthographicProjection();
		void ResetProjection();
	};
}
