#ifndef LIST_CPP_
#define LIST_CPP_

#include "list.hpp"
#include <iostream>

#include "Except.h"
#include "StartConv.h"

//namespace list_type
//{

template<typename Object>
void list<Object>::init()
{
    the_size = 0;
    head = new node;
    tail = new node;
    head->next = tail;  // [head]->[next : address of tail ]
    tail->prev = head; 	// tail set  address of  head
}

template<typename Object>
list<Object>::list()
{
    std::cout<<" list::list() init ... " <<std::endl;
    init();
}


template<typename Object>
list<Object>::list(const list& rhs)
{
    init();
    *this = rhs;
}


template<typename Object>
const list<Object>& list<Object>::operator=(const list& rhs)
{
    std::cout<< " Operator = froom list<Object>::operator=(const list& rhs " <<std::endl;

    if(this == &rhs)
        return *this;

    make_empty();

    for( const_iterator itr = rhs.begin(); itr != rhs.end(); ++itr)
        push_back(*itr);

    return *this;
}


template<typename Object>
void list<Object>::make_empty()
{
    std::cout<< " call make_empty " <<std::endl;

    while(!empty())
        pop_front();
}




template<typename Object>
typename list<Object>::iterator list<Object>::begin()
{
    //				std::cout<<"Begin head = " << head->data <<std::endl;
    iterator iter(*this, head);
    return ++iter;
}

template<typename Object>
typename list<Object>::const_iterator  list<Object>::begin() const
{
    const_iterator  cons_iter(*this,head);
    return ++cons_iter;
}

template<typename Object>
typename list<Object>::iterator  list<Object>::end()
{
    return iterator(*this, tail);
}


template<typename Object>
typename list<Object>::const_iterator  list<Object>::end() const
{
    return const_iterator(*this, tail);
}

template<typename Object>
int list<Object>::size()const
{
    return the_size;
}

template<typename Object>
bool list<Object>::empty()const
{
    return size() == 0;
}

template<typename Object>
Object& list<Object>::front()
{
    return *begin();
}

template<typename Object>
const Object& list<Object>::front() const
{
    return *begin();
}

template<typename Object>
Object& list<Object>::back()
{
    return *--end();
}

template<typename Object>
const Object& list<Object>::back() const
{
    return *--end();
}

template<typename Object>
void list<Object>::push_front(const Object& x)
{
    insert(begin(), x); // begin increse ++iterator
}

template<typename Object>
void list<Object>::push_back(const Object& x)
{
    insert( end(), x); // insert to tail
}

//pop front
template<typename Object>
void list<Object>::pop_front()
{
    erase( begin());
}

template<typename Object>
void list<Object>::pop_back()
{
    erase( --end() );
}

template<typename Object>
typename list<Object>::iterator list<Object>::insert( iterator itr, const Object& x)
{
    itr.assertIsValid();
    if(itr.head != head) {
        throw IteratorOutOfBoundsException(" cannot erase at end()"); 
    }
		if(itr.head != head)
			throw IteratorMismatchException("erase iterator not in this list");

    node *p = itr.current;

		std::cout<< "### p->prev =  " << p->prev << ", current address p = " << p   << std::endl;
    p->prev->next = new node( x, p->prev, p);
		std::cout<< "### p->prev->next = " << p->prev->next <<std::endl;
    p->prev  = p->prev->next;
		std::cout<< "### p->prev = " << p->prev <<std::endl;
    the_size++;
		std::cout<< "-------------------------------------------------" <<std::endl;
    return iterator(*this, p->prev);

}

template<typename Object>
typename list<Object>::iterator list<Object>::erase(iterator iter)
{
		iter.assertIsValid();
    if(iter == end())
        std::cout<< " cannot erase at end() " <<std::endl;

    if(iter.head != head)
        std::cout<<"  erast iterator not in this list" <<std::endl;

    node *p = iter.current;
    iterator  ret_val( *this, p->next);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    the_size--;
    return ret_val;
}


template<typename Object>
typename list<Object>::iterator list<Object>::erase(iterator from, iterator to )
{
    for(iterator iter = from; iter != to; )
        iter = erase(iter);

    return to;
}


template<typename Object>
Object& const_list_iter<Object>::retrieve()const
{
		assertIsValid();
    if(current->next == NULL)
        std::cout<<" cannot perform *end() in list" <<std::endl;

    return current->data;
}

template<typename Object>
const Object& const_list_iter<Object>::operator * () const
{
    return retrieve();
}

template<typename Object>
const_list_iter<Object>& const_list_iter<Object>::operator++()
{
		std::cout<< "const_list_iter<Object>::operator ++() =  "<< current->next <<std::endl;
		assertCanAdvance();
    current  =  current->next;
    return *this;
}

template<typename Object>
const_list_iter<Object>  const_list_iter<Object>::operator++(int)
{
	  std::cout<<"const_list_iter<Object>::operator ++(int)  "<< this->current <<std::endl;
    const_list_iter<Object> old = *this;
    ++(*this);
		std::cout<<"operator++ (int ) address , old = " << old.current <<std::endl;
		std::cout<<"----------------------------------------------------" <<std::endl;
    return old;
}

template<typename Object>
const_list_iter<Object>& const_list_iter<Object>::operator --()
{
		assertCanRetreat();
    current = current->prev;
    return *this;
}

template<typename Object>
const_list_iter<Object> const_list_iter<Object>::operator --(int)
{
    const_list_iter<Object> old = *this;
    --(*this);
    return old;
}

/* node *  head  = & source; // pointer to source */
/* node *  current = *p ;    // pointer to pointer */
template<typename Object>
const_list_iter<Object>::const_list_iter( const list<Object>& source, node *p )
    :  head( source.head ) , current( p )
{

}


template<typename Object>
const_list_iter<Object>::const_list_iter() : head(NULL), current(NULL)
{
}


template<typename Object>
list_iter<Object>::list_iter(const list<Object>& source , node *p )
    : const_list_iter<Object>(source, p)
{
}

template<typename Object>
list_iter<Object>::list_iter()
{
}



template<typename Object>
bool const_list_iter<Object>::operator ==( const const_list_iter& rhs ) const
{

    return current == rhs.current;
}

template<typename Object>
bool const_list_iter<Object>::operator !=(const const_list_iter& rhs ) const
{
    return !( *this == rhs );
}


// Throws an exception if this iterator is obviously
// uninitialized. Otherwise, returns safely.
template <typename Object>
void const_list_iter<Object>::assertIsInitialized( ) const
{
    if( head == NULL || current == NULL )
        throw IteratorUninitializedException( "list iterator" );
}


// Throws an exception if the current position is
// not somewhere in the range from begin to end, inclusive.
// Otherwise, returns safely.
template <typename Object>
void const_list_iter<Object>::assertIsValid( ) const
{
    assertIsInitialized( );

    if( current == head )
        throw IteratorOutOfBoundsException( "At position prior to begin( ) in list" );
}

// Throws an exception if operator++ cannot be safely applied
// to the current position. Otherwise, returns safely.
template <typename Object>
void const_list_iter<Object>::assertCanAdvance( ) const
{
    assertIsInitialized( );

    if( current->next == NULL )
        throw IteratorOutOfBoundsException( "Cannot perform ++end( ) in list" );
}


// Throws an exception if operator-- cannot be safely applied
// to the current position. Otherwise, returns safely.
template <typename Object>
void const_list_iter<Object>::assertCanRetreat( ) const
{
    assertIsValid( );

    if( current->prev == head )
        throw IteratorOutOfBoundsException( "Cannot perform --begin( ) in list" );
}




// for list_iter
template<typename Object>
const Object& list_iter<Object>::operator *() const
{
    return const_list_iter<Object>::operator*();
}


template<typename Object>
Object& list_iter<Object>::operator*()
{
    return this->retrieve();
}

template<typename Object>
list_iter<Object>& list_iter<Object>::operator ++()
{
		this->assertCanAdvance();
    this->current = this->current->next;
    return *this;
}

template<typename Object>
list_iter<Object> list_iter<Object>::operator ++(int)
{
    list<Object>  old = *this; // Assigned value of pointer to old
    ++(*this);
    return old;
}

template<typename Object>
list_iter<Object>& list_iter<Object>::operator --()
{

		this->assertCanRetreat();
    this->current = this->current->prev;

    return *this;
}

template<typename Object>
list_iter<Object> list_iter<Object>::operator --(int)
{
    list<Object> old = *this;
    --(*this);
    return old;
}


template<typename Object>
void list<Object>::get_iter()
{
    const_list_iter<int>  clistiter  = end();
    ListNode<int> *ln =  clistiter.head;
    std::cout<< " ln tail value = "<< ln->data <<", prev = "
            << ln->prev << ", next->data = " << ln->next->data <<std::endl;
    std::cout<<"-----------------" <<std::endl;
}

template<class Collection>
void print_collection(const Collection& _the_list)
{
    const_list_iter<int> end_iter = _the_list.end();
    std::cout<< "check end in _the_list = " << *end_iter <<std::endl;

    for(const_list_iter<int> c_iter =  _the_list.begin(); c_iter != _the_list.end(); c_iter++) {
        std::cout<< " c_iter value push_front = " << *c_iter <<std::endl;
    }

}
//}


//using namespace list_type;
#include "EndConv.h"

#endif

