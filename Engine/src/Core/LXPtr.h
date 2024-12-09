#pragma once

#include <cstdint>

#include "MemoryManager.h"

namespace Lumex {
	namespace Core {

		template <typename T>
		class LXPtr
		{
		private:
			/*
			* Holds the hash calculated by the memory manager for its VTable
			* This way, when the VTable size changes and the location of the hash changes due to a difference in bounding, this LXPtr doesn't need to be updated since it has the true unbounded hash value
			*/
			uintptr_t m_AddressHash;

		public:
			/* Constructors */
			LXPtr()
			{
				m_AddressHash = MemoryManager::Get().RegisterPointer(nullptr);
			}
			LXPtr(T* address)
			{
				m_AddressHash = MemoryManager::Get().RegisterPointer(address);
			}
			LXPtr(const LXPtr& ptr)
			{
				m_AddressHash = ptr.m_AddressHash;
				MemoryManager::Get().AddReference(m_AddressHash);
			}

			/* Destructor */
			~LXPtr()
			{
				// If this pointer is null, destroy nothing
				if (m_AddressHash == static_cast<uintptr_t>(0))
				{
					return;
				}

				// Remove this pointer as a reference to a row in the table, if it is the last pointer looking at that row, delete the data
				if (MemoryManager::Get().RemoveReference(m_AddressHash))
				{
					delete operator->();
				}
			}

			/* Operator overloads */
			T& operator*()
			{
				return *(operator->());
			}
			T* operator->()
			{
				return reinterpret_cast<T*>(MemoryManager::Get().GetAddress(m_AddressHash));
			}
			LXPtr& operator=(const LXPtr& ptr)
			{
				// If we are setting this pointer equal to another pointer looking at the same location, do nothing
				if (m_AddressHash == ptr.m_AddressHash)
				{
					return *this;
				}

				// If this is not a nullptr, remove a reference from what this was already looking at
				if (m_AddressHash != static_cast<uintptr_t>(0))
				{
					if (MemoryManager::Get().RemoveReference(m_AddressHash))
					{
						delete operator->();
					}
				}

				// If we are setting this pointer to a non-null pointer, add a reference to that existing pointer
				if (ptr.m_AddressHash != static_cast<uintptr_t>(0))
				{
					MemoryManager::Get().AddReference(ptr.m_AddressHash);
				}

				m_AddressHash = ptr.m_AddressHash;
				return *this;
			}
		};
	}
}