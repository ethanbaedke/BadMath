#include "MemoryManager.h"

namespace Lumex {
	namespace Core {

		MemoryManager::MemoryManager()
			: Singleton()
		{
			// Allocate the data for a VTable of the starting size
			m_VTable = new VRow[m_VTableSize];
			int a = 5 + 5;
		}

		void MemoryManager::GrowVTable(int originalTableSize)
		{
			// Store the old tables size and a pointer to the old table
			int oldTableSize = m_VTableSize;
			VRow* oldTable = m_VTable;

			// Create a new table that is double the size of the current table
			m_VTableSize = oldTableSize * 2;
			m_VTable = new VRow[m_VTableSize];

			// Insert all data in the old table into the new table, making sure to copy over the reference counts
			for (int i = 0; i < originalTableSize; i++)
			{
				// Ignore empty data addresses
				if (oldTable[i].DataAddress == nullptr)
				{
					continue;
				}

				uintptr_t hash = HashAddress(oldTable[i].DataAddress);
				if (InsertAddress(oldTable[i].DataAddress, hash))
				{
					size_t newIndex = hash %= m_VTableSize;
					m_VTable[newIndex].ReferenceCount = oldTable[i].ReferenceCount;
					continue;
				}

				// We hit a collision while copying the data over, resize the original table by its resize factor another time and try again
				delete m_VTable;
				m_VTable = oldTable;
				GrowVTable(originalTableSize);
			}

			// Delete the old table
			delete oldTable;
		}

		bool MemoryManager::InsertAddress(void* address, uintptr_t hash)
		{
			// Bound the index of that hash to the size of the table
			size_t index = hash %= m_VTableSize;

			// If the location at this index already contains our address, increment the counter
			if (m_VTable[index].DataAddress == address)
			{
				m_VTable[index].ReferenceCount++;
				return true;
			}

			// If the location is empty, populate it with our address and set the counter to one
			if (m_VTable[index].ReferenceCount == 0)
			{
				m_VTable[index].DataAddress = address;
				m_VTable[index].ReferenceCount = 1;
				return true;
			}

			// There was a collision
			return false;
		}

		uintptr_t MemoryManager::HashAddress(void* address)
		{
			uintptr_t addr = reinterpret_cast<uintptr_t>(address);
			addr ^= (addr >> 21);
			addr ^= (addr << 13);
			addr ^= (addr >> 7);
			return addr;
		}

		uintptr_t MemoryManager::RegisterPointer(void* address)
		{
			// Return a hash of 0 for null pointers
			if (address == nullptr)
			{
				return reinterpret_cast<uintptr_t>(nullptr);
			}

			// Hash the address and insert it into the VTable
			uintptr_t hash = HashAddress(address);
			if (InsertAddress(address, hash))
			{
				return hash;
			}

			// There was a collision, resize the VTable
			GrowVTable(m_VTableSize);

			// Recursive call this function to register the desired address with the new VTable
			return RegisterPointer(address);
		}

		void* MemoryManager::GetAddress(uintptr_t hash)
		{
			size_t index = hash %= m_VTableSize;
			return m_VTable[index].DataAddress;
		}

		void MemoryManager::AddReference(uintptr_t hash)
		{
			size_t index = hash %= m_VTableSize;
			m_VTable[index].ReferenceCount++;
		}

		bool MemoryManager::RemoveReference(uintptr_t hash)
		{
			size_t index = hash %= m_VTableSize;
			m_VTable[index].ReferenceCount--;
			return m_VTable[index].ReferenceCount == 0;
		}
	}
}