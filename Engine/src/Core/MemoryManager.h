#pragma once

#include <cstdlib>

#include "Singleton.h"

namespace Lumex {
	namespace Core {

		/* Forward declare LXPtr to make it a friend of MemoryManager so it can access the private RegisterPointer function */
		template <typename T>
		class LXPtr;

		class MemoryManager : public Singleton<MemoryManager>
		{
		private:
			/* The structure used by the VTable to manage memory for LXPtrs */
			struct VRow
			{
				void* DataAddress = nullptr;
				int ReferenceCount = 0;
			};

			/*
			* This is the reference table for memory managed using the LXPtr wrapper
			* It holds addresses that LXPtrs need to look at to find the values they "point" to
			* This is done so when managed data is moved in memory, LXPtrs continue to point to the correct data
			* This table also tracks how many references a variable in managed memory has so it can be freed automatically
			*/
			VRow* m_VTable;

			/* Starting size of the VTable */
			int m_VTableSize = 2;

		public:
			MemoryManager();

		private:
			/* Increase the size of the VTable by 100%, takes in the original table size since it may call itself recursively and needs to maintain this information */
			void GrowVTable(int originalTableSize);

			/* Try and insert an address into the VTable given the address and its hash value, returns true if insertion was successful with no collisions */
			bool InsertAddress(void* address, uintptr_t hash);

			/* Returns a hash value of the input address */
			uintptr_t HashAddress(void* address);

			/* Takes in an address to store in the VTable and returns its unique hash value */
			uintptr_t RegisterPointer(void* address);

			/* Returns an address in the VTable at an index cooresponding to the input hash value */
			void* GetAddress(uintptr_t hash);

			/* Called when an LXPtr is set equal to another LXPtr and the number of LXPtrs looking at an address needs to increment */
			void AddReference(uintptr_t hash);

			/* Called when an LXPtr has stopped looking at a value in the table, returns true if that slot no longer has any LXPtrs looking at it */
			bool RemoveReference(uintptr_t hash);

			template <typename T>
			friend class LXPtr;
		};

	}
}