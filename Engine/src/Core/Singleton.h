#pragma once

namespace Lumex {
	namespace Core {

		/*
		* Parent class for managers that should only have one instance
		* <T> should be the type of the class that inherits from Singleton
		*/
		template<typename T>
		class Singleton
		{
		private:
			/* The single instance of the class inheriting from Singleton */
			static T* m_Instance;

		public:
			Singleton()
			{
				// Set the instance to the instantiated subclass
				m_Instance = static_cast<T*>(this);
			}

			/* Retrieve the instance */
			static T& Get()
			{
				return *m_Instance;
			}
		};

		template<typename T>
		T* Singleton<T>::m_Instance = nullptr;
	}
}