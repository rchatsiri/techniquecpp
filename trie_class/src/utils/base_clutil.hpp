#ifndef HNMAV_INTERFACE_CLUTIL_HPP
#define HNMAV_INTERFACE_CLUTIL_HPP
/* 						Titles														Authors 												Date
 * -interface combine with  platdevices_info( contrain cl infomation )
 *   																						Chatsiri.rat										27/08/2012
 * -Add sturct to implement on interface class  Chatsiri.rat										27/08/2012
 * - Change interface to base prefix name				Chatsiri.rat	                  28/08/2012
 * -Add share_ptr_info base class 							Chatsiri.rat	                  30/08/2012
 * -Add Buffer elements													Chatsiri.rat										14/09/2012
 */

#include "CL/cl.h"
#include <vector>
#include <iostream>
#include <boost/shared_ptr.hpp>

#define BUFFER_SIZE 256;

namespace hnmav_util
{

    using namespace boost;

    struct platdevices_info {

        // platform info
        cl_platform_id  *platform_ids;
        cl_device_id    *device_ids;
        cl_context_properties *properties;

        cl_context      context;

        cl_context_properties *proper[3];

        std::vector<cl_context_properties>  context_vec;

        cl_uint  				num_platforms;
        cl_uint					num_devices;
        cl_program 			program;

        // memory info
			  std::vector<cl_mem> *  mem_input_buffers;
			  std::vector<cl_mem> *	 mem_copy_buffers;

				std::vector<cl_command_queue> queues;
				std::vector<cl_kernel> kernels;
				std::vector<cl_event>  events;
				//input to stream data 
				std::string            input_str;
				std::string 					 output_str;
				// buffer global size
				unsigned int										 ibuffer;
				int										 buffer_elements;
    };


    class base_clutil
    {
        public:
						/* using shared_ptr_info connect to another classes */
            virtual std::vector<shared_ptr<platdevices_info> > &   get_platdevices_info_vec() = 0;
						virtual void set_platdevices_info_vec(std::vector<shared_ptr<platdevices_info> > & ptr_info) = 0;
            virtual platdevices_info * get_platdevices_data() = 0;
    };

		class clutil : public  base_clutil
		{
				public:
			      // interface member function
					std::vector<shared_ptr<platdevices_info> > &  get_platdevices_info_vec()
						{
	            if( platform_vec.size() == 0)
							 {
                platform_ptr  info_ptr(new platdevices_info);
                platform_vec.push_back(info_ptr);
						  	std::cout<<"### Shared_ptr Init paltdevices_info  = "<< platform_vec.size() << std::endl;
							 }	
							return  platform_vec;
            }

						// using pass by references to set data in shared_ptr_info 
					  void set_platdevices_info_vec(std::vector<shared_ptr<platdevices_info> >   & ptr_info)
						{
							  if(platform_vec.back() != NULL)
								{
										 platform_vec.pop_back(); 
										 platform_vec.push_back(ptr_info.back());
								}
								
								return platform_vec.push_back(ptr_info.back()); 
						}

					  platdevices_info * get_platdevices_data(){
        			shared_ptr<platdevices_info>   plat_shared_ptr =  platform_vec.back();
        			platdevices_info *platdevices =  plat_shared_ptr.get();
							return platdevices;
						}


					  virtual std::vector<shared_ptr<platdevices_info> > &  get_info() = 0;
	
        private:

           typedef	shared_ptr<platdevices_info>       platform_ptr;
           std::vector<shared_ptr<platdevices_info> >  platform_vec;
		};
				   	
}

#endif /*HNMAV_INTERFACE_CLUTIL_HPP */
