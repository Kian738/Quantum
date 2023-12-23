#include "CameraController.h"

#include "Core/Globals.h"

#undef near
#undef far
#undef max

namespace Quantum
{
	CameraController::CameraController(bool isPerspective, float aspectRatio, float fov, float near, float far)
		: m_IsPerspective(isPerspective)
		, m_AspectRatio(COALESCE(aspectRatio, GEngine->GetWindow().GetAspectRatio()))
		, m_Fov(fov)
		, m_Near(near)
		, m_Far(far)
	{
		float middle = glm::sqrt(m_Near * m_Far);
		float halfHeight = middle * glm::tan(glm::radians(m_Fov / 2.0f));
		m_ZoomLevel = glm::max(halfHeight, m_MinZoom);

		m_Camera = CreateScope<Camera>(ComputeProjection());

		SetPosition({ 0.0f, 0.0f, middle });

		GEngine->GetWindow().ResizeEvent += [this](int width, int height) { OnWindowResize(width, height); };
	}

	void CameraController::OnUpdate(float deltaTime)
	{
		auto rotationSpeed = m_RotationSpeed * deltaTime;
		auto zoomSpeed = m_ZoomSpeed * deltaTime;
		auto cameraSpeed = m_CameraSpeed * deltaTime;
		if (Input::IsShiftDown())
			cameraSpeed *= 2.0f;

		auto [mouseDeltaX, mouseDeltaY] = Input::GetMousePositionDelta();
		if (mouseDeltaX != 0.0f || mouseDeltaY != 0.0f)
		{
			auto rotationX = glm::angleAxis(glm::radians((float)mouseDeltaX * rotationSpeed), m_Camera->GetOrientationY());
			auto rotationY = glm::angleAxis(glm::radians((float)mouseDeltaY * rotationSpeed), m_Camera->GetOrientationX());
			auto addedRotation = glm::inverse(rotationX * rotationY);

			SetRotation(addedRotation * m_Camera->GetRotation()); // TODO: Handle rotation on event instead of every frame
		}

		if (Input::IsKeyDown(Key::W))
			m_CameraPosition -= m_Camera->GetOrientationZ() * cameraSpeed;
		if (Input::IsKeyDown(Key::S))
			m_CameraPosition += m_Camera->GetOrientationZ() * cameraSpeed;

		if (Input::IsKeyDown(Key::A))
			m_CameraPosition -= m_Camera->GetOrientationX() * cameraSpeed;
		if (Input::IsKeyDown(Key::D))
			m_CameraPosition += m_Camera->GetOrientationX() * cameraSpeed;

		if (Input::IsKeyDown(Key::Q))
			m_CameraPosition -= m_Camera->GetOrientationY() * cameraSpeed;
		if (Input::IsKeyDown(Key::E))
			m_CameraPosition += m_Camera->GetOrientationY() * cameraSpeed;

		SetPosition(m_CameraPosition);

		if (Input::IsKeyDown(Key::Minus))
			m_Fov -= 1.0f;
		if (Input::IsKeyDown(Key::Equal))
			m_Fov += 1.0f;

		SetFov(m_Fov);
	}

	void CameraController::SetZoomLevel(float zoomLevel)
	{
		// TODO: Implement
	}

	void CameraController::SetFov(float fov)
	{
		if (m_Fov == fov)
			return;

		m_Fov = fov;
		ResetProjection();
	}

	void CameraController::SetPerspective(bool isPerspective)
	{
		if (m_IsPerspective == isPerspective)
			return;

		m_IsPerspective = isPerspective;
		ResetProjection();
	}

	void CameraController::SetAspectRatio(float aspectRatio)
	{
		if (m_AspectRatio == aspectRatio)
			return;

		m_AspectRatio = aspectRatio;
		ResetProjection();
	}

	void CameraController::SetPosition(const Vector3& position)
	{
		m_CameraPosition = position;
		m_Camera->SetPosition(m_CameraPosition);
	}

	void CameraController::SetRotation(const Quaternion& rotation)
	{
		m_Camera->SetRotation(rotation);
	}

	void CameraController::OnWindowResize(int width, int height)
	{
		if (width == 0 || height == 0)
			return;

		SetAspectRatio((float)width / (float)height);
	}

	Matrix4 CameraController::ComputePerspectiveProjection()
	{
		return glm::perspective(
			glm::radians(m_Fov),
			m_AspectRatio,
			m_Near,
			m_Far
		);
	}

	Matrix4 CameraController::ComputeProjection()
	{
		return m_IsPerspective ? ComputePerspectiveProjection() : ComputeOrthographicProjection();
	}

	Matrix4 CameraController::ComputeOrthographicProjection()
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
		m_Camera->SetProjection(ComputeProjection());
	}
}
