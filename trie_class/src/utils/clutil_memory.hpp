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
#include <boost/lexical_cast.hpp>
#include <vector>

#include "CL/cl.h"

#include "utils/base_clutil.hpp"
#include "utils/clutil_exception.hpp"
#include "utils/logger/clutil_logger.hpp"

namespace hnmav_util
{

	  using namespace boost;
    //  memory internal initial, write Real Object here.
    class memory : public base_clutil
    {
        public:

            memory();

            bool  cl_create_buffer(std::string buffer_elements);

            bool  cl_create_subbuffer();

            bool  cl_check_buffer_size();

            // Interface class
            std::vector<shared_ptr<platdevices_info> >&    get_platdevices_info_vec() {
                return platdevices_shared_ptr;
            }
            void set_platdevices_info_vec(std::vector<shared_ptr<platdevices_info> >& ptr_info) {
                platdevices_shared_ptr = ptr_info;
            }

            platdevices_info *get_platdevices_data() {
                shared_ptr<platdevices_info>   plat_shared_ptr = platdevices_shared_ptr.back();
                platdevices_info *platdevices =  plat_shared_ptr.get();
                return platdevices;
            }


        private:

            std::size_t buffer_elements;
            std::vector<shared_ptr<platdevices_info> >  platdevices_shared_ptr;
            // cl define
            platdevices_info *platdevices;

			      shared_ptr<clutil_logging<std::string, int> >  *  logger_ptr;
						clutil_logging<std::string, int>  *  logger;
     };

    memory::memory()
    {
        logger_ptr = &clutil_logging<std::string, int>::get_instance();
			  logger = logger_ptr->get();
    }

    bool memory::cl_create_subbuffer()
    {
        cl_int err = CL_SUCCESS;
        platdevices_info *platdevices = get_platdevices_data();

        try {
            for(int count_devices = 0; count_devices < platdevices->num_devices; count_devices++) {

                cl_buffer_region  region = {
                    buffer_elements *count_devices * sizeof(cl_char), // origin
                    buffer_elements * sizeof(cl_char) // size
                };

                if(platdevices->mem_input_buffers->size() == 0)
                    return false;

                cl_mem buffer =  clCreateSubBuffer(platdevices->mem_input_buffers->back(),
                        CL_MEM_READ_WRITE,
                        CL_BUFFER_CREATE_TYPE_REGION,
                        &region,
                        &err);

                platdevices->mem_input_buffers->push_back(buffer);
            }

            if(err == CL_SUCCESS)
                throw clutil_exception(err, "clCreateSubBuffer");

        } catch(std::runtime_error& ex) {
            logger->write_error( ex.what() ); 
            return false;
        }

        return true;
    }

    bool memory::cl_create_buffer(std::string  buffer_str)
    {
        logger->write_info("Start cl_create_buffer ");

        try {

            cl_int err = CL_SUCCESS;
            platdevices_info *platdevices 	= get_platdevices_data();
            // create buffer input & copy
            platdevices->mem_input_buffers 	= new std::vector<cl_mem>();
            platdevices->mem_copy_buffers 	= new std::vector<cl_mem>();
            std::istringstream  input_stream(buffer_str);
            input_stream >> platdevices->ibuffer;

            platdevices->buffer_elements 		=  buffer_str.size();
            platdevices->input_str 			 		=  buffer_str;

            logger->write_info("-- Convert String to float --");
            logger->write_info("-- Size of num_devices = ",  lexical_cast<std::string>( platdevices->num_devices) ); 

            cl_mem buffer_input = clCreateBuffer(platdevices->context,
                    CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
                    sizeof(cl_char) * platdevices->buffer_elements * platdevices->num_devices,
                    (void *)platdevices->input_str.c_str(),
                    &err);

            if(err != CL_SUCCESS)
                throw clutil_exception(err, "clCreateBuffer");

            logger->write_info("-- Initial buffer input completed, Address = ",  lexical_cast<std::string>( buffer_input) );

            cl_mem buffer_output =   clCreateBuffer(platdevices->context,
                    CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
                    sizeof(cl_char) * platdevices->buffer_elements * platdevices->num_devices,
                    (void *)platdevices->output_str.c_str(),
                    &err);

            /*        cl_mem size_input =  clCreateBuffer(platdevices->context,
                                CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                sizeof(cl_int),
                                &platdevices->buffer_elements,
                                &err);
            */


            if(err != CL_SUCCESS)
                throw clutil_exception(err, "clCreateBuffer");

            logger->write_info("-- Initial buffer output  completed, Address = ",  lexical_cast<std::string>(buffer_output));

            platdevices->mem_input_buffers->push_back(buffer_input);
            platdevices->mem_copy_buffers->push_back(buffer_output);

        } catch(std::runtime_error&  ex) {
            logger->write_error( ex.what() );
            return false;
        }

        return true;
    }

    bool memory::cl_check_buffer_size()
    {
        logger->write_info("Start cl_check buffer size ... "); 
        std::size_t buffer_size;
        platdevices_info *platdevices = get_platdevices_data();

        for(std::vector<cl_mem>::iterator iter = platdevices->mem_input_buffers->begin();
                iter != platdevices->mem_input_buffers->end();
                ++iter) {
            clGetMemObjectInfo(*iter,
                    CL_MEM_SIZE,
                    sizeof(cl_char) * platdevices->buffer_elements * platdevices->num_devices,
                    & buffer_elements,
                    NULL);
						
            logger->write_info("### buffer size = ",  lexical_cast<std::string>(buffer_size));
        }

        return true;
    }

    // Handeler memory
    class clutil_memory : public base_clutil
    {
        public:
            clutil_memory();

            void cl_create_buffer(std::string buffer_elements);
            bool cl_create_subbuffer();
            bool cl_check_buffer_size();

            ~clutil_memory();

            std::vector<shared_ptr<platdevices_info> >&    get_platdevices_info_vec() {
                return  memory_util->get_platdevices_info_vec();
            }
            void set_platdevices_info_vec(std::vector<shared_ptr<platdevices_info> >& ptr_info) {
                memory_util->set_platdevices_info_vec(ptr_info);
            }

            platdevices_info *get_platdevices_data() {
                return memory_util->get_platdevices_data();
            }

        private:
            memory *memory_util;

    };

    clutil_memory::clutil_memory() : memory_util(new memory())
    {

    }

    void  clutil_memory::cl_create_buffer(std::string buffer_elements)
    {
        memory_util->cl_create_buffer(buffer_elements);
    }

    bool  clutil_memory::cl_create_subbuffer()
    {
        return	memory_util->cl_create_subbuffer();
    }

    bool clutil_memory::cl_check_buffer_size()
    {
        return memory_util->cl_check_buffer_size();
    }

    clutil_memory::~clutil_memory()
    {

    }



}

#endif /*HNMAV_UTIL_CLUTIL_HPP */
