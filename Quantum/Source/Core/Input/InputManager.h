#pragma once

#include "Core/Types.h"
#include "Core/Window.h"
#include "KeyCodes.h"
#include "MouseCodes.h"

namespace Quantum
{
	enum class KeyModifier : UInt8
	{
		Shift = 1,
		Control = 2,
		Alt = 4,
		Super = 8,
		CapsLock = 16,
		NumLock = 32
	};

	// TODO: Add support for gamepad input
	// TODO: Rename to InputManager and add support for mappings
	class Input
	{
	private:
		static constexpr int c_KeyCount = 1024;
		static constexpr int c_MouseButtonCount = 256;

		static inline int s_Modifiers = 0;

		static inline Array<bool, c_KeyCount> s_Keys;
		static inline Array<bool, c_MouseButtonCount> s_MouseButtons;
		
		static inline Vector2D s_MousePosition;
		static inline Vector2D s_MouseScroll;
	public:
		static void Initialize();
		static void Shutdown();
		static void Reset();

		static bool IsKeyDown(KeyCode key) { return s_Keys[key]; };
		static bool IsKeyUp(KeyCode key) { return !s_Keys[key]; };

		static bool IsMouseButtonDown(MouseCode button) { return s_MouseButtons[button]; };
		static bool IsMouseButtonUp(MouseCode button) { return !s_MouseButtons[button]; };

		static bool IsShiftDown() { return IsModifierDown(KeyModifier::Shift); };
		static bool IsCtrlDown() { return IsModifierDown(KeyModifier::Control); };
		static bool IsAltDown()	{ return IsModifierDown(KeyModifier::Alt); };
		static bool IsSuperDown() { return IsModifierDown(KeyModifier::Super); };
		static bool IsCapsLockDown() { return IsModifierDown(KeyModifier::CapsLock); };
		static bool IsNumLockDown() { return IsModifierDown(KeyModifier::NumLock); };

		static Vector2D GetMousePosition() { return s_MousePosition; };
		static float GetMouseX() { return s_MousePosition.x; };
		static float GetMouseY() { return s_MousePosition.y; };

		static Vector2D GetMouseScroll() { return s_MouseScroll; };
		static float GetMouseScrollX() { return s_MouseScroll.x; };
		static float GetMouseScrollY() { return s_MouseScroll.y; };
	private:
		static void OnKeyChange(int key, int scanCode, int action, int mods);
		static void OnMouseButtonChange(int button, int action, int mods);

		static void OnMouseMove(double x, double y);
		static void OnMouseScroll(double x, double y);

		static bool IsModifierDown(KeyModifier modifier);
	};
}
