#include "Camera.h"

namespace Quantum
{
	Camera::Camera(const Matrix4D& projectionMatrix)
		: m_ProjectionMatrix(projectionMatrix)
		, m_ViewMatrix(1.0f)
		, m_ViewProjectionMatrix(m_ProjectionMatrix * m_ViewMatrix)
		, m_Position(0.0f)
		, m_Rotation(1.0f, 0.0f, 0.0f, 0.0f)
	{
	}

	void Camera::SetProjection(const Matrix4D& projectionMatrix)
	{
		m_ProjectionMatrix = projectionMatrix;
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::SetPosition(const Vector3D& position)
	{
		m_Position = position;
		RecalculateViewMatrix();
	}

	void Camera::SetRotation(const Quaternion& rotation)
	{
		m_Rotation = rotation;
		auto rotationMatrix = glm::mat3_cast(m_Rotation);
		m_OrientationX = rotationMatrix * Vector3D(1.0f, 0.0f, 0.0f);
		m_OrientationY = rotationMatrix * Vector3D(0.0f, 1.0f, 0.0f);
		m_OrientationZ = rotationMatrix * Vector3D(0.0f, 0.0f, 1.0f);
		RecalculateViewMatrix();
	}

	void Camera::RecalculateViewMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position - m_OrientationZ, m_OrientationY);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
