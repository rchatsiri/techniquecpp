#include "control_thread.hpp"

void workruntest()
{
worker_run_test wruntest;
wruntest.work_date_time();

}

int main()
{


//boost::thread workthread(workruntest);
//std::cout<<"Wait for thread..." <<std::endl;
//workthread.join();


// detach 
thread_edit_doc threadedit;
threadedit.edit_document("data.doc");

}
