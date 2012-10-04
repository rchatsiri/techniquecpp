/* 						Titles														Authors 												Date
 * - Add command queue for write & get data from devices 
 *   																					 Chatsiri.rat										  09/09/2012
 */


#include "scanner.hpp"
#include "trie.hpp"

#include <vector>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/find_iterator.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>

#include <CL/cl.h>

#include "utils/clutil_platform.hpp"
#include "utils/clutil_memory.hpp"
#include "utils/base_clutil.hpp"
#include "utils/clutil_commandqueue.hpp"
#include "utils/config/options_system.hpp"
#include "utils/logger/clutil_logger.hpp"

#include "google/coredumper.h"

using namespace boost;

namespace hnmav_algorithms
{
		namespace util = hnmav_util;

    namespace  scan
    {

        scanner::scanner()
        {
            shortest_sig = UINT_MAX;
            longest_sig  = 0;
        }

        scanner::scanner(std::istream& in)
        {
            scanner();
            load_database(in);
        }

        void scanner::load_database(std::istream& in)
        {
					
            // test test platform_id
            std::size_t buffer_elements = 254 ;
            hnmav_util::clutil *util  = new hnmav_util::clutil_platform;
            hnmav_util::clutil_platform   *util_platform = static_cast<hnmav_util::clutil_platform *>(util);
            util_platform->get_info();
            util_platform->set_num_platforms_ids(0,NULL);

            util_platform->init_platforms_ids();

						util::options_system & op_system = util::options_system::get_instance();
						std::string opencl_file = op_system.get_openclfile_path();

						//init logger
						shared_ptr<util::clutil_logging<std::string, int> > * logger_ptr = &util::clutil_logging<std::string, int>::get_instance();
						util::clutil_logging<std::string, int> * logger = logger_ptr->get();
						std::string logger_main_file = op_system.get_logger_mainfile_path();
						std::string logger_settings  = op_system.get_logger_settingsfile_path();

						logger->add_logger(logger_main_file);
						logger->add_settings(logger_settings);
					  logger->init_backend();
						logger->formatter_normal();
						logger->init_frontend();

            if(util_platform->input_kernel_source(opencl_file)) {

                std::string platform_info = util_platform->get_platforms_info(CL_PLATFORM_VENDOR, "CL_PLATFORM_VENDOR");
                logger->write_info( "--- Platform info : ", platform_info );

                // get deivce ids
                util_platform->get_device_ids(CL_DEVICE_TYPE_ALL);

                util_platform->context_properties();
                util_platform->cl_create_context();
                util_platform->cl_create_programs_with_source();
                util_platform->cl_build_programs();
            }
				 
            std::string buffer;
            getline(in, buffer);

            try {
                while(in.fail() == false) {
                    // return position of =
                    std::string::size_type pos = buffer.find('=');
                    std::vector<std::string>  split_buffer;
                    // split  name and signagure
                    split(split_buffer, buffer, is_any_of("="), token_compress_on);

                    //   data size 2 include with viruies = signature file
                    if(split_buffer.size() > 2) {
                        throw std::out_of_range(" data cannot estimate ");
                    }

                    virus_name =  split_buffer.front();
                    signature_name = split_buffer.back();
									  logger->write_info("------------------------------------Virus Type ---------------------------------");
                    logger->write_info(" virus name : ", virus_name);
                    logger->write_info(" sig   name : ", signature_name);
										logger->write_info("--------------------------------------------------------------------------------");

									// memory management  class
            			hnmav_util::base_clutil   *base_memory_clutil = new  hnmav_util::clutil_memory;
            			base_memory_clutil->set_platdevices_info_vec(util->get_info());
            			hnmav_util::clutil_memory *memory_clutil = static_cast<hnmav_util::clutil_memory *>(base_memory_clutil);
            			memory_clutil->cl_create_buffer(signature_name);
								  // memory_clutil->cl_create_subbuffer();
					 				// command queue communication class 	
								  hnmav_util::base_clutil   *base_comqueue_clutil = new hnmav_util::clutil_commandqueue(buffer_elements);
									base_comqueue_clutil->set_platdevices_info_vec(util->get_info());
									hnmav_util::clutil_commandqueue *comqueue_clutil = static_cast<hnmav_util::clutil_commandqueue*>(base_comqueue_clutil);
	
				          comqueue_clutil->add_input_str(signature_name);
									comqueue_clutil->cl_create_command_queue();	
								  // comqueue_clutil->cl_write_event();

                  memory_clutil->cl_check_buffer_size();	

									comqueue_clutil->cl_call_kernel();
									// comqueue_clutil->cl_read_buffer();
									comqueue_clutil->cl_enqueue_task(); 
									comqueue_clutil->cl_enqueue_copy_buffer();
									comqueue_clutil->cl_enqueue_map_buffer();	
									comqueue_clutil->cl_enqueue_unmap_buffer();				  
 
                    add(virus_name, signature_name);
                    //                    print_boost(signature_name);
                    getline(in, buffer);
                }
            } catch(std::exception&  ex) {
                logger->write_error( ex.what() );
            }
        }


        void scanner::add(const std::string& name, const std::string& signature)
        {
            typedef tokenizer<offset_separator> assic_token;
            int offset[] = { 2 };
            offset_separator assic_offset(offset, offset+2);
            assic_token token(signature, assic_offset);

            ac::pattern  pat;
            pat.m_name = name;

            size_t pattern_lenght = signature.length() / 2;
            pat.m_pattern					= new unsigned char [ pattern_lenght ];
            pat.m_len							= 0;

            for(assic_token::iterator iter = token.begin(); iter != token.end(); iter++) {
                const char *char_assic = iter->c_str();
                pat.m_pattern[ pat.m_len ] = (unsigned char)strtoul(char_assic, NULL, 16);
                pat.m_len++;
            }

            m_patterns.push_back( pat );
            m_trie.add(&m_patterns.back());

        }

    } /* end of package scan */

} /* hnmav_algorithms scan */

