#ifndef SHARED_UTIL_HPP
#define SHARED_UTIL_HPP
/*            Titles                            Authors                         Date 
 * -Create interface connect to other class			Chatsiri.rat										05/09/2012
 *
 */             
#include "iconnect_util.hpp"

using namespace boost;
typedef struct data_struct_define {
    std::vector<std::string>  data_vec;
}data_struct;

template<typename info>
class 	shared_ptr_info
{
    public:
        shared_ptr_info(shared_ptr<data_struct> ptr) {
                data_vec.push_back(ptr);
            }

        shared_ptr<data_struct> *get_info() {
            return &data_vec.back();
        }

    private:
				std::vector<shared_ptr<data_struct> > data_vec;
};

class base_util
{
    public:

        virtual std::string get_data() = 0;

        virtual std::vector<shared_ptr<data_struct> > &  get_ptr_info() = 0; 

				virtual  void ptr_info(/*abs_read_connect*/ iconnect_util  &  ic_util) = 0;        
};
#endif /* SHARED_UTIL_HPP */
