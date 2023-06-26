#pragma once

namespace Core
{
	/*
	*	This keyboard's keys enum was created for store their code.
	*/
	namespace KeyBoard
	{
		enum class Key
		{
			NONE = -1,

			ENTER = 0x0D,
			ESC = 0x1B,

			// ---------------------------------------------
			// -- The arrow keys and some special keys    --
			// -- have two code for their representation. --
			// ---------------------------------------------
			IS_ARROW = 0xE0,

			LEFT = 0x4B,
			UP = 0x48,
			RIGHT = 0x4D,
			DOWN = 0x50,
			// ---------------------------------------------

			A = 0x41,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			Y,
			Z,
		};
	}
}