#include<iostream>

template<typename T>
 struct str_msg{
				static	T  msg;
				};

template<typename T>
T str_msg<T>::msg;

template<typename T>
	class base_struct_class
	{
			public:
				base_struct_class(): str_(NULL){};
				base_struct_class(T const& _str) : str_(_str){ }
			  str_msg<T>  get_str_msg();	
				str_msg<T>& get_str_msg_pointer();	
			private:
				T const& str_;
		//		str_msg<T> strmsg;
	};

template<typename T>
	str_msg<T>&  base_struct_class<T>::get_str_msg_pointer()
	{
			  str_msg<T> strmsg;
			 	strmsg.msg = str_;
				std::cout<< " address of strmsg_pointer : " << &strmsg << " , data pointer : "<< strmsg.msg <<std::endl;
		return strmsg;
	}

template<typename T>
	str_msg<T>::msg&  base_struct_class<T>::get_str_msg_pointer()
	{
				//str_msg<T> strmsg;
			 //	strmsg.msg = str_;
			//	std::cout<< " address of strmsg_pointer : " << &strmsg << " , data pointer : "<< strmsg.msg <<std::endl;
			 str_msg<T>::msg = str_;	
		//	return strmsg;
				return str_msg<T>::msg;
	}

template<typename T>
	str_msg<T> 	base_struct_class<T>::get_str_msg()
		{
				
		   	str_msg<T> strmsg;
				strmsg.msg = str_;
				std::cout<<" struct member msg : "<< strmsg.msg <<", address : " << &strmsg   <<std::endl;
			return strmsg;
		}

main(){
		std::string name_data = "data";
		base_struct_class<std::string>  bstclass(name_data); 

		str_msg<std::string>  strmsg = bstclass.get_str_msg();
   	std::cout<< " strmsg : " << &strmsg  << " data : " <<  strmsg.msg <<  std::endl;
		
//    str_msg<std::string> & strmsg_pointer = bstclass.get_str_msg_pointer();
		
 //   std::cout<< " strmsg_pointer : " <<  strmsg_pointer <<std::endl; 
//		std::cout<< " value of reference   : "<<  &(strmsg_pointer) <<std::endl;
//  str_msg<std::string>  msgs = bstclass.get_str_msg();
//  std::cout<< " msgs->msg : " << bstclass.get_str_msg().msg <<std::endl;
		
	}
