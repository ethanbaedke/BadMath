#include "Mathematics.h"

namespace Lumex {
	namespace Mathematics {

		float SquareRoot(float x)
		{
			return 1.0f / InverseSquareRoot(x);
		}

		float InverseSquareRoot(float x)
		{
			float xhalf = 0.5f * x;
			int i = *(int*)&x;
			i = 0x5f3759df - (i >> 1);
			x = *(float*)&i;
			x = x * (1.5f - xhalf * x * x);
			x = x * (1.5f - xhalf * x * x);
			return x;
		}

	}
}