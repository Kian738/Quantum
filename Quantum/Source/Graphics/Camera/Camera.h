#pragma once

#include "Core/Types.h"

namespace Quantum
{
	class Camera
	{
	private:
		static inline const Vector3D c_AxisX = { 1.0f, 0.0f, 0.0f };
		static inline const Vector3D c_AxisY = { 0.0f, 1.0f, 0.0f };
		static inline const Vector3D c_AxisZ = { 0.0f, 0.0f, 1.0f };

		Matrix4D m_ProjectionMatrix;
		Matrix4D m_ViewMatrix;
		Matrix4D m_ViewProjectionMatrix;

		Vector3D m_Position;
		Quaternion m_Rotation;

		Vector3D m_OrientationX = c_AxisX;
		Vector3D m_OrientationY = c_AxisY;
		Vector3D m_OrientationZ = c_AxisZ;
	public:
		Camera(const Matrix4D& projectionMatrix);

		const Matrix4D& GetProjection() const { return m_ProjectionMatrix; };
		const Matrix4D& GetView() const { return m_ViewMatrix; };
		const Matrix4D& GetViewProjection() const { return m_ViewProjectionMatrix; };

		const Vector3D& GetPosition() const { return m_Position; };
		const Quaternion& GetRotation() const { return m_Rotation; };

		const Vector3D& GetOrientationX() const { return m_OrientationX; };
		const Vector3D& GetOrientationY() const { return m_OrientationY; };
		const Vector3D& GetOrientationZ() const { return m_OrientationZ; };

		void SetProjection(const Matrix4D& projectionMatrix);

		void SetPosition(const Vector3D& position);
		void SetRotation(const Quaternion& rotation);
	private:
		void RecalculateViewMatrix();
	};
}
