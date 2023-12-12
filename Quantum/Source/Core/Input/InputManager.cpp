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

		s_Keys.fill(false);
		s_MouseButtons.fill(false);

		s_MousePosition = {};
		s_MouseScroll = {};
	}

	void Input::OnKeyChange(int key, int scanCode, int action, int mods)
	{
		if (key < 0 || key >= s_Keys.size())
			return;

		bool state;
		switch (action)
		{
			case GLFW_PRESS:
				state = true;
				break;
			case GLFW_RELEASE:
				state = false;
				break;
			case GLFW_REPEAT:
			default:
				return;
		}

		s_Modifiers = mods;
		s_Keys[key] = state;
	}

	void Input::OnMouseButtonChange(int button, int action, int mods)
	{
		if (button < 0 || button >= s_MouseButtons.size())
			return;

		bool state;
		switch (action)
		{
			case GLFW_PRESS:
				state = true;
				break;
			case GLFW_RELEASE:
				state = false;
				break;
			case GLFW_REPEAT:
			default:
				return;
		}

		s_Modifiers = mods;
		s_MouseButtons[button] = state;
	}

	void Input::OnMouseMove(double x, double y)
	{
		s_MousePosition.x = x;
		s_MousePosition.y = y;
	}

	void Input::OnMouseScroll(double x, double y)
	{
		s_MouseScroll.x = x;
		s_MouseScroll.y = y;
	}

	bool Input::IsModifierDown(KeyModifier modifier)
	{
		return (s_Modifiers & static_cast<UInt8>(modifier)) != 0;
	}
}
