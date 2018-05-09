#include <list>
#include <exception>
#include <iostream>
#include "Chapter3Solutions.h"

namespace weiss_solutions
{
    namespace chapter3 
    {
        /// <summary>
        /// A function to check whether the indicies of the vector are ascending and positive. 
        /// Used for error checking in printLots
        /// </summary>
        bool isAsscendingAndInRange(const std::list<int>& intList, int upperBound)
        {
            int currentValue = *intList.begin();
            if (currentValue < 0 || currentValue > upperBound) return false;

            for (auto position = ++intList.begin(); position != intList.end(); ++position)
            {
                auto nextValue = *position;
                if (nextValue < currentValue || currentValue > upperBound) return false;
                currentValue = nextValue;
            }

            return true;

        }

        /// <summary>
        /// Function from exercise 1, chapter 3. 
        /// Prints the elements of the first list are in the positions specified by the second list.</summary>
        /// <param name = "theList">The list to print.</param>
        /// <param name = "positions">List of integers in ascending order.</param>
        template <typename T>
        void printLots(const std::list<T>& theList, const std::list<int>& printingIndicies, std::ostream& os = std::cout)
        {
            if (!isAsscendingAndInRange(printingIndicies, theList.size())) 
                throw std::out_of_range("Indicies must be ascesing and positive.");
            if (printingIndicies.empty()) 
                return;

            auto theListPosition = theList.begin();

            auto currentIndex = *printingIndicies.begin();
            for (int i = 0; i < currentIndex; ++i)
                ++theListPosition;

            os << *theListPosition << " ";

            for (auto position = ++printingIndicies.begin(); position != printingIndicies.end(); ++position)
            {
                auto distance = *position - currentIndex;
                for (int i = 0; i < distance; ++i)
                    ++theListPosition;

                os << *theListPosition << " ";
                currentIndex += distance;
            }
            
            os << "\n";
        }


        /// A demo of using the function printLots
        void exercise1()
        {
            std::list<int> intList;
            for (int i = 0; i < 10; ++i)
            {
                intList.push_back(i);
            }

            std::list<int> indicies;
            indicies.push_back(1);
            indicies.push_back(5);
            indicies.push_back(8);

            printLots(intList, indicies);
            std::cin.get();
        }
    }
}