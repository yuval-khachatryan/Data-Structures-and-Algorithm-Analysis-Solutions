#ifndef YK_WS_CH3_VECTOR_H
#define YK_WS_CH3_VECTOR_H

#include <algorithm>

/*
 * Implementation of Vector from chapter 3. Copying the code it to understand it better and may be find bugs.
 * Also, it is possible that it is used or improved it exercises.
 */

namespace weiss_solutions {
	template <typename Object>
	class Vector {
	public:
		static constexpr int SPARE_CAPACITY = 16;
		explicit Vector(int initSize = 0) : theSize{initSize}, theCapacity{initSize + SPARE_CAPACITY} 
		{
			objects = new Object[theCapacity];
		}

		Vector(const Vector & rhs) : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ nullptr }
		{
			objects = new Object[theCapacity];
			for (int i = 0; i < theSize; ++i)
				objects[i] = rhs.objects[i];
		}

		Vector& operator = (const Vector & rhs) {
			Vector copy = rhs;
			std::swap(*this, copy);
			return *this;
		}

		Vector(Vector && rhs) : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
		{
			rhs.theSize = 0;
			rhs.theCapacity = 0;
			rhs.objects = nullptr;
		}

		Vector& operator = (Vector && rhs)
		{
			std::swap(theSize, rhs.theSize);
			std::swap(theCapacity, rhs.theCapacity);
			std::swap(objects, rhs.objects);

            return *this;
		}

        ~Vector()
        {
            delete[] objects;
        }

		void reserve(int newCapacity)
		{
			if (newCapacity < theSize)
				return;

			Object * newOjects = new Object[newCapacity];
			for (int i = 0; i < newCapacity; ++i)
				newObjects[i] = std::move(objects[i]);

			theCapacity = newCapacity;
			std::swap(objects, newOjects);
			delete[] newOjects;
		}

		void resize(int newSize) {
			if (newSize > theCapacity) 
				reserve(newSize);
				
			theSize = newSize;
		}

		Object& operator[](int index) 
		{
			return objects[index];
		}

		const Object& operator[](int index) const
		{
			return objects[index];
		}

		bool empty() const
		{
			return theSize == 0;
		}

		int size() const
		{
			return theSize;
		}

		int capacity() const
		{
			return theCapacity;
		}

		void pushBack(const Object & x)
		{
			if (theSize == theCapacity)
				reserve(2 * theCapacity + 1);
			objects[theSize] = x;
			++theSize;
		}

		void pushBack(const Object && x)
		{
			if (theSize == theCapacity)
				reserve(2 * theCapacity + 1);
			objects[theSize] = std::move(x);
			++theSize;
		}


		void popBack()
		{
			--theSize;
		}

		const Object& back() const
		{
			return objects[theSize - 1];
		}

		typedef Object * iterator;
		typedef const Object * const_iterator;

		iterator begin()
		{
			return &objects[0];
		}

		iterator end()
		{
			return &objects[theSize];
		}

		const_iterator begin() const
		{
			return &objects[0];
		}

		const_iterator end() const
		{
			return &objects[theSize];
		}
		
	private:
		int theSize;
		int theCapacity;
		Object * objects;
	};



	
}

#endif
