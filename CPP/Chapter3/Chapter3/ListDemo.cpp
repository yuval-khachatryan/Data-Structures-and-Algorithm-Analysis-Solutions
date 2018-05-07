#include <iostream>
#include "List.h"
#include "Chapter3Routines.h"

namespace weiss_solutions 
{
    void listConstructorDemo() 
    {
        std::cout << "Creating new int list intList:\n";
        List<int> intList;

        std::cout << "List creation successful.\n";
        std::cout << "Current contents of the list:\n";
        for (int i : intList)
            std::cout << i << " ";
        std::cout << "\n";
    }

    void listInsertionDemo()
    {
        std::cout << "\nCreating list and inserting elements:\n";
        List<int> intList;
        
        std::cout << "Inserting first five even numbers at the end of the list.\n";
        
        for (int i = 1; i <= 5; ++i)
            intList.pushBack(2 * i);
        

        std::cout << "Contents of the list are: ";
        for (int i : intList) std::cout << i << " ";
        std::cout << "\n";

        std::cout << "Inserting first five odd numbers at the beginning of the list.\n";
        for (int i = 1; i <= 5; ++i)
            intList.pushFront(2 * i - 1);

        std::cout << "Contents of the list are: ";
        for (int i : intList) std::cout << i << " ";
        std::cout << "\n";

        std::cout << "\nRemoving list elements:\n";
        std::cout << "Removing two elements at the front:\n";
        intList.popFront();
        intList.popFront();
        std::cout << "The contents of the list are: ";
        for (int i : intList) std::cout << i << " ";
        std::cout << "\n";

        std::cout << "Removing an element at the back of the lsit:\n";
        intList.popBack();
        std::cout << "The contents of the list are: ";
        for (int i : intList) std::cout << i << " ";
        std::cout << "\n";

        std::cout << "Removing all elements in the list using erase function:\n";
        intList.erase(intList.begin(), intList.end());
        std::cout << "the contents of the list are: ";
        for (int i : intList) std::cout << i << " ";
        std::cout << "\n";
    }

    void listDemo()
    {
        listConstructorDemo();
        listInsertionDemo();
        std::cin.get();
    }
}