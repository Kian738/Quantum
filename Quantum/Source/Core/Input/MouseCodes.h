#pragma once

#include "Core/Types.h"

namespace Quantum
{
	using MouseCode = UInt16;

	namespace Mouse
	{
		enum : UInt16
		{
			Button0,
			Button1,
			Button2,
			Button3,
			Button4,
			Button5,
			Button6,
			Button7,

			ButtonLast = Button7,
			ButtonLeft = Button0,
			ButtonRight = Button1,
			ButtonMiddle = Button2
		};
	}
}
