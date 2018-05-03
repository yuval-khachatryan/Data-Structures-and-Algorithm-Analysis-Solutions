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
				objects[k] = rhs.objects[k];
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
		}


		
	private:
		int theSize;
		int theCapacity;
		Object * objects;
	};



	
}

#endif
