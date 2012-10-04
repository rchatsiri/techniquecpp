#ifndef CONNECT_UTIL_HPP
#define CONNECT_UTIL_HPP

#include <iostream>
//#include "iconnect_util.hpp"
#include "shared_util.hpp"

using namespace boost;

//struct data_struct_define;
//typedef data_struct_define data_struct;

class connect_util : public iconnect_util 
{

public:
  connect_util()
	{
		std::cout<< "Abstrace read connect " <<std::endl;
  }


 ~connect_util(){ }; 

	std::vector<shared_ptr<data_struct> >  shared_ptr_vec()
	{
		data = "Data in abs_read_connect ";
		data_str.data_vec.push_back(data);
		data_shared_ptr  d_shared_ptr(&data_str);
		shared_ptr_info_vec.push_back(d_shared_ptr);   
		return shared_ptr_info_vec;
	}

	void  set_data_struct(data_struct &  d_str)
	{
        data_str.data_vec.push_back(d_str.data_vec.back());
	}
 
	virtual data_struct & get_data() = 0;

protected:
	 std::string data;
	 typedef shared_ptr<data_struct>  data_shared_ptr;
	 std::vector<shared_ptr<data_struct> >  shared_ptr_info_vec; 
   data_struct  data_str;
};

#endif /* CONNECT_UTIL_HPP */
