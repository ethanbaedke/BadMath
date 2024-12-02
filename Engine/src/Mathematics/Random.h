#pragma once

#include <stdint.h>

namespace Lumex {
	namespace Mathematics {

		class Random
		{
		public:
			/* Returs a random integer in the input range */
			static int GetInt(int lowerInclusive, int upperInclusive);

			/* Returns a random float in the input range */
			static float GetFloat(float lowerInclusive, float upperExclusive);

		private:
			/* Holds a random state that is regenerated with every random calculation */
			static uint32_t m_State;

			/* Returns a random float from 0 to 1, exclusive */
			static float GetRandom();
		};
	}
}