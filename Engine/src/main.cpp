#include <iostream>
#include <string>

#include "Core/MemoryManager.h"
#include "Core/LXPtr.h"

using namespace Lumex::Core;

// Declare testing functions from the Testing folder
extern void TEST_Mathematics();
extern void TEST_Memory();

int main()
{
	// Create managers
	MemoryManager* renderManager = new MemoryManager();

	// Testing
	//TEST_Mathematics();
	TEST_Memory();

	return 0;
}