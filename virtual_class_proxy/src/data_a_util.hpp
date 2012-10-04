/*            Titles                            Authors                         Date
 * - Base  data_a 													Chatsiri.rat											 05/09/2012
 *
 */
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <vector>
#include "shared_util.hpp"

using namespace boost;


class data_a : public base_util
{
    public:
        data_a() {
            std::cout<< "Start data_a " <<std::endl;
        }
        std::string get_data() {
            this->data = "Data in data_a ";
            return this->data;
        }

        std::vector<shared_ptr<data_struct> >& get_ptr_info() {
            struct_str.data_vec.push_back(data);
            data_shared_ptr d_shared_ptr(&struct_str);

            //							 info_shared_ptr  info(d_shared_ptr);

            shared_ptr_info_vec.push_back(d_shared_ptr);
            return  shared_ptr_info_vec;
        }
        ~data_a() {

        }

        void ptr_info(iconnect_util& ic_util) {
               std::cout<< "-------------------------------------------------" <<std::endl;
							 std::cout<< "In Data_a  interface with ic_util " <<std::endl;
               data_shared_ptr  d_ptr = ic_util.shared_ptr_vec().back();
							 data_struct * data  = d_ptr.get();
							 std::cout<< "ic_util get vector data_vec = " << data->data_vec.back() <<std::endl;
						   ic_util.set_data_struct(struct_str);						   	
               std::cout<< "-------------------------------------------------" <<std::endl;

        }


    private:
        std::string data;

        data_struct struct_str;

        typedef shared_ptr<data_struct>   data_shared_ptr;

        //        typedef shared_ptr_info<data_struct>  info_shared_ptr;

        std::vector<shared_ptr<data_struct> >  shared_ptr_info_vec;

};

class proxy_a : public base_util
{
    public:
        proxy_a(): a(new data_a()) {

        }

        std::vector<shared_ptr<data_struct> >&   get_ptr_info() {
            return a->get_ptr_info();
        }

        std::string get_data() {
            return a->get_data();
        }

        void ptr_info(iconnect_util& ic_util) {
            a->ptr_info(ic_util);
        }

        ~proxy_a() {
            delete a;
        }


    private:
        proxy_a(const proxy_a&);
        const proxy_a& operator=(const proxy_a&);
        data_a   *a;
};




