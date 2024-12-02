#include <iostream>
#include <string>

#include "Core/RenderManager.h"

using namespace Lumex::Core;

// Declare testing functions from the Testing folder
extern void TEST_Mathematics();

int main()
{
	// Testing
	//TEST_Mathematics();

	// Test making a singleton
	RenderManager* renderManager = new RenderManager();
	std::cout << std::to_string(RenderManager::Get().TestFunction()) << std::endl;

	return 0;
}