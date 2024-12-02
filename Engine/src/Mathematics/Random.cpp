#include "Random.h"

#include "Mathematics/Math.h"

namespace Lumex {
	namespace Mathematics {

		uint32_t Random::m_State = -1;

		int Random::GetInt(int lowerInclusive, int upperInclusive)
		{
			// Linear Interpolate between the input integers as floats
			// We put the floats one outside the range on both ends to include the ends when the floats are casted back to ints
			float percent = GetRandom();
			float randomFloat = Math::LinearInterpolate(lowerInclusive - 1.0f, upperInclusive + 1.0f, percent);
			int randomInt = (int)randomFloat;

			return randomInt;
		}

		float Random::GetFloat(float lowerInclusive, float upperExclusive)
		{
			// Linear Interpolate between the two inputs
			// GetRandom() will never return 1, making the upper bound exclusive
			float percent = GetRandom();
			float randomFloat = Math::LinearInterpolate(lowerInclusive, upperExclusive, percent);

			return randomFloat;
		}

		float Random::GetRandom()
		{
			//Run the XorShift RNG Algorithm on the state
			m_State ^= m_State << 13;
			m_State ^= m_State >> 17;
			m_State ^= m_State << 5;

			// Get the states percent of a maximum 32-bit unsigned integer
			uint32_t max = -2;
			float percent = (float)m_State / max;

			return percent;
		}
	}
}