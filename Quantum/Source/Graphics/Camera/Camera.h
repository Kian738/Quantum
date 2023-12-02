#pragma once

#include "Core/Types.h"

namespace Quantum
{
	class Camera
	{
	private:
		Matrix4D m_ProjectionMatrix;
		Matrix4D m_ViewMatrix;
		Matrix4D m_ViewProjectionMatrix;

		Vector3D m_Position;
		Quaternion m_Rotation;

		Vector3D m_OrientationX = { 1.0f, 0.0f, 0.0f };
		Vector3D m_OrientationY = { 0.0f, 1.0f, 0.0f };
		Vector3D m_OrientationZ = { 0.0f, 0.0f, 1.0f };
	public:
		Camera(const Matrix4D& projectionMatrix);

		const Matrix4D& GetProjection() const { return m_ProjectionMatrix; };
		const Matrix4D& GetView() const { return m_ViewMatrix; };
		const Matrix4D& GetViewProjection() const { return m_ViewProjectionMatrix; };

		const Vector3D& GetPosition() const { return m_Position; };
		const Quaternion& GetRotation() const { return m_Rotation; };

		const Vector3D& GetXAxis() const { return m_OrientationX; };
		const Vector3D& GetYAxis() const { return m_OrientationY; };
		const Vector3D& GetZAxis() const { return m_OrientationZ; };

		void SetProjection(const Matrix4D& projectionMatrix);
		void SetPosition(const Vector3D& position);
		void SetRotation(const Quaternion& rotation);
	private:
		void RecalculateViewMatrix();
	};
}
