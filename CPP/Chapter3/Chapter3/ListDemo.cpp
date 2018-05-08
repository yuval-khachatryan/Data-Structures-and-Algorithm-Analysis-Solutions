#include <iostream>
#include "List.h"
#include "Chapter3Routines.h"

namespace weiss_solutions 
{
    template <class T>
    void printList(const List<T>& lst)
    {
        std::cout << "The contents of the list are: ";
        for (const T& t : lst)
            std::cout << t << " ";
        std::cout << "\n";
    }

    void listConstructorDemo() 
    {
        std::cout << "\nCreating new int list intList:\n";
        List<int> intList;

        std::cout << "List creation successful.\n";
        std::cout << "Current contents of the list:\n";
        printList<int>(intList);
    }

    /// <summary>Checks whether the insertion and deletion work properly</summary>
    void listInsertionDemo()
    {
        std::cout << "\nCreating list and inserting elements:\n";
        List<int> intList;
        
        std::cout << "Inserting first five even numbers at the end of the list.\n";
        
        for (int i = 1; i <= 5; ++i)
            intList.pushBack(2 * i);
        printList(intList);

        std::cout << "Inserting first five odd numbers at the beginning of the list.\n";
        for (int i = 1; i <= 5; ++i)
            intList.pushFront(2 * i - 1);

        std::cout << "Contents of the list are: ";
        printList(intList);

        std::cout << "\nRemoving list elements:\n";
        std::cout << "Removing two elements at the front:\n";
        intList.popFront();
        intList.popFront();
        std::cout << "The contents of the list are: ";
        for (int i : intList) std::cout << i << " ";
        std::cout << "\n";

        std::cout << "Removing an element at the back of the lsit:\n";
        intList.popBack();
        printList(intList);

        std::cout << "Removing all elements in the list using erase function:\n";
        intList.erase(intList.begin(), intList.end());
        printList(intList);
    }

    ///<summary>Creates an int list</summary>
    List<int> createIntList(int n = 10)
    {
        List<int> intList;
        for (int i = 0; i < n; ++i)
        {
            if (i % 2 == 0)
                intList.pushBack(i * 2);
            else
                intList.pushFront(-i * 3);
        }

        return intList;
    }

    /// <summary> Checks copy assignment and copy constructor
    void copyDemo()
    {
        std::cout << "\nCreating a list to copy from.\n";
        List<int> intList = createIntList(20);
        printList(intList);

        std::cout << "Copying the list:\n";
        auto intListCopy{ intList };
        printList(intListCopy);

        std::cout << "Creating a new list.\n";
        auto anotherIntList = createIntList(30);
        printList(intList);

        std::cout << "Copying the list to previous copy.\n";
        intListCopy = anotherIntList;
        printList(intListCopy);
    }

    /// <summary> Checks move constructor and move assignemnt constructor </summary>
    void moveDemo()
    {
        std::cout << "\nCreating a list from temporary list.\n";
        auto intList1{ createIntList() };
        printList(intList1);

        
        std::cout << "Creating a new list.\n";
        List<int> intList2;
        printList(intList2);

        std::cout << "Copying temporary list: \n";
        intList2 = createIntList(20);
        printList(intList2);
    }

    void listDemo()
    {
        listConstructorDemo();
        listInsertionDemo();
        copyDemo();
        moveDemo();
        std::cin.get();
    }
}