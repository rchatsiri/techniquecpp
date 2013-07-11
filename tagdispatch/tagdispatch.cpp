#include <iostream>
#include <typeinfo>
#include <string>
using namespace std ;

class Base;

class Base
  {
  public :
    typedef Base Parent ;
    virtual ~Base() {} ;
    virtual void f( Base& b ) = 0 ;
  } ;

 
template< class T > class Target 
  {
  public :
    virtual void f_impl( T& ) = 0 ;
  } ;

template<> class F<Base>
  {
  public :
    void f( Base& )
      {
      throw( bad_cast() );
      }
  } ;


 
template< class P > class AuxF
  {
  public :
    template< class T > static void   
    Dispatch( T* t, Base& b )
      {
      typedef F< P > FTParent ;
      static_cast< FTParent* >(t)->
      // navigate hierarchy
        F< P >::f( b ) ;
        // static bind (f is virtual)
      } 
  } ;

 
template<> class AuxF< Base >
  {
  public :
    template< class T > static void 
    Dispatch( T* t, Base& b )
      {
      throw( bad_cast() );
      }
  } ;

template< class T > class F : virtual public Base
  {
  public :
    void f( Base& b )
      {
      typedef Target< T > TargetT ;
      TargetT* t = 
      Dynamic_cast< TargetT* >(&b) ;
      if( t )
        t->f_impl( static_cast<T&>
                   (*this) ) ;
      else
        {
        typedef T::Parent TParent ;
        AuxF< TParent >::Dispatch(
          static_cast< T* >( this ), b ) ;
        }
      }
  } ;


// Project-specific file

#include <iostream>
using namespace std ;

class B ;  class C ;
class A : public F< A >, 
          public Target< A >,
          public Target< B >,
          public Target< C >
  {
  public :
    void f_impl( A& ) 
      { cout << A-A << endl ; }
    void f_impl( B& ) 
      { cout << A-B << endl ; }
    void f_impl( C& ) 
      { cout << A-C << endl ; }
  } ;

class B : public F< B >,
          public Target< A >,
          public Target< B >
  {
  public :
    void f_impl( A& ) 
      { cout << B-A << endl ; }
    void f_impl( B& ) 
      { cout << B-B << endl ; }  
  } ;

class C : public F< C >, public A
  {
  public :
    typedef A Parent  ;
    void f( Base& b ) 
      { F<C>::f(b) ; } 
    void f_impl( A& ) 
      { cout << C-A << endl ; }
    void f_impl( C& ) 
      { cout << C-C << endl ; }  
  } ;

 
 
int main()
  {
  A a ;
  B b ;
  C c ;
  Base& x1 = a ;
  Base& x2 = b ;
  Base& x3 = c ;

  x1.f( x1 ) ; // A-A
  x2.f( x1 ) ; // A-B
  x3.f( x1 ) ; // A-C
  x1.f( x2 ) ; // B-A
  x2.f( x2 ) ; // B-B
  x3.f( x2 ) ; // B-C  => B-A
  x1.f( x3 ) ; // C-A
  x2.f( x3 ) ; // C-B  => A-B
  x3.f( x3 ) ; // C-C

  return( 0 ) ;
  }
