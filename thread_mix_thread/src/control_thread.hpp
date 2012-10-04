#ifndef CONTROL_THREAD_HPP
#define CONTROL_THREAD_HPP

#include <iostream>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include <boost/bind.hpp>

#include <functional>
#include <thread>
#include <string>

using namespace boost;

class worker_run_test
{
	public:
		void work_date_time()
		{
		  	boost::posix_time::seconds work_time(3);
				std::cout<< "Thread 	worker running " <<std::endl;
				boost::this_thread::sleep(work_time);
				std::cout<< "Work finished " <<std::endl;	
		}
};


enum command_type{ open_new_document };


struct user_command
	{
 		command_type type;
		user_command(): type(open_new_document){}
	};

class thread_edit_doc
{
public:
		void open_document_and_display_gui(std::string const& filename){ }
		bool done_editing(){ return true; }
		user_command get_user_input()
		{
			return user_command();
		}		
		std::string get_file_name_from_user()
		{
			return "foo.doc";
		}
		void process_user_input(user_command const& cmd)
		{
		}
    void edit_document(std::string const&  filename)
		{
				open_document_and_display_gui(filename);
				while(!done_editing())
				{
					user_command cmd = get_user_input();
					if(cmd.type == open_new_document)
					{
						std::string const   new_name = get_file_name_from_user();
						thread t(edit_document,new_name);
	//						std::thread t(bind(&edit_document,&new_name));
					t.detach();
					}
					else
					{
						process_user_input(cmd);
					}
				}
		}
private:

};

#endif /* CONTROL_THREAD_HPP */
