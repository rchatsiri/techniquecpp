#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

#include "StartConv.h"

//namespace list_type
//{

    template<typename Object>
    class const_list_iter;
    template<typename Object>
    class list_iter;
    template<typename Object>
    class list;

    // internel class
    template <typename Object>
    class ListNode
    {
        private:
            Object data;
            ListNode  *prev;
            ListNode  *next;

            ListNode(const Object& d = Object(), ListNode *p = NULL, ListNode *n = NULL )
                : data(d), prev(p), next(n) { }
            friend class const_list_iter<Object>;
            friend class list_iter<Object>;
            friend class list<Object>;
    };


    template<typename Object>
    class list
    {
        public:
            typedef list_iter<Object>  iterator;
            typedef const_list_iter<Object> const_iterator;

            list();
            //            ~list();

            list(const list& rhs);
            const list& operator=(const list& rhs);

            iterator begin();
            const_iterator begin() const;

            iterator end();
            const_iterator end() const;

            int size() const;
            bool empty() const;

            Object& front();
            const Object& front() const;

            Object& back();
            const Object& back() const;

            void push_front( const Object& x);
            void push_back( const Object& x );

            void get_iter();
            void pop_front();
            void pop_back();

            iterator insert( iterator itr, const Object& x );
            iterator erase( iterator itr);
            iterator erase( iterator start, iterator end);

            friend class const_list_iter<Object>;
            friend class list_iter<Object>;

        private:
            typedef ListNode<Object> node;
            int  the_size;
            node *head;
            node *tail;

            void init();
            void make_empty();
    };

    template<typename Object>
    class const_list_iter
    {
        public:
            const_list_iter();
            virtual ~const_list_iter() {}
            virtual  const Object& operator * () const;

            const_list_iter&   operator++();
            const_list_iter  operator++(int);

            const_list_iter& operator--();
            const_list_iter operator--(int);

            bool operator==(	const const_list_iter& rhs )const;
            bool operator!=(  const const_list_iter& rhs )const;

        protected:
            typedef ListNode<Object> node;

            node *head;
            node *current;

            void assertIsInitialized( ) const;
            void assertIsValid( ) const;
            void assertCanAdvance( ) const;
            void assertCanRetreat( ) const;
            friend class list<Object>;
            Object& retrieve() const;

            const_list_iter(const list<Object>& source, node *p );
    };

    template<typename Object>
    class list_iter : public const_list_iter<Object>
    {
        public:
            list_iter();
            // initial for base class
            const Object& operator * () const;
            Object& operator *();

            list_iter& operator ++();
            list_iter operator ++(int);

            list_iter& operator --();
            list_iter operator --(int);
        protected:
            typedef ListNode<Object> node;
            friend class list<Object>;

            list_iter(const list<Object>& source, node *p );

    };



//}
#include "EndConv.h"

#include "list.cpp"

#endif /* LIST_H */
