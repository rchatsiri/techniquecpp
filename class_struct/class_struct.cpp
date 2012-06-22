#include <iostream>
#include <string>
#include "class_struct.hpp"


namespace class_struct
{
template<typename T>
iMainClass<T>::iMainClass() {}

template<typename T>
iMainClass<T>::~iMainClass() {}


template<typename T>
void iMainClass<T>::set_stmsg(T const& str_data_)
{
    stmsg msg = {str_data_, 1};
    std::cout<< " msg->str_data_ : "<< str_data_ <<std::endl;
		for(int i = 0; i < 5 ; i++)
			stmsg_map[i] = { str_data_,i };
}
}

/*template<typename T>
std::map<int, stmsg >& iMainClass<T>::get_stmsg_map()
{
		return ::stmsg_map;
}*/
/*template<typename T>
iMainClass<T>::stmsg& iMainClass<T>::get_stmsg_map()
{
		return ::stmsg_map;
}*/

int main()
{
    class_struct::iMainClass<std::string>  iMClass;
    std::string _str = "data";
    iMClass.set_stmsg(_str);
    //lmsg.value_data = 1;
}
