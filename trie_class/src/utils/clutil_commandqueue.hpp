#ifndef  CLUTIL_COMMANDQUEUE_HPP
#define  CLUTIL_COMMANDQUEUE_HPP
/* 						Titles														Authors 												Date
 *-Support command queue (Interface send/receive with vector<shared_ptr<platdevices_info> >
 * 																						  Chatsiri.rat										07/09/2012
 *-Add input_str(Experimental with std::string). input_str is private variable
 * ( not plan include in struct name platdevices_info.
 * 																							Chatsiri.rat										09/09/2012
 *-Add  memory buffer input & output member function.
 * 																							Chatsiri.rat	                  11/09/2012
 */


#include <boost/shared_ptr.hpp>

#include <iostream>
#include "base_clutil.hpp"
#include "clutil_infodevice.hpp"

namespace hnmav_util
{
    using namespace boost;

    class commandqueue : public base_clutil
    {
        public:

            commandqueue(std::size_t buffer_elements_) : buffer_elements(buffer_elements_) {
                 logger_ptr = &clutil_logging<std::string, int>::get_instance();
          			 logger = logger_ptr->get();
						}

            bool cl_create_command_queue();
            bool cl_write_event();
            bool cl_call_kernel();
            bool cl_read_buffer();

            bool cl_enqueue_task();
            bool cl_enqueue_copy_buffer();
            bool cl_enqueue_map_buffer();
            bool cl_enqueue_unmap_buffer();

            bool add_input_str(std::string input_str);


            // Interface class
            std::vector<shared_ptr<platdevices_info> >&    get_platdevices_info_vec() {
                return platdevices_shared_ptr;
            }
            void set_platdevices_info_vec(std::vector<shared_ptr<platdevices_info> >& ptr_info) {
                platdevices_shared_ptr = ptr_info;
            }

            platdevices_info *get_platdevices_data() {
                shared_ptr<platdevices_info>   plat_shared_ptr =  platdevices_shared_ptr.back();
                platdevices_info *platdevices =  plat_shared_ptr.get();
                return platdevices;
            }

        private:

            std::size_t buffer_elements;
            std::vector<shared_ptr<platdevices_info> >  platdevices_shared_ptr;
            // cl define
            platdevices_info *platdevices;
            void   *mapped_memory;
					  shared_ptr<clutil_logging<std::string, int> > * logger_ptr;				
						clutil_logging<std::string, int>  * logger;	
    };


    bool commandqueue::cl_enqueue_unmap_buffer()
    {
        logger->write_info("Start Unmap buffer ");
        platdevices_info *platdevices = get_platdevices_data();
        cl_int err = CL_SUCCESS;

        try {
            err = clEnqueueUnmapMemObject(platdevices->queues.back(),
                    platdevices->mem_copy_buffers->back(),
                    mapped_memory,
                    0,
                    NULL,
                    NULL);

            if(err != CL_SUCCESS)
                throw clutil_exception(err, "clEnqueueUnMemObject");

            logger->write_info("### Unmap memory complete ###");
        } catch(std::runtime_error ex) {
            std::cout<< ex.what() <<std::endl;
        }

    }

    bool commandqueue::cl_enqueue_map_buffer()
    {
        logger->write_info("Start enqueue map buffer ");
        platdevices_info *platdevices =  get_platdevices_data();

        try {
            cl_int err = CL_SUCCESS;
            logger->write_info("Buffer input = ",lexical_cast<std::string>(platdevices->input_str.size()));
            logger->write_info("Mem copy check size : " , lexical_cast<std::string>((sizeof(cl_char) * platdevices->buffer_elements  * platdevices->num_devices)));
        
            logger->write_info("Queue size = ", lexical_cast<std::string>(platdevices->queues.back()));


            mapped_memory  =  clEnqueueMapBuffer(platdevices->queues.back(),
                    platdevices->mem_copy_buffers->back(),
                    CL_TRUE,
                    CL_MAP_READ,
                    0,
                    sizeof(cl_char) * platdevices->buffer_elements  * platdevices->num_devices,
                    0,
                    NULL,
                    NULL,
                    &err);

            if(err != CL_SUCCESS)
                throw clutil_exception(err, "clEnqueueMapBuffer");

            logger->write_info("### Map memory complete ###");

            char  mem_result[platdevices->buffer_elements];
            memcpy(mem_result, mapped_memory,  platdevices->buffer_elements);

        } catch(std::runtime_error ex) {
            logger->write_error(ex.what());
        }

    }

    bool commandqueue::cl_enqueue_copy_buffer()
    {
        logger->write_info("Start enqueue copy buffer ");
        cl_int err = CL_SUCCESS;
        platdevices_info *platdevices = get_platdevices_data();

        try {
            err = clEnqueueCopyBuffer(platdevices->queues.back(),
                    platdevices->mem_input_buffers->back(),
                    platdevices->mem_copy_buffers->back(),
                    0,
                    0,
                    sizeof(cl_char) * platdevices->buffer_elements * platdevices->num_devices,
                    0,
                    NULL,
                    NULL);

            if(err != CL_SUCCESS)
                throw clutil_exception(err, "clEnqueueCopyBuffer");

        } catch(std::runtime_error  ex) {
            logger->write_error(ex.what());
            return false;
        }

        return true;
    }

    bool commandqueue::cl_enqueue_task()
    {
        logger->write_info("Start cl_enqueue_task ... ");
        cl_int err = CL_SUCCESS;
        platdevices_info *platdevices = get_platdevices_data();

        try {
            err = clEnqueueTask(platdevices->queues.back(),
                    platdevices->kernels.back(),
                    0,
                    NULL,
                    NULL);

            if(err != CL_SUCCESS)
                throw clutil_exception(err,"clEnqueueTask");

        } catch(std::runtime_error ex) {
            logger->write_error(ex.what());
            return false;
        }

        return true;
    }

    bool commandqueue::cl_create_command_queue()
    {
        logger->write_info("### Start cl_create_command_queue");
        cl_int err = CL_SUCCESS;
        platdevices_info *platdevices = get_platdevices_data();

        try {

            for(unsigned int count_queue  = 0; count_queue < platdevices->num_devices; count_queue++) {

                InfoDevice<cl_device_type>::display(platdevices->device_ids[count_queue],
                        CL_DEVICE_TYPE,
                        "CL_DEVICE_TYPE");


                cl_command_queue command_queue = clCreateCommandQueue(platdevices->context,
                        platdevices->device_ids[count_queue],
                        0,
                        &err);

                if(err != CL_SUCCESS)
                    throw clutil_exception(err, "clCreateCommandQueue");

                logger->write_info("Address of command queue = " , lexical_cast<std::string>(command_queue));
                logger->write_info("Count_queue = ",lexical_cast<std::string>(count_queue));

                platdevices->queues.push_back(command_queue);

                cl_kernel  kernel = clCreateKernel(platdevices->program,
                        "square",
                        &err);

                if(err != CL_SUCCESS)
                    throw clutil_exception(err, "clCreateKernel");

                logger->write_info("--Create kernel success--");

                logger->write_info("--Address of mem_input_buffer = ",lexical_cast<std::string>(platdevices->mem_input_buffers->back())); 
                logger->write_info("--Address of mem_output_buffer = ",lexical_cast<std::string>(platdevices->mem_copy_buffers->back()));

                for(std::vector<cl_mem>::iterator iter = platdevices->mem_input_buffers->begin();
                        iter != platdevices->mem_input_buffers->end();
                        ++iter) {
                    err = clSetKernelArg(kernel,
                            0,
                            sizeof(cl_mem),
                            &(*iter));

                    if(err != CL_SUCCESS)
                        throw clutil_exception(err, "clCreateKernelArg");

		               logger->write_info( "--Input set completed " ); 
                }


                for(std::vector<cl_mem>::iterator iter = platdevices->mem_copy_buffers->begin();
                        iter != platdevices->mem_copy_buffers->end();
                        ++iter) {

                    err = clSetKernelArg(kernel,
                            1,
                            sizeof(cl_mem),
                            &(*iter));

                    if(err != CL_SUCCESS)
                        throw clutil_exception(err, "clCreateKernelArg");
										
									   logger->write_info("--Output set completed ");

                }


                err = clSetKernelArg(kernel,
                        2,
                        sizeof(cl_int),
                        &platdevices->buffer_elements);

                platdevices->kernels.push_back(kernel);

            }

        } catch(std::runtime_error  ex) {
            logger->write_info( ex.what() );
            return false;
        }

        return true;
    }
    bool commandqueue::cl_write_event()
    {
        logger->write_info( "### Start cl_write_event " );
        cl_int err = CL_SUCCESS;
        platdevices_info *platdevices = get_platdevices_data();

        try {

            if(platdevices->mem_input_buffers->size() == 0)
                return false;

            err =  clEnqueueWriteBuffer(
                    platdevices->queues[0],
                    platdevices->mem_input_buffers->back(),
                    CL_TRUE,
                    0,
                    sizeof(cl_char) * platdevices->buffer_elements * platdevices->num_devices,
                    (void *)platdevices->input_str.c_str(),
                    0,
                    NULL,
                    NULL);


            if(err != CL_SUCCESS)
                throw clutil_exception(err, "clEnqueueWriteBuffer");

        } catch(std::runtime_error ex) {
            logger->write_error(ex.what());
            return false;
        }

        return true;
    }

    bool commandqueue::cl_call_kernel()
    {
        logger->write_info("### Start cl_call_kernel ");
        cl_int err = CL_SUCCESS;
        platdevices_info *platdevices = get_platdevices_data();

        try {
            for(unsigned int count_queue = 0; count_queue < platdevices->queues.size(); count_queue++) {
                std::size_t  g_wi = platdevices->input_str.size();
                cl_event event;
                err = clEnqueueNDRangeKernel(platdevices->queues[count_queue],
                        platdevices->kernels[count_queue],
                        1,
                        NULL,
                        (const std::size_t *)&g_wi,
                        (const std::size_t *)NULL,
                        0,
                        0,
                        &event);

                if(err != CL_SUCCESS)
                    throw clutil_exception(err, "clEnqueueNDRageKernel");

                platdevices->events.push_back(event);
            }

            clWaitForEvents(platdevices->events.size(), const_cast<cl_event *>(&platdevices->events[0]));
        } catch(std::runtime_error  ex) {
            logger->write_error( ex.what() );
            return false;
        }

        return true;
    }

    bool commandqueue::cl_read_buffer()
    {
        logger->write_info("Start cl_read_buffer ");
        platdevices_info *platdevices = get_platdevices_data();
        clEnqueueReadBuffer(platdevices->queues[0],
                platdevices->mem_input_buffers->back(),
                CL_TRUE,
                0,
                sizeof(cl_char) * platdevices->buffer_elements * platdevices->num_devices,
                (void *)platdevices->input_str.c_str(),
                0,
                NULL,
                NULL);
        return true;
    }

    bool commandqueue::add_input_str(std::string input_str)
    {
        platdevices_info *platdevices = get_platdevices_data();

        if(input_str.size() == 0)
            return false;

        platdevices->input_str = input_str;
        return true;
    }

    class clutil_commandqueue : public base_clutil
    {
        public:
            clutil_commandqueue(std::size_t buffer_elements_) : commandqueue_util(new commandqueue(buffer_elements_)) { }
            bool cl_create_command_queue();
            bool cl_write_event();
            bool cl_call_kernel();
            bool cl_read_buffer();

            bool cl_enqueue_task();
            bool cl_enqueue_copy_buffer();
            bool cl_enqueue_map_buffer();

            bool cl_enqueue_unmap_buffer();

            bool add_input_str(std::string input_str);

            // Interface class
            std::vector<shared_ptr<platdevices_info> >&    get_platdevices_info_vec() {
                return  commandqueue_util->get_platdevices_info_vec();
            }
            void set_platdevices_info_vec(std::vector<shared_ptr<platdevices_info> >& ptr_info) {
                commandqueue_util->set_platdevices_info_vec(ptr_info);
            }

            platdevices_info *get_platdevices_data() {
                return commandqueue_util->get_platdevices_data();
            }

        private:
            commandqueue *commandqueue_util;
    };

    bool clutil_commandqueue::cl_create_command_queue()
    {
        return commandqueue_util->cl_create_command_queue();
    }

    bool clutil_commandqueue::cl_write_event()
    {
        return commandqueue_util->cl_write_event();
    }

    bool clutil_commandqueue::cl_call_kernel()
    {
        return commandqueue_util->cl_call_kernel();
    }

    bool clutil_commandqueue::cl_read_buffer()
    {
        return commandqueue_util->cl_read_buffer();
    }

    bool clutil_commandqueue::add_input_str(std::string input_str)
    {
        return commandqueue_util->add_input_str(input_str);
    }

    bool clutil_commandqueue::cl_enqueue_task()
    {
        return commandqueue_util->cl_enqueue_task();
    }

    bool clutil_commandqueue::cl_enqueue_copy_buffer()
    {
        return  commandqueue_util->cl_enqueue_copy_buffer();
    }

    bool clutil_commandqueue::cl_enqueue_map_buffer()
    {
        return commandqueue_util->cl_enqueue_map_buffer();
    }

    bool clutil_commandqueue::cl_enqueue_unmap_buffer()
    {
        return commandqueue_util->cl_enqueue_unmap_buffer();
    }


}



#endif /* CLUTIL_COMMANDQUEUE_HPP */
