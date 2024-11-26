#include "Math.h"

#include <xmmintrin.h>

namespace Lumex {

		const float Math::PI = 3.1415927f;

		float Math::SquareRoot(float x)
		{
			return 1.0f / InverseSquareRoot(x);
		}

		float Math::Sin(float radian)
		{
			bool flip;
			float normRad = NormalizeRadian(radian, &flip);
			float sinValue = CalculateSinFromNormalizedRadian(normRad);

			if (flip)
				sinValue = -sinValue;

			return sinValue;
		}

		float Math::Cos(float radian)
		{
			bool flip;
			float normRad = NormalizeRadian(radian, &flip);
			float cosValue = CalculateCosFromNormalizedRadian(normRad);

			if (flip)
				cosValue = -cosValue;

			return cosValue;
		}

		float Math::Tan(float radian)
		{
			// We get the normalized radian and call our calculation functions rather than just Sin and Cos to avoid calling NormalizeRadian twice
			bool flip;
			float normRad = NormalizeRadian(radian, &flip);
			float sinValue = CalculateSinFromNormalizedRadian(normRad);
			float cosValue = CalculateCosFromNormalizedRadian(normRad);

			if (flip)
			{
				sinValue = -sinValue;
				cosValue = -cosValue;
			}

			float tanValue = sinValue / cosValue;

			return tanValue;
		}

		float Math::Arctan2(float y, float x)
		{
			// Handle X being zero to avoid division by zero
			if (x == 0)
			{
				// The vector made from our x and y values points straight up
				if (y > 0)
				{
					return PI / 2.0f;
				}
				// The vector made from our x and y values points straight down
				else if (y < 0)
				{
					return -PI / 2.0f;
				}
				// The input was (0, 0) and there is no angle to return
				else
				{
					return 0.0f;
				}
			}

			float ratio = y / x;

			// Get the arctan, making sure the input value to the function is between -1 and 1 (increases accuracy)
			float arctanValue;
			if (ratio > 1)
				arctanValue = (PI / 2) - Arctan(1.0f / ratio);
			else if (ratio < -1)
				arctanValue = -((PI / 2) + Arctan(1.0f / ratio));
			else
				arctanValue = Arctan(ratio);

			// Put the angle in the correct quadrent
			// Quadrents 1 or 4
			if (x > 0)
			{
				return arctanValue;
			}
			else
			{
				// Quadrent 2
				if (y > 0)
				{
					return arctanValue + PI;
				}
				// Quadrent 3
				else
				{
					return arctanValue - PI;
				}
			}
		}

		float Math::InverseSquareRoot(float x)
		{
			float xhalf = 0.5f * x;
			int i = *(int*)&x;
			i = 0x5f3759df - (i >> 1);
			x = *(float*)&i;
			x = x * (1.5f - xhalf * x * x);
			x = x * (1.5f - xhalf * x * x);
			return x;
		}

		float Math::NormalizeRadian(float radian, bool* outFlipSign)
		{
			if (radian > 0)
			{
				int backtrack = (int)((radian / PI) + 0.5f);
				*outFlipSign = backtrack % 2 != 0;
				float confined = radian - (PI * backtrack);
				return confined;
			}
			else
			{
				int backtrack = (int)((radian / PI) - 0.5f);
				*outFlipSign = backtrack % 2 != 0;
				float confined = radian - (PI * backtrack);
				return confined;
			}
		}

		float Math::CalculateSinFromNormalizedRadian(float radian)
		{
			// Approximate the sine of the normalized radian using a Taylor Series
			float mult = radian;
			float multInc = radian * radian;

			// x
			float e1 = mult;

			// x^3 / 3!
			mult *= multInc;
			float e2 = mult / 6.0f;

			// x^5 / 5!
			mult *= multInc;
			float e3 = mult / 120.0f;

			// x^7 / 7!
			mult *= multInc;
			float e4 = mult / 5040.0f;

			// x^9 / 9!
			mult *= multInc;
			float e5 = mult / 362880.0f;

			//x - (x^3 / 3!) + (x^5 / 5!) - (x^7 / 7!) + (x^9 / 9!)
			float sinValue = e1 - e2 + e3 - e4 + e5;

			return sinValue;
		}

		float Math::CalculateCosFromNormalizedRadian(float radian)
		{
			// Approximate the cosine of the normalized radian using a Taylor Series
			float multInc = radian * radian;
			float mult = multInc;

			// x
			float e1 = 1.0f;

			// x^2 / 2!
			float e2 = mult / 2.0f;

			// x^4 / 4!
			mult *= multInc;
			float e3 = mult / 24.0f;

			// x^6 / 6!
			mult *= multInc;
			float e4 = mult / 720.0f;

			// x^8 / 8!
			mult *= multInc;
			float e5 = mult / 40320.0f;

			//x - (x^2 / 2!) + (x^4 / 4!) - (x^6 / 6!) + (x^8 / 8!)
			float cosValue = e1 - e2 + e3 - e4 + e5;

			return cosValue;
		}

		float Math::Arctan(float ratio)
		{
			// Approximate the arctangent of the ratio using a Taylor Series
			float mult = ratio;
			float multInc = ratio * ratio;

			// x
			float e1 = mult;

			// x^3 / 3
			mult *= multInc;
			float e2 = mult / 3.0f;

			// x^5 / 5
			mult *= multInc;
			float e3 = mult / 5.0f;

			// x^7 / 7
			mult *= multInc;
			float e4 = mult / 7.0f;

			// x^9 / 9
			mult *= multInc;
			float e5 = mult / 9.0f;

			//x - (x^3 / 3) + (x^5 / 5) - (x^7 / 7) + (x^9 / 9)
			float arctanValue = e1 - e2 + e3 - e4 + e5;

			return arctanValue;
		}

}