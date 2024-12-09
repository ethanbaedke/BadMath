#include <iostream>
#include <string>

#include "Core/LXPtr.h"

using namespace Lumex::Core;

static class TEST_Class
{
public:
	int Value;

	TEST_Class(int value)
	{
		Value = value;
	}

	~TEST_Class()
	{
		std::cout << "Destroying TEST_Class(" + std::to_string(Value) + "), ";
	}
};

void TEST_Memory()
{
	// Test populating the VTable on the Memory Manager with lots of values
	std::cout << "Storing and displaying 100 test classes on the heap with VXPtrs..." << std::endl;
	{
		const int TEST_SIZE = 100;
		LXPtr<TEST_Class> ptrs[TEST_SIZE];
		for (int i = 0; i < TEST_SIZE; i++)
		{
			ptrs[i] = new TEST_Class(i);
		}

		for (int i = 0; i < TEST_SIZE; i++)
		{
			if (i % 10 == 0)
			{
				std::cout << std::endl << "   ";
			}
			std::cout << std::to_string(ptrs[i]->Value) << ", ";
		}

		std::cout << "\n\nExiting scope (should destroy all TEST_Class instances)...\n" << std::endl;
	}

	std::cout << std::endl;
}