#pragma once

#include "Singleton.h"

namespace Lumex {
	namespace Core {

		/* Right now, this class is simply a test for singletons */
		class RenderManager : public Singleton<RenderManager>
		{
		public:
			/* Returns the integere 5 for testing purposes */
			int TestFunction();
		};

	}
}