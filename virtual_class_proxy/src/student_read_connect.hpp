#ifndef  STUDENT_READ_CONNECT_HPP
#define  STUDENT_READ_CONNECT_HPP

#include "connect_util.hpp"
#include "shared_util.hpp"

class student_read_connect : public connect_util
{
public:
 student_read_connect()
 {
	  data = "Student_read_conect";
		_data_str.data_vec.push_back(data);	
 }
 
 data_struct & get_data()
 {
		return  _data_str;
 }

 void view_data_str()
			{
					_data_str = this->data_str;
					std::cout<< "Data in student_read_connect = " << _data_str.data_vec.back() <<std::endl;
			}

private:

 std::string data;

 data_struct  _data_str;	
	
};

#endif /* STUDENT_READ_CONNECT_HPP */
