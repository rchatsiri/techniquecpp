#ifndef ICONNECT_UTIL_HPP
#define ICONNECT_UTIL_HPP

#include "shared_util.hpp"
#include <boost/shared_ptr.hpp>

using namespace boost;

struct data_struct_define;

typedef data_struct_define data_struct; 

class iconnect_util 
{
	public:

	virtual std::vector<shared_ptr<data_struct> >  shared_ptr_vec() =0;
	virtual void set_data_struct(data_struct &  d_str) = 0;
		
  //form base_util
//  virtual std::string get_data() = 0;
//  virtual std::vector<shared_ptr<data_s> > &  get_ptr_info() = 0; 



};

#endif /*ICONNECT_UTIL_HPP */
