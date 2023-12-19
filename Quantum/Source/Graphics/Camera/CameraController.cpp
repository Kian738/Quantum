#include "CameraController.h"

#include "Core/Globals.h"

#undef near
#undef far
#undef max

namespace Quantum
{
	CameraController::CameraController(bool isPerspective, float aspectRatio, float fov, float near, float far)
		: m_IsPerspective(isPerspective)
		, m_AspectRatio(aspectRatio) // TODO: Adapt to window size
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

	void CameraController::OnUpdate(float delta)
	{
		auto cameraSpeed = m_CameraSpeed * delta;
		if (Input::IsShiftDown())
			cameraSpeed *= 2.0f;

		auto& cameraRotation = m_Camera->GetRotation();
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

		// TODO: Implement camera rotation from mouse movement
		auto rotationSpeed = m_RotationSpeed * delta;
		if (Input::IsKeyDown(Key::Left))
			m_Camera->SetRotation(cameraRotation * glm::angleAxis(rotationSpeed, Vector3D(0.0f, 1.0f, 0.0f)));
		if (Input::IsKeyDown(Key::Right))
			m_Camera->SetRotation(cameraRotation * glm::angleAxis(-rotationSpeed, Vector3D(0.0f, 1.0f, 0.0f)));
		if (Input::IsKeyDown(Key::Up))
			m_Camera->SetRotation(cameraRotation * glm::angleAxis(rotationSpeed, Vector3D(1.0f, 0.0f, 0.0f)));
		if (Input::IsKeyDown(Key::Down))
			m_Camera->SetRotation(cameraRotation * glm::angleAxis(-rotationSpeed, Vector3D(1.0f, 0.0f, 0.0f)));

		// TODO: Implement camera zoom from mouse scroll
		auto zoomSpeed = m_ZoomSpeed * delta;
		// TODO: if (Input::GetMouseScroll delta)
	}

	void CameraController::SetZoomLevel(float zoomLevel)
	{
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

	void CameraController::SetPosition(const Vector3D& position)
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

	Matrix4D CameraController::ComputePerspectiveProjection()
	{
		return glm::perspective(
			glm::radians(m_Fov),
			m_AspectRatio,
			m_Near,
			m_Far
		);
	}

	Matrix4D CameraController::ComputeProjection()
	{
		return m_IsPerspective ? ComputePerspectiveProjection() : ComputeOrthographicProjection();
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
		m_Camera->SetProjection(ComputeProjection());
	}
}
