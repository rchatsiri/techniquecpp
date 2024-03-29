/*            Titles                            Authors                         Date
 *  - data_b test proxy concept.
 */

#include <iostream>
#include "shared_util.hpp"

using  namespace boost;

class data_b : public base_util
{
    public:
        data_b() {
            std::cout<< "Start data_b " <<std::endl;
        }
        std::string get_data() {
            this->data = "Data in data_b ";
            return this->data;
        }

        std::vector<shared_ptr<data_struct> >& get_ptr_info() {
            struct_str.data_vec.push_back(data);
            data_shared_ptr d_shared_ptr(&struct_str);

            //							 info_shared_ptr  info(d_shared_ptr);

            shared_ptr_info_vec.push_back(d_shared_ptr);
            return shared_ptr_info_vec;
        }


        void ptr_info(iconnect_util/*abs_read_connect*/ & ic_util) {

        }


        ~data_b() {

        }

    private:
        std::string data;

        data_struct struct_str;

        typedef shared_ptr<data_struct>   data_shared_ptr;
        //      typedef shared_ptr_info<data_struct>  info_shared_ptr;
        std::vector<shared_ptr<data_struct> >  shared_ptr_info_vec;

};

class proxy_b : public base_util
{
    public:
        proxy_b(): b(new data_b()) {

        }

        std::vector<shared_ptr<data_struct> >&   get_ptr_info() {
            return b->get_ptr_info();
        }

        std::string get_data() {
            return b->get_data();
        }

        void ptr_info(iconnect_util/*abs_read_connect*/ & ic_util) {
            b->ptr_info(ic_util);
        }

        ~proxy_b() {
            delete b;
        }


    private:
        proxy_b(const proxy_b&);
        const proxy_b& operator=(const proxy_b&);
        data_b   *b;
};


