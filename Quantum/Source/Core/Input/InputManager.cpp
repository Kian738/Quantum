#include "InputManager.h"

#include "Core/Core.h"

DEFINE_LOG_CATEGORY_STATIC(Input);

namespace Quantum
{
	void Input::Initialize()
	{
		LOG(Info, LogInput, "Initializing Input Manager...");

		Reset();

		auto& window = GEngine->GetWindow();
		window.KeyEvent += [](int key, int scanCode, int action, int mods) { OnKeyChange(key, scanCode, action, mods); };
		window.MouseButtonEvent += [](int button, int action, int mods) { OnMouseButtonChange(button, action, mods); };
		window.MouseMoveEvent += [](double x, double y) { OnMouseMove(x, y); };
		window.MouseScrollEvent += [](double x, double y) { OnMouseScroll(x, y); };
	}

	void Input::Shutdown()
	{
		LOG(Info, LogInput, "Shutting down Input Manager...");

		Reset();

		// TODO: Unbind callbacks from window
	}

	void Input::Reset()
	{
		s_Modifiers = 0;

		s_Keys.reset();
		s_KeysPrev.reset();

		s_MouseButtons.reset();
		s_MouseButtonsPrev.reset();

		s_MousePosition = {};
		s_MousePositionPrev = {};
		s_MousePositionDelta = {};

		s_MouseScroll = {};
		s_MouseScrollPrev = {};
		s_MouseScrollDelta = {};
	}

	void Input::OnUpdate()
	{
		s_MousePositionDelta = {};
		s_MouseScrollDelta = {};
	}

	bool Input::ProcessChange(int key, int action, bool& state)
	{
		if (key < 0 || key >= s_Keys.size())
			return false;

		switch (action)
		{
		case GLFW_PRESS:
		case GLFW_REPEAT:
			state = true;
			break;
		case GLFW_RELEASE:
			state = false;
			break;
		default:
			return false;
		}

		return true;
	}

	void Input::OnKeyChange(int key, int scanCode, int action, int mods)
	{
		bool state;
		if (!ProcessChange(key, action, state))
			return;

		s_KeysPrev = s_Keys;

		s_Keys[key] = state;
		s_Modifiers = mods;
	}

	void Input::OnMouseButtonChange(int button, int action, int mods)
	{
		bool state;
		if (!ProcessChange(button, action, state))
			return;

		s_MouseButtonsPrev = s_MouseButtons;

		s_MouseButtons[button] = state;
		s_Modifiers = mods;
	}

	void Input::OnMouseMove(double x, double y)
	{
		s_MousePositionPrev = s_MousePosition;

		s_MousePosition.first = x;
		s_MousePosition.second = y;

		s_MousePositionDelta = SubtractVector(s_MousePosition, s_MousePositionPrev);
	}

	void Input::OnMouseScroll(double x, double y)
	{
		s_MouseScrollPrev = s_MouseScroll;

		s_MouseScroll.first = x;
		s_MouseScroll.second = y;

		s_MouseScrollDelta = SubtractVector(s_MouseScroll, s_MouseScrollPrev);
	}

	bool Input::IsModifierDown(KeyModifier modifier)
	{
		return (s_Modifiers & static_cast<UInt8>(modifier)) != 0;
	}

	Input::Vector2D Input::SubtractVector(const Vector2D& a, const Vector2D& b)
	{
		auto result = a;
		result.first -= b.first;
		result.second -= b.second;
		return result;
	}
}
