#ifndef INHERITANCE_TEST_VCLASSINHERITANCE_HPP
#define INHERITANCE_TEST_VCLASSINHERITANCE_HPP

#include <iostream>
#include <string>


namespace inheritance_test
{

template<typename T1, typename T2>
class vclassinheritance
{
public:
    vclassinheritance(T1 const& str) : str_point(str) {};
    virtual void  processinher(T1 const& str)=0;
    virtual T1 const&  get_str()=0;
/*protected:
    void set_newstr(T1 str); */
private:
    T1 const& str_point;
};

}

#endif /* INHERITANCE_TEST_VCLASSINHERITANCE_HPP */




