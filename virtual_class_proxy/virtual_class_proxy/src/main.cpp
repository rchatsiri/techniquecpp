/*            Titles                            Authors                         Date
 *- Add proxy concept 												Chatsiri.rat										  05/09/2012
 *
 */             
 
#include "data_a_util.hpp"
#include "data_b_util.hpp"
#include "shared_util.hpp"

#include "student_read_connect.hpp"

int main()
{
//	 proxy_a proxy;// = new proxy_a();
	 base_util * util = new proxy_a;
   std::cout<< "Get data = " <<  util->get_data() <<std::endl; 
//    using  share_ptr_info  concept
/*   std::vector<shared_ptr_info<data_struct> >  data_vec = util->get_ptr_info(); 
	 shared_ptr_info<data_struct>  data_shared_ptr = data_vec.back();

	 shared_ptr<data_struct> *  struct_shared_ptr = data_shared_ptr.get_info();
   data_struct *  dstruct = struct_shared_ptr->get(); 
	 std::cout<<"Get data in shared_ptr success = " << dstruct->data_vec.back() <<std::endl;*/

	std::vector<shared_ptr<data_struct> > vec  = util->get_ptr_info();
	shared_ptr<data_struct>  data_shared_ptr = vec.back();
	data_struct * dstr = data_shared_ptr.get();
  std::cout<<"Get data in shared_ptr success = " << dstr->data_vec.back() <<std::endl;

/*	util = new proxy_b;
	std::cout<< "Get data = " << util->get_data() <<std::endl;

  std::vector<shared_ptr<data_struct> > vec_b = util->get_ptr_info();  
  shared_ptr<data_struct>  data_shared_ptr_b = vec_b.back();
	data_struct * dstr_b = data_shared_ptr_b.get();
  std::cout<<"Get data in shared_ptr success = " << dstr_b->data_vec.back() <<std::endl;
*/

    iconnect_util * icutil = new student_read_connect;
  // address in proxy-b
    util->ptr_info(*icutil);
		student_read_connect * src = static_cast<student_read_connect*>(icutil);
	  src->view_data_str();	
}





