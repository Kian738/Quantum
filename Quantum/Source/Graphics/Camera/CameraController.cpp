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

			auto rotation = glm::inverse(rotationX * rotationY);
			SetRotation(rotation * m_Camera->GetRotation()); // TODO: Handle rotation on event instead of every frame however may result in complications with physics
		}

		auto position = m_Camera->GetPosition();

		if (Input::IsKeyDown(Key::W))
			position -= m_Camera->GetOrientationZ() * cameraSpeed;
		if (Input::IsKeyDown(Key::S))
			position += m_Camera->GetOrientationZ() * cameraSpeed;

		if (Input::IsKeyDown(Key::A))
			position -= m_Camera->GetOrientationX() * cameraSpeed;
		if (Input::IsKeyDown(Key::D))
			position += m_Camera->GetOrientationX() * cameraSpeed;

		if (Input::IsKeyDown(Key::Q))
			position -= m_Camera->GetOrientationY() * cameraSpeed;
		if (Input::IsKeyDown(Key::E))
			position += m_Camera->GetOrientationY() * cameraSpeed;

		SetPosition(position);

		auto fov = m_Fov;

		if (Input::IsKeyDown(Key::Minus))
			fov -= 1.0f;
		if (Input::IsKeyDown(Key::Equal))
			fov += 1.0f;

		if (Input::IsKeyDown(Key::D0))
			fov = 45.0f; // TODO: Should be default fov instead of a hardcoded value but whatever

		SetFov(fov);
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
		m_Camera->SetPosition(position);
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
