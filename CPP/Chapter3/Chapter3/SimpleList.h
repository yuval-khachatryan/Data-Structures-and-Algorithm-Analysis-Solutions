#ifndef YH_WS_CHAPTER3_SIMPLE_LIST_H
#define YH_WS_CHAPTER3_SIMPLE_LIST_H

#include <algorithm>
#include <exception>

namespace weiss_solutions
{
    /// An implementation of singly linked list - used in some exercises

    template <typename Object>
    class SimpleList
    {
    private:
        struct Node
        {
            Object data;
            Node* next;

            Node(const Object& d = Object{}, Node* n = nullptr) : data{ d }, next{ n } {}
            Node(Object &&d, Node* n = nullptr) : data{ std::move(d) }, next{ n } {}
        };
    public:
        class const_iterator
        {
        public:
            const Object & operator * () const
            {
                return retrieve();
            }

            const_iterator & operator++()
            {
                previous = current;
                current = current->next;
                return *this;
            }

            const_iterator operator++(int)
            {
                const_iterator old = *this;
                previous = current;
                current = current->next;
                return old;
            }

            bool operator == (const const_iterator& itr)
            {
                return current == itr.current && previous == itr.previous;
            }

            bool operator != (const const_iterator& itr)
            {
                return current != itr.current || previous != itr.previous;
            }


        protected:
            Node * previous;
            Node * current;
            const SimpleList<Object> *theList;

            const_iterator(const SimpleList<Object>& lst, Node * prev, Node* curr)
                : theList{ &lst }, previous{ prev }, current{ curr } {}
            friend class SimpleList<Object>;

            void assertIsValid()
            {
                if (current == nullptr || previous == nullptr || theList == nullptr)
                    throw std::invalid_argument{ "List is not initialized." };
                if(previous == theList->tail || current == theList->head)  
                    throw std::out_of_range{ "Iterator out of range." };
                if (previous->next != current)
                {
                    std::cerr << "List consistence is broken";
                    throw std::logic_error{ "List consistence is broken." };
                }
            }

            Object & retrieve() const
            {
                return current->data;
            }
        };

        class iterator : public const_iterator
        {
        public:
            Object & operator* ()
            {
                return const_iterator::retrieve();
            }

            const Object & operator *() const
            {
                return const_iterator::operator*();
            }

            iterator& operator++()
            {
                this->previous = this->current;
                this->current = this->current->next;
                return *this;
            }

            iterator operator++(int)
            {
                iterator old = *this;
                previous = current;
                current = current->next;
                return old;
            }

        protected:
            iterator(const SimpleList<Object>& lst, Node * prev, Node * curr) : const_iterator{ lst, prev, curr } {}

            friend class SimpleList<Object>;
        };

        SimpleList()
        {
            init();
        }

        ~SimpleList()
        {
            clear();
            delete head;
            delete tail;
        }

        SimpleList(SimpleList<Object>& lst)
        {
            init();
            for (const Object & x : lst)
                pushBack(x);
        }

        SimpleList & operator = (SimpleList<Object>& lst)
        {
            SimpleList<Object> newValue{ lst };
            std::swap(newValue, *this);
            return *this;
        }

        SimpleList(SimpleList<Object>&& lst)
            : theSize{ lst.theSize }, head{ lst.head }, tail{ lst.tail }, lastNode{ lst.lastNode }
        {
            lst.theSize = 0;
            lst.head = nullptr;
            lst.tail = nullptr;
            lst.lastNode = nullptr;
        }

        SimpleList& operator = (SimpleList<Object>&& lst)
        {
            std::swap(theSize, lst.theSize);
            std::swap(head, lst.head);
            std::swap(tail, lst.tail);
            std::swap(lastNode, lst.lastNode);

            return *this;
        }

        ///<summary> Insert a node before the node pointed by itr.current</summary>
        iterator insert(iterator itr, const Object & x)
        {
            checkIterator(itr);
            theSize++;
            Node *current = itr.current;
            Node *previous = itr.previous;
            Node *newNode = new Node{ x, current };
            previous->next = newNode;
            if (itr == end() || theSize == 1)
                lastNode = newNode;
            return iterator{ *this, current, newNode };
        }

        ///<summary> Insert a node before the node pointed itr.current</summary>
        iterator insert(iterator itr, Object && x)
        {
            checkIterator(itr);
            theSize++;
            Node *current = itr.current;
            Node *previous = itr.previous;
            Node *newNode = new Node{ std::move(x), current };
            previous->next = newNode;
            if (itr == end())
                lastNode = newNode;
            return iterator(*this, current, newNode);
        }

        ///<summary> Erase the node pointed by itr.current</summary>
        iterator erase(iterator itr)
        {
            checkIterator(itr);
            if (itr.current == tail)
                throw std::out_of_range{ "End of the list reached." };
            theSize--;
            Node *current = itr.current;
            Node *previous = itr.previous;
            previous->next = current->next;
            if (current == lastNode)
                lastNode = previous;
            iterator result{ *this, previous, previous->next };
            checkIterator(result);
            delete current;
            return result;
        }

        /// <summary>
        /// Erases the nodes pointed by iterators between from and to.
        /// If to appears before from then all the nodes until the end node are deleted.
        /// To make it more safe, one might needs to check whether the range is valid first.
        /// </summary>
        iterator erase(iterator from, iterator to)
        {
            checkIterator(from);
            checkIterator(to);

            iterator itr = from;
            Node * lastNode = to.current;

            // erasing nodes might make to invalid.
            // hence instead of checking for equality with last node instead of its iterator
            while (itr != end() && itr.current != lastNode) {
                itr = erase(itr);
            }

            return itr;
        }

        /// <summary>
        /// Swaps two adjacent nodes - the first one pointed by position.
        /// Implemented as a part of exercise 2
        /// </summary>
        iterator swapNodes(iterator position)
        {
            checkIterator(position);
            if (position.current == lastNode)
                throw std::out_of_range("Can not swap last node.\n");

            auto previousNode = position.previous;
            auto firstNode = position.current;
            auto secondNode = firstNode->next;
            firstNode->next = secondNode->next;
            secondNode->next = firstNode;
            previousNode->next = firstNode;
            
            if (secondNode == lastNode) lastNode = firstNode;
            return iterator(*this, previousNode, previousNode->next);
        }

        void clear()
        {
            if (theSize > 0)
                erase(begin(), end());
        }

        iterator begin()
        {
            return iterator{ *this, head, head->next };
        }

        const_iterator begin() const
        {
            return const_iterator{ *this, head, head->next };
        }

        iterator end()
        {
            return iterator{ *this, lastNode, tail };
        }

        const_iterator end() const
        {
            return const_iterator{ *this, lastNode, tail };
        }

        iterator back()
        {
            iterator result = begin();
            while (result.current != lastNode)
                ++result;

            return result;
        }

        const_iterator back() const
        {
            const_iterator result = begin();
            while (result.current != lastNode)
                ++result;
            
            return result;
        }

        iterator pushFront(const Object & x)
        {
            return insert(begin(), x);
        }

        iterator pushFront(Object && x)
        {
            return insert(begin(), std::move(x));
        }

        iterator popFront()
        {
            if (theSize == 0)
                throw std::length_error("Length error. Iterator is emptpy.\n");
            return erase(begin());
        }


        iterator pushBack(Object && x)
        {
            return insert(end(), std::move(x));
        }

        iterator pushBack(const Object & x) 
        {
            return insert(end(), x);
        }

        iterator popBack()
        {
            return erase(back());
        }

    private:
        int theSize;
        Node * head;
        Node * tail;
        Node * lastNode;

        void init()
        {
            theSize = 0;
            head = new Node;
            tail = new Node;
            lastNode = head;
            
            head->next = tail;
        }

        void checkIterator(const_iterator itr)
        {
            itr.assertIsValid();
            if (itr.theList != this)
                throw std::out_of_range{ "The iterator doesn't point to current list" };
        }

    };

}

#endif
