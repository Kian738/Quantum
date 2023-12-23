#include "Camera.h"

namespace Quantum
{
	Camera::Camera(const Matrix4& projectionMatrix)
		: m_ProjectionMatrix(projectionMatrix)
		, m_ViewMatrix(1.0f)
		, m_ViewProjectionMatrix(m_ProjectionMatrix * m_ViewMatrix)
		, m_Position(0.0f)
		, m_Rotation(1.0f, 0.0f, 0.0f, 0.0f)
	{
	}

	void Camera::SetProjection(const Matrix4& projectionMatrix)
	{
		m_ProjectionMatrix = projectionMatrix;
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::SetPosition(const Vector3& position)
	{
		m_Position = position;
		RecalculateViewMatrix();
	}

	void Camera::SetRotation(const Quaternion& rotation)
	{
		m_Rotation = rotation;
		auto rotationMatrix = glm::mat3_cast(m_Rotation);
		m_OrientationX = rotationMatrix * c_AxisX;
		m_OrientationY = rotationMatrix * c_AxisY;
		m_OrientationZ = rotationMatrix * c_AxisZ;
		RecalculateViewMatrix();
	}

	void Camera::RecalculateViewMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position - m_OrientationZ, m_OrientationY);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
