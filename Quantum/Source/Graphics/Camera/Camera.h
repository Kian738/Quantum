#pragma once

#include "Core/Types.h"

namespace Quantum
{
	class Camera
	{
	private:
		static inline const Vector3 c_AxisX = { 1.0f, 0.0f, 0.0f };
		static inline const Vector3 c_AxisY = { 0.0f, 1.0f, 0.0f };
		static inline const Vector3 c_AxisZ = { 0.0f, 0.0f, 1.0f };

		Matrix4 m_ProjectionMatrix;
		Matrix4 m_ViewMatrix;
		Matrix4 m_ViewProjectionMatrix;

		Vector3 m_Position;
		Quaternion m_Rotation;

		Vector3 m_OrientationX = c_AxisX;
		Vector3 m_OrientationY = c_AxisY;
		Vector3 m_OrientationZ = c_AxisZ;
	public:
		Camera(const Matrix4& projectionMatrix);

		const Matrix4& GetProjection() const { return m_ProjectionMatrix; };
		const Matrix4& GetView() const { return m_ViewMatrix; };
		const Matrix4& GetViewProjection() const { return m_ViewProjectionMatrix; };

		const Vector3& GetPosition() const { return m_Position; };
		const Quaternion& GetRotation() const { return m_Rotation; };

		const Vector3& GetOrientationX() const { return m_OrientationX; };
		const Vector3& GetOrientationY() const { return m_OrientationY; };
		const Vector3& GetOrientationZ() const { return m_OrientationZ; };

		void SetProjection(const Matrix4& projectionMatrix);

		void SetPosition(const Vector3& position);
		void SetRotation(const Quaternion& rotation);
	private:
		void RecalculateViewMatrix();
	};
}
