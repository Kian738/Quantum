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
		using Vector2D = Pair<double, double>;

		static constexpr int c_KeyCount = 1024;
		static constexpr int c_MouseButtonCount = 256;

		static inline int s_Modifiers = 0;

		static inline BitSet<c_KeyCount> s_KeysPrev;
		static inline BitSet<c_KeyCount> s_Keys;

		static inline BitSet<c_MouseButtonCount> s_MouseButtonsPrev;
		static inline BitSet<c_MouseButtonCount> s_MouseButtons;
		
		static inline Vector2D s_MousePositionPrev;
		static inline Vector2D s_MousePosition;
		static inline Vector2D s_MousePositionDelta;

		static inline Vector2D s_MouseScrollPrev;
		static inline Vector2D s_MouseScroll;
		static inline Vector2D s_MouseScrollDelta;
	public:
		static void Initialize();
		static void Shutdown();
		static void Reset();

		static bool IsKeyDown(KeyCode key) { return s_Keys[key]; };
		static bool IsKeyUp(KeyCode key) { return !s_Keys[key]; };
		static bool IsKeyPressed(KeyCode key) { return s_Keys[key] && !s_KeysPrev[key]; };
		static bool IsKeyReleased(KeyCode key) { return !s_Keys[key] && s_KeysPrev[key]; };

		static bool IsMouseButtonDown(MouseCode button) { return s_MouseButtons[button]; };
		static bool IsMouseButtonUp(MouseCode button) { return !s_MouseButtons[button]; };
		static bool IsMouseButtonPressed(MouseCode button) { return s_MouseButtons[button] && !s_MouseButtonsPrev[button]; };
		static bool IsMouseButtonReleased(MouseCode button) { return !s_MouseButtons[button] && s_MouseButtonsPrev[button]; };

		static bool IsShiftDown() { return IsModifierDown(KeyModifier::Shift); };
		static bool IsCtrlDown() { return IsModifierDown(KeyModifier::Control); };
		static bool IsAltDown()	{ return IsModifierDown(KeyModifier::Alt); };
		static bool IsSuperDown() { return IsModifierDown(KeyModifier::Super); };
		static bool IsCapsLockDown() { return IsModifierDown(KeyModifier::CapsLock); };
		static bool IsNumLockDown() { return IsModifierDown(KeyModifier::NumLock); };

		static Vector2D GetMousePosition() { return s_MousePosition; };
		static float GetMouseX() { return s_MousePosition.first; };
		static float GetMouseY() { return s_MousePosition.second; };

		static Vector2D GetMousePositionDelta() { return s_MousePositionDelta; };
		static float GetMouseXDelta() { return s_MousePositionDelta.first; };
		static float GetMouseYDelta() { return s_MousePositionDelta.second; };

		static Vector2D GetMouseScroll() { return s_MouseScroll; };
		static float GetMouseScrollX() { return s_MouseScroll.first; };
		static float GetMouseScrollY() { return s_MouseScroll.second; };

		static Vector2D GetMouseScrollDelta() { return s_MouseScrollDelta; };
		static float GetMouseScrollXDelta() { return s_MouseScrollDelta.first; };
		static float GetMouseScrollYDelta() { return s_MouseScrollDelta.second; };

		static void OnUpdate();
	private:
		static bool ProcessChange(int key, int action, bool& state);

		static void OnKeyChange(int key, int scanCode, int action, int mods);
		static void OnMouseButtonChange(int button, int action, int mods);

		static void OnMouseMove(double x, double y);
		static void OnMouseScroll(double x, double y);

		static bool IsModifierDown(KeyModifier modifier);

		static Vector2D SubtractVector(const Vector2D& a, const Vector2D& b);
	};
}
