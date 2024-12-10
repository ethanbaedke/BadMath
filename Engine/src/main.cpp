#include <iostream>
#include <string>

#include "Collections/List.h"

// Declare testing functions from the Testing folder
extern void TEST_Mathematics();

using namespace Lumex::Collections;

int main()
{
	// Testing
	//TEST_Mathematics();

	List<int> myList;
	for (int i = 0; i < 10; i++)
	{
		myList.Add(i);
	}

	return 0;
}