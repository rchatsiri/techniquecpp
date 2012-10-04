#ifndef HNMAV_UTIL_CLUTIL_MEMORY_HPP
#define HNMAV_UTIL_CLUTIL_MEMORY__HPP

/* 						Titles														Authors 												Date
 * -Add utility for managment memory 						Chatsiri.rat										26/08/2012
 * -Move utiltity class to PIMP idom 						Chatsiri.rat										27/08/2012
 * -Add interface class													Chatsiri.rat										27/08/2012
 * -API concept using Proxy class	clutil_memory	Chatsiri.rat										01/09/2012
 */

/*3th libraries */
#include <boost/shared_ptr.hpp>
#include <vector>

#include "CL/cl.h"

#include "utils/base_clutil.hpp"
#include "utils/clutil_exception.hpp"

using namespace boost;

namespace hnmav_util
{
    //  struct variable info memory buffer*/
    struct memory_info {
        cl_mem mem_buffer;
        cl_context context;
    };

    //  memory internal initial, write Real Object here.
    class memory : public base_clutil
    {
        public:

            memory();

            bool  cl_create_buffer(std::size_t buffer_elements);

            std::vector<shared_ptr<platdevices_info> >&    get_platdevices_info_vec() {
                return platdevices_shared_ptr;
            }
            void set_platdevices_info_vec(std::vector<shared_ptr<platdevices_info> >& ptr_info) {
                platdevices_shared_ptr = ptr_info;
            }

            std::vector<shared_ptr<platdevices_info> >&   get_platdevices_info() {
                return  platdevices_shared_ptr;
            }


        private:

            std::size_t buffer_elements;
            std::vector<shared_ptr<platdevices_info> >  platdevices_shared_ptr;
            // cl define
            platdevices_info *platdevices;

    };

    memory::memory()
    {

    }


    bool memory::cl_create_buffer(std::size_t buffer_elements)
    {
        try {
            std::cout<<std::endl;
            std::cout<< "------------Start cl_create_buffer----------------- " <<std::endl;

            cl_int err = CL_SUCCESS;
            std::vector<shared_ptr<platdevices_info> > plat_vec = get_platdevices_info_vec();
            shared_ptr<platdevices_info>               plat_shared_ptr = plat_vec.back();
            platdevices_info *platdevices =  plat_shared_ptr.get();

            std::cout<< "cl_create_buffer->number_devices = " << platdevices->num_devices <<std::endl;
            std::cout<< "cl_carete_buffer->context        = " << platdevices->context <<std::endl;

            platdevices->mem_buffer = clCreateBuffer(platdevices->context,
                    CL_MEM_READ_WRITE,
                    sizeof(int) * buffer_elements * platdevices->num_devices,
                    NULL,
                    &err);

            if(err != CL_SUCCESS)
                throw clutil_exception(err, "clCreateBuffer");
        } catch(std::runtime_error&  ex) {
            std::cout << ex.what() <<std::endl;
        }

        std::cout<< "------------------------------------------------------ " <<std::endl;
        std::cout<<std::endl;
    }

    // Handeler memory
    class clutil_memory : public base_clutil
    {
        public:
            clutil_memory();

            void cl_create_buffer(std::size_t buffer_elements);

            ~clutil_memory();

            std::vector<shared_ptr<platdevices_info> >&    get_platdevices_info_vec() {
                return  memory_util->get_platdevices_info_vec();
            }
            void set_platdevices_info_vec(std::vector<shared_ptr<platdevices_info> >& ptr_info) {
                memory_util->set_platdevices_info_vec(ptr_info);
            }

            std::vector<shared_ptr<platdevices_info> >&   get_platdevices_info() {
                return  memory_util->get_platdevices_info();
            }



        private:
            memory *memory_util;

    };

    clutil_memory::clutil_memory() : memory_util(new memory())
    {

    }

    void  clutil_memory::cl_create_buffer(std::size_t buffer_elements)
    {
        memory_util->cl_create_buffer(buffer_elements);
    }

    clutil_memory::~clutil_memory()
    {

    }



}

#endif /*HNMAV_UTIL_CLUTIL_HPP */
