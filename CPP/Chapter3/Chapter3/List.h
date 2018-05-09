#ifndef YK_WS_CH3_LIST_H
#define YK_WS_CH3_LIST_H
#include <algorithm>
#include <exception>

// Implementation of the list class from Weiss book.
namespace weiss_solutions
{
    template <typename Object>
    class List
    {
    private:
        struct Node
        {
            Object data;
            Node *prev;
            Node *next;

            Node(const Object &d = Object{}, Node * p = nullptr, Node * n = nullptr)
                : data{ d }, prev{ p }, next{ n } {}
            Node(Object && d, Node *p = nullptr, Node * n = nullptr)
                : data{ std::move(d) }, prev{ p }, next{ n } {}
        };
    public:
        class const_iterator
        {
        public:        
            const Object & operator * () const
            {
                return retrieve();
            }

            const_iterator & operator++ ()
            {
                current = current->next;
                return *this;
            }

            const_iterator operator++ (int)
            {
                const_iterator old = *this;
                current = current->next;
                return old;
            }

            const_iterator & operator-- ()
            {
                current = current->prev;
                return *this;
            }

            const_iterator operator-- (int) {
                const_iterator old = *this;
                current = current->prev;
                return old;
            }
            
            bool operator==(const const_iterator & rhs) const
            {
                return current == rhs.current;
            }

            bool operator != (const const_iterator & rhs) const
            {
                return !(*this == rhs);
            }

        protected:
            const List<Object> *theList;
            Node * current;
            

            const Object & retrieve() const
            {
                return current->data;
            }

            const_iterator(const List<Object> &lst, Node * p) : theList{ &lst }, current { p } {}

            void assertIsValid() const
            {
                if (theList == nullptr || current == nullptr || current == theList->head)
                    throw std::out_of_range{ "Iterator out of range" };
            }

            friend class List<Object>;
        };

        class iterator : public const_iterator
        {
        public:

            Object & operator * ()
            {
                return this->current->data;
            }

            
            const Object & operator * () const
            {
                return const_iterator::operator*();
            }
            


            iterator & operator++ ()
            {
                this->current = this->current->next;
                return *this;
            }

            iterator operator++ (int)
            {
                iterator old = *this;   
                this->current = this->current->next;
                return old;
            }

            iterator & operator-- ()
            {
                this->current = this->current->prev;
                return *this;
            }

            iterator operator-- (int)
            {
                iterator old = *this;
                current = current->prev;
                return old;
            }

        protected:
            iterator(const List<Object>& lst, Node * p) : const_iterator{ lst, p } {}

            friend class List<Object>;
        };

        List()
        {
            init();
        }

        ~List()
        {
            clear();
            delete head;
            delete tail;
        }

        List(const List& rhs)
        {
            init();
            for (auto & x : rhs)
                pushBack(x);
        }

        List & operator = (const List& rhs)
        {
            List copy{ rhs };
            std::swap(*this, copy);
            return *this;
        }

        List(List&& rhs) : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}
        {
            rhs.theSize = 0;
            rhs.head = nullptr;
            rhs.tail = nullptr;
        }

        List & operator = (List&& rhs) {
            std::swap(theSize, rhs.theSize);
            std::swap(head, rhs.head);
            std::swap(tail, rhs.tail);

            return *this;
        }

        iterator begin()
        {
            return iterator{ *this, head->next };
        }

        const_iterator begin() const
        {
            return const_iterator{ *this, head->next };
        }

        iterator end()
        {
            return iterator{ *this, tail };
        }

        const_iterator end() const
        {
            return const_iterator{ *this, tail };
        }

        int size() const
        {
            return theSize;
        }

        bool empty() const
        {
            return size() == 0;
        }

        void clear()
        {
            while (!empty())
                popFront();
        }

        Object & front()
        {
            return *begin();
        }

        const Object & front() const
        {
            return *begin();
        }

        Object & back()
        {
            return *--end();
        }

        const Object & back() const
        {
            return *--end();
        }

        void pushFront(const Object & x)
        {
            insert(begin(), x);
        }

        void pushFront(Object && x)
        {
            insert(begin(), x);
        }

        void pushBack(const Object & x)
        {
            insert(end(), x);
        }

        void pushBack(Object && x)
        {
            insert(end(), x);
        }

        void popFront()
        {
            erase(begin());
        }

        void popBack()
        {
            erase(--end());
        }

        /// <summary>inserts the objects x before the position specified by itr</summary>
        iterator insert(iterator itr, const Object & x)
        {
            checkIterator(itr);
            Node *p = itr.current;
            ++theSize;
            Node *newNode = new Node{ x, p->prev, p };
            p->prev->next = newNode;
            p->prev = newNode;
            return iterator{*this, newNode };
        }

        /// <summary> inserts the temporary object x before the position specified by itr</summary>
        iterator insert(iterator itr, Object && x)
        {
            checkIterator(itr);
            Node *p = itr.current;
            ++theSize;
            Node newNode = { std::move(x), p ->prev, p };
            p->prev->next = newNode;
            p->prev = newNode;
            return iterator{*this, newNode };
        }

        iterator erase(iterator itr)
        {
            checkIterator(itr);
            Node* p = itr.current;
            iterator returnVal{ *this, p->next };
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete p;
            --theSize;

            return returnVal;
        }

        iterator erase(iterator from, iterator to)
        {
            checkIterator(from);
            checkIterator(to);
            for (iterator itr = from; itr != to; )
                itr = erase(itr);

            return to;
        }

    private:
        int theSize;
        Node * head;
        Node * tail;

        void init()
        {
            theSize = 0;
            head = new Node;
            tail = new Node;
            head->next = tail;
            tail->prev = head;
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