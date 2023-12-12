#include "CameraController.h"

#include "Core/Globals.h"

#undef near
#undef far
#undef max

namespace Quantum
{
	CameraController::CameraController(bool isPerspective, float aspectRatio, float fov, float near, float far)
		: m_IsPerspective(isPerspective)
		, m_AspectRatio(aspectRatio)
		, m_Fov(fov)
		, m_Near(near)
		, m_Far(far)
	{
		float middle = glm::sqrt(m_Near * m_Far);
		float halfHeight = middle * glm::tan(glm::radians(m_Fov / 2.0f));
		m_ZoomLevel = glm::max(halfHeight, m_MinZoom);

		m_Camera = CreateScope<Camera>(m_IsPerspective ? ComputePerspectiveProjection() : ComputeOrthographicProjection());

		SetPosition({ 0.0f, 0.0f, middle });
	}

	void CameraController::OnUpdate(float delta)
	{
		// TODO: Test this out
		auto& cameraRotation = m_Camera->GetRotation();
		if (Input::IsKeyDown(Key::W))
			m_CameraPosition -= m_Camera->GetZAxis() * m_CameraSpeed * delta;
		if (Input::IsKeyDown(Key::S))
			m_CameraPosition += m_Camera->GetZAxis() * m_CameraSpeed * delta;

		if (Input::IsKeyDown(Key::A))
			m_CameraPosition -= m_Camera->GetXAxis() * m_CameraSpeed * delta;
		if (Input::IsKeyDown(Key::D))
			m_CameraPosition += m_Camera->GetXAxis() * m_CameraSpeed * delta;

		if (Input::IsKeyDown(Key::Q))
			m_CameraPosition -= m_Camera->GetYAxis() * m_CameraSpeed * delta;
		if (Input::IsKeyDown(Key::E))
			m_CameraPosition += m_Camera->GetYAxis() * m_CameraSpeed * delta;


		SetPosition(m_CameraPosition);

		// TODO: Mouse input
	}

	void CameraController::SetPosition(const Vector3D& position)
	{
		m_CameraPosition = position;
		m_Camera->SetPosition(m_CameraPosition);
	}

	void CameraController::SetRotation(const Quaternion& rotation)
	{
		m_Camera->SetRotation(rotation);
	}

	void CameraController::SetPerspective(bool isPerspective)
	{
		if (m_IsPerspective == isPerspective)
			return;

		m_IsPerspective = isPerspective;
		ResetProjection();
	}

	Matrix4D CameraController::ComputePerspectiveProjection()
	{
		return glm::perspective(
			glm::radians(m_Fov),
			m_AspectRatio,
			m_Near,
			m_Far
		);
	}

	Matrix4D CameraController::ComputeOrthographicProjection()
	{
		auto halfWidth = m_AspectRatio * m_ZoomLevel;
		return glm::ortho(
			-halfWidth,
			halfWidth,
			-m_ZoomLevel,
			m_ZoomLevel,
			m_Near,
			m_Far
		);
	}

	void CameraController::ResetProjection()
	{
		auto projection = m_IsPerspective ? ComputePerspectiveProjection() : ComputeOrthographicProjection();
		m_Camera->SetProjection(projection);
	}
}
