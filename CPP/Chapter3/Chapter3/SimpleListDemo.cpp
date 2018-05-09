#include <iostream>
#include "SimpleList.h"
#include "Chapter3Routines.h"

namespace weiss_solutions
{
    template <class T>
    void printSimpleList(const SimpleList<T>& lst)
    {
        std::cout << "The contents of the list are: ";
        for (const T& t : lst)
            std::cout << t << " ";
        std::cout << "\n";
    }

    void simpleListConstructorDemo()
    {
        std::cout << "\nCreating new int list intList:\n";
        SimpleList<int> intList;

        std::cout << "List creation successful.\n";
        std::cout << "Current contents of the list:\n";
        printSimpleList(intList);
    }

    /// <summary>Checks whether the insertion and deletion work properly</summary>
    void simpleListInsertionDemo()
    {
        std::cout << "\nCreating list and inserting elements:\n";
        SimpleList<int> intList;

        std::cout << "Inserting first five even numbers at the end of the list.\n";

        for (int i = 1; i <= 5; ++i)
            intList.pushFront(2 * i);
        printSimpleList(intList);

        std::cout << "Inserting first five odd numbers at the beginning of the list.\n";
        for (int i = 1; i <= 5; ++i)
            intList.pushFront(2 * i - 1);

        std::cout << "Contents of the list are: ";
        printSimpleList(intList);

        std::cout << "\nRemoving list elements:\n";
        std::cout << "Removing two elements at the front:\n";
        intList.popFront();
        intList.popFront();
        std::cout << "The contents of the list are: ";
        for (int i : intList) std::cout << i << " ";
        std::cout << "\n";

        std::cout << "Removing an element at the back of the lsit:\n";
        intList.popBack();
        printSimpleList(intList);

        std::cout << "Removing all elements in the list using erase function:\n";
        intList.erase(intList.begin(), intList.end());
        printSimpleList(intList);
    }

    ///<summary>Creates an int list</summary>
    SimpleList<int> createIntSimpleList(int n = 10)
    {
        SimpleList<int> intList;
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
    void simpleListCopyDemo()
    {
        std::cout << "\nCreating a list to copy from.\n";
        SimpleList<int> intList = createIntSimpleList(5);
        printSimpleList(intList);

        std::cout << "Copying the list:\n";
        auto intListCopy{ intList };
        printSimpleList(intListCopy);

        std::cout << "Creating a new list.\n";
        auto anotherIntList = createIntSimpleList(6);
        printSimpleList(intList);

        std::cout << "Copying the list to previous copy.\n";
        intListCopy = anotherIntList;

        std::cout << "Copying success!!\n";
        printSimpleList(intListCopy);

        
    }

    /// <summary> Checks move constructor and move assignemnt constructor </summary>
    void simpleListMoveDemo()
    {
        std::cout << "\nCreating a list from temporary list.\n";
        auto intList1{ createIntSimpleList() };
        printSimpleList(intList1);


        std::cout << "Creating a new list.\n";
        SimpleList<int> intList2;
        printSimpleList(intList2);

        std::cout << "Copying temporary list: \n";
        intList2 = createIntSimpleList(20);
        printSimpleList(intList2);
    }

    void simpleListIteratorTest()
    {
        SimpleList<int> intList = createIntSimpleList(10);
        const auto listStart = intList.begin();

        std::cout << "List first value is " << *listStart << "\n";
    }

    void simpleListDemo()
    {
        simpleListConstructorDemo();
        simpleListInsertionDemo();
        simpleListCopyDemo();
        simpleListCopyDemo();
        std::cin.get();
    }
}