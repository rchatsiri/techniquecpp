#include "virtualclasstemplate.hpp"

namespace inheritance_test
{
template<typename T1, typename T2>
class a_inheritance : public vclassinheritance<T1,T2>
{
public:
    a_inheritance(T1 const& str) : vclassinheritance<T1,T2>(str), str_point_(str){

    }
    virtual void processinher(T1 const& str) {
       // set_newstr(str);
    }

    virtual T1 const& get_str() {
        return str_point_;
    }
private:
    T1 const& str_point_;

};
}

int main()
{
    std::cout<<" test virtual "<<std::endl;
    std::string const& str = "init value";
    //inheritance_test::vclassinheritance<std::string, std::string>  vcinher;
			inheritance_test::a_inheritance<std::string, std::string>  ainher(str);
}
