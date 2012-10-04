#include <iostream>
#include <sstream>
#include <boost/lexical_cast.hpp>
//#include "typeboosttest.hpp"

/*template<typename T2, typename T1>
inline T2 lexical_cast(const T1 &in) {
    T2 out;
    std::stringstream ss;
    ss << in;
    ss >> out;
    return out;
}*/

template <typename ElemT>
struct HexTo {
    ElemT value;
    operator ElemT() const {return value;}
    friend std::istream& operator>>(std::istream& in, HexTo& out) {
        in >> std::hex >> out.value;
        return in;
    }
};



int main()
{

std::string data_input = "8078FC6540EDEA0672E42DD850B52AB02F660F89D24F60";
//typecasting_test  casttype(data_input);
//casttype.casting2float();
//casttype.casting2short();
//casttype.casting2int();

//float data_type = lexical_cast<float>(data_input);
//std::cout<< "Data type float = " << data_type <<std::endl;

uint32_t value = boost::lexical_cast<HexTo<uint32_t> > (data_input);
std::cout << "Cast to unint32_t  value = " << value <<std::endl;

std::string value_str = boost::lexical_cast<std::string>(value);
std::cout << "Cast to string value_str = " << value_str <<std::endl;

}

