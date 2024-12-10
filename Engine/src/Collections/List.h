#pragma once

namespace Lumex {
	namespace Collections {

		template<typename T>
		class List
		{
		public:
			/* The current number of elements in the list */
			size_t Length = 0;

		private:
			/* A pointer to the data this list holds on the heap */
			T* m_Data = nullptr;

			/* The maximum number of elements the list can currently hold */
			size_t m_Size = 2;

		public:
			List()
			{
				m_Data = new T[m_Size];
			}

			void Add(const T& element)
			{
				// If the list is full, increase its size
				if (Length == m_Size)
				{
					Grow();
				}

				m_Data[Length] = element;
				Length++;
				return m_Data[Length - 1];
			}

			/* Operator overload for getting and setting values in the list */
			T& operator[](size_t index)
			{
				return m_Data[index];
			}
			const T& operator[](size_t index) const
			{
				return m_Data[index];
			}

		private:
			void Grow()
			{
				// Store the old list
				T* oldData = m_Data;
				size_t oldSize = m_Size;

				// Double the size of our list
				m_Size *= 2;
				m_Data = new T[m_Size];

				// Copy the data from the old list to the new list
				for (size_t i = 0; i < oldSize; i++)
				{
					m_Data[i] = oldData[i];
				}

				// Delete the old data
				delete[] oldData;
			}
		};

	}
}