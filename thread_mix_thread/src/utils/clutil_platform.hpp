#ifndef HNMAV_UTIL_CLUTIL_HPP
#define HNMAV_UTIL_CLUTIL_HPP

/* 						Titles														Authors 												Date
 * -Initial utility infomation									Chatsiri.rat										19/08/2012
 * -Add for info device, exception 							Chatsiri.rat										20/08/2012
 * -Add boost::share_ptr for handling malloc memory
 *  																						Chatsiri.rat									  25/08/2012
 * -Base_cltuil new cl_info object							Chatsiri.rat	                  01/09/2012
 */

#include "CL/cl.h"
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

#include "google/coredumper.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <alloca.h>
#include <malloc.h>
#include <cstdlib>

#include "utils/base_clutil.hpp"
#include "utils/clutil_exception.hpp"


#define DEFAULT_PLATFORM 0
#define DEFAULT_USE_MAP  false
#define NUM_BUFFER_ELEMENTS 16
#define SIZE_PROPERTIES 2;

namespace hnmav_util
{

    /* initial Real class */
    class platform : public clutil
    {
        public:
            platform(): platform_id(DEFAULT_PLATFORM), use_map(DEFAULT_USE_MAP) {
            }

            void set_num_platforms_ids(cl_uint number_entries,
                    cl_platform_id *platforms);

            bool init_platforms_ids();

            bool input_kernel_source(std::string str);

            std::string&   get_source();

            std::size_t get_source_size();

            std::string get_platforms_info(cl_platform_info name, std::string str);

            cl_device_id  get_device_ids(cl_device_type device_type);

            cl_platform_id get_platform_ids();

            void  context_properties();

            void cl_create_context();

            void cl_create_programs_with_source();

            void cl_build_programs();

            ~platform();

            std::vector<shared_ptr<platdevices_info> >&    get_info() {
                return get_platdevices_info_vec();
            }

        private:

            std::ifstream    *input_file_stream;
            std::string      *src_prog;
            std::string      *info;
            std::string      src;

            int platform_id;
            bool use_map;

    };


    class clutil_platform : public clutil
    {
        public:
            clutil_platform(): platform_id(DEFAULT_PLATFORM), use_map(DEFAULT_USE_MAP)
                , platform_util(new platform()) {

            }

            void set_num_platforms_ids(cl_uint number_entries,
                    cl_platform_id *platforms);

            bool init_platforms_ids();

            bool input_kernel_source(std::string str);

            std::string&   get_source();

            std::size_t get_source_size();

            std::string get_platforms_info(cl_platform_info name, std::string str);

            cl_device_id  get_device_ids(cl_device_type device_type);

            cl_platform_id get_platform_ids();

            void  context_properties();

            void cl_create_context();

            void cl_create_programs_with_source();

            void cl_build_programs();

            ~clutil_platform();

            std::vector<shared_ptr<platdevices_info> >&   get_info() {
                return platform_util->get_info();
            }

        private:

            int platform_id;
            bool use_map;
            platform *platform_util;

    };

    /* clutil_platform declear */
    void clutil_platform::set_num_platforms_ids(cl_uint number_entries,
            cl_platform_id *platforms)
    {

        platform_util->set_num_platforms_ids(number_entries, platforms);
    }


    bool  clutil_platform::init_platforms_ids()
    {
        return platform_util->init_platforms_ids();
    }

    bool clutil_platform::input_kernel_source(std::string str)
    {
        return platform_util->input_kernel_source(str);
    }

    std::string&   clutil_platform::get_source()
    {
        return platform_util->get_source();
    }

    std::size_t clutil_platform::get_source_size()
    {
        return platform_util->get_source_size();
    }

    std::string clutil_platform::get_platforms_info(cl_platform_info name, std::string str)
    {
        return platform_util->get_platforms_info(name, str);
    }

    cl_device_id  clutil_platform::get_device_ids(cl_device_type device_type)
    {
        return platform_util->get_device_ids(device_type);
    }

    cl_platform_id  clutil_platform::get_platform_ids()
    {
        return platform_util->get_platform_ids();
    }

    void  clutil_platform::context_properties()
    {
        platform_util->context_properties();
    }

    void clutil_platform::cl_create_context()
    {
        platform_util->cl_create_context();
    }

    void clutil_platform::cl_create_programs_with_source()
    {
        platform_util->cl_create_programs_with_source();
    }


    void clutil_platform::cl_build_programs()
    {
        platform_util->cl_build_programs();
    }

    clutil_platform::~clutil_platform()
    {
    }



    /* platform declare */
    platform::~platform()
    {
        std::cout<< "clutil_platform delete object " <<std::endl;
    }

    cl_platform_id	platform::get_platform_ids()
    {
        return NULL;
    }

    void platform::cl_build_programs()
    {
        std::vector<shared_ptr<platdevices_info> >  plat_vec = get_platdevices_info_vec();
        shared_ptr<platdevices_info>  info_shared_ptr  =  plat_vec.back();
        platdevices_info   *devices = info_shared_ptr.get();

        std::cout << "Program = " <<  devices->program << ", num_devices = " << devices->num_devices <<std::endl;

        try {
            cl_int err = clBuildProgram(devices->program,
                    devices->num_devices,
                    devices->device_ids,
                    "-I.",
                    NULL,
                    NULL);

            if(err != CL_SUCCESS)
                throw clutil_exception(err, "clBuildProgram");

        } catch(std::runtime_error e) {
            char build_log[16389];
            clGetProgramBuildInfo(devices->program,
                    devices->device_ids[0],
                    CL_PROGRAM_BUILD_LOG,
                    sizeof(build_log),
                    build_log,
                    NULL);

            std::cout<< e.what() <<std::endl;
            std::cerr<< "Build log = "<< build_log << std::endl;

        }

        std::cout<< "Num_devices = " << devices->num_devices <<std::endl;
    }

    void  platform::cl_create_programs_with_source()
    {
        std::vector<shared_ptr<platdevices_info> >  plat_vec = get_platdevices_info_vec();
        shared_ptr<platdevices_info>  info_shared_ptr  =  plat_vec.back();
        platdevices_info   *devices = info_shared_ptr.get();


        //        platdevices_info devices  =  get_info();

        try {
            cl_int err = CL_SUCCESS;
            std::string source = get_source();
            const char  *str = source.c_str();
            std::size_t  length = source.length();
            devices->program = clCreateProgramWithSource(devices->context, 1, &str, &length , &err);

            if(err != CL_SUCCESS)
                throw clutil_exception(err, "clCreateProgramWithSource");

            std::cout<< "Start address program = " << devices->program <<", source = " << source  <<std::endl;
        } catch(std::runtime_error e) {
            std::cout << e.what() <<std::endl;
        }
    }

    void  platform::cl_create_context()
    {
        std::cout<<"Start  cl_create_contxt " <<std::endl;
        std::vector<shared_ptr<platdevices_info> >  plat_vec = get_platdevices_info_vec();
        shared_ptr<platdevices_info>  info_shared_ptr  =  plat_vec.back();
        platdevices_info   *devices = info_shared_ptr.get();


        //        platdevices_info devices =  get_info();
        cl_context_properties   cl_properties[devices->context_vec.size()];

        for(int count = 0; count < devices->context_vec.size(); count++)
            cl_properties[count] = devices->context_vec[count];

        try {
            cl_int err = CL_SUCCESS;

            //get data from properties
            for(int count = 0; count < devices->context_vec.size(); count++) {
                std::cout<< "Devices ["<<count<<"] = " <<cl_properties[count] <<std::endl;
            }

            devices->context =  clCreateContext(cl_properties,
                    devices->num_devices,
                    devices->device_ids,
                    NULL,
                    NULL,
                    &err );

            if(err != CL_SUCCESS)
                throw clutil_exception(err, "clCreateContext");

        } catch(std::runtime_error e) {
            std::cout<< e.what() <<std::endl;
        }

    }
    void platform::set_num_platforms_ids(cl_uint number_entries,
            cl_platform_id *platforms)
    {
        try {
            std::cout<< " Start in num_platforms_ids " <<std::endl;

            std::vector<shared_ptr<platdevices_info> >  plat_vec = get_platdevices_info_vec();
            shared_ptr<platdevices_info>  info_shared_ptr  =  plat_vec.back();
            platdevices_info   *platdevices = info_shared_ptr.get();

            cl_int err = clGetPlatformIDs(0, NULL, &platdevices->num_platforms);

            if((err != CL_SUCCESS)  ? err : (platdevices->num_platforms <= 0 ? -1 : CL_SUCCESS)) {
                throw	clutil_exception(err,"Device Info");
            }


        } catch(std::runtime_error  e) {
            std::cout<< "Error : " << e.what() <<std::endl;
            exit(EXIT_FAILURE);
        }

    }
    bool platform::input_kernel_source(std::string str)
    {
        try {
            input_file_stream  = new std::ifstream(str.c_str());

            if(input_file_stream->is_open()) {
                src_prog = new std::string(std::istreambuf_iterator<char>(*input_file_stream),
                        std::istreambuf_iterator<char>());
                return true;
            }

            std::string error_msg_file = "Reading source : ";
            throw clutil_exception(-1,  error_msg_file.append(str) );

        } catch(std::runtime_error e) {
            std::cout<< e.what() << std::endl;
            return false;
        }

    }

    std::string& platform::get_source()
    {
        return  *src_prog;
    }

    std::size_t platform::get_source_size()
    {
        return src_prog->length();
    }

    std::string platform::get_platforms_info(cl_platform_info  name, std::string str)
    {
        std::cout<< " Start get_platforms_info " <<std::endl;
        std::size_t param_value_size;
        std::string info_str;

        try {
            std::vector<shared_ptr<platdevices_info> >  plat_vec = get_platdevices_info_vec();
            shared_ptr<platdevices_info>  info_shared_ptr  =  plat_vec.back();
            platdevices_info   *platforms = info_shared_ptr.get();


            //            platdevices_info  platforms =  get_info();

            cl_int err = clGetPlatformInfo(platforms->platform_ids[platform_id],
                    name,
                    0,
                    NULL,
                    &param_value_size);

            if(err != CL_SUCCESS)
                throw clutil_exception(err,"Fail to fine OpenCL Platform stage 1");

            char *info = (char *)alloca(sizeof(char) * param_value_size);
            err = clGetPlatformInfo(*platforms->platform_ids, name, param_value_size, info, NULL);

            if(err != CL_SUCCESS)
                throw clutil_exception(err,"Fail to fine OpenCL Platform stage 2");

            info_str = std::string(info);

        } catch(std::runtime_error e) {
            std::cout<< e.what() <<std::endl;
            exit(EXIT_FAILURE);

        }

        return info_str;
    }


    cl_device_id  platform::get_device_ids(cl_device_type device_type)
    {
        std::cout<< "Start get_devices_ids " <<std::endl;
        std::vector<shared_ptr<platdevices_info> >  plat_vec = get_platdevices_info_vec();
        shared_ptr<platdevices_info>  info_shared_ptr  =  plat_vec.back();
        platdevices_info   *devices = info_shared_ptr.get();

        // platdevices_info   devices = get_info();

        try {

            cl_int err = clGetDeviceIDs(devices->platform_ids[platform_id],
                    device_type,
                    0,
                    NULL,
                    &devices->num_devices);

            devices->device_ids =  (cl_device_id *)malloc(sizeof(cl_device_id) * devices->num_devices );

            err = clGetDeviceIDs(devices->platform_ids[platform_id],
                    device_type,
                    devices->num_devices,
                    &devices->device_ids[0],
                    NULL);
            std::cout<<std::endl;
            std::cout<< "----------------------------------Num Devices-------------------------------------------" <<std::endl;
            std::cout<< "Address num_devices = " << &devices->num_devices << ", device_type " << device_type <<std::endl;
            std::cout<< "Value num_devices = " << devices->num_devices <<std::endl;


            std::cout<< "----------------------------------------------------------------------------------------" <<std::endl;
            std::cout<<std::endl;

            if(err != CL_SUCCESS)
                throw   clutil_exception(err, "clGetDeviceIDs");

        } catch(std::runtime_error e) {
            std::cout<< e.what() <<std::endl;
            exit(EXIT_FAILURE);
        }

        return *devices->device_ids;

    }

    bool platform::init_platforms_ids()
    {
        std::cout<< "-- Init init_platforms_ids " <<std::endl;

        try {
            std::vector<shared_ptr<platdevices_info> >  plat_vec = get_platdevices_info_vec();
            shared_ptr<platdevices_info>  info_shared_ptr  =  plat_vec.back();
            platdevices_info   *platforms = info_shared_ptr.get();

            platforms->platform_ids = (cl_platform_id *)malloc(sizeof(cl_platform_id) * platforms->num_platforms );
            cl_int err = clGetPlatformIDs(platforms->num_platforms, platforms->platform_ids, NULL);

            if(err != CL_SUCCESS) {
                throw clutil_exception(err, "clGetPlatformIDs");
            }

            std::cout<< " Num_platfrom = " << platforms->num_platforms <<std::endl;
            return true;
        } catch(std::runtime_error e) {
            std::cout << e.what() <<std::endl;
            exit(EXIT_FAILURE);
        }
    }

    void platform::context_properties()
    {
        std::cout<< "Start context_properties " <<std::endl;
        std::vector<shared_ptr<platdevices_info> >  plat_vec = get_platdevices_info_vec();
        shared_ptr<platdevices_info>  info_shared_ptr  =  plat_vec.back();
        platdevices_info   *platforms = info_shared_ptr.get();

        std::cout<< " CL_CONTEXT_PLATFORM = " << CL_CONTEXT_PLATFORM <<", Properties = " <<  (cl_context_properties)platforms->platform_ids[platform_id] << std::endl;
        cl_context_properties context_pro[] = { CL_CONTEXT_PLATFORM,
                (cl_context_properties)platforms->platform_ids[platform_id],
                0
                                              };
        platforms->properties = context_pro;
        platforms->context_vec.push_back(CL_CONTEXT_PLATFORM);
        platforms->context_vec.push_back((cl_context_properties)platforms->platform_ids[platform_id]);
        platforms->context_vec.push_back(0);
        std::cout<<"Start address properties = " << platforms->properties <<std::endl;
    };

}
#endif /* HNMAV_UTIL_CLUTIL_HPP  */

