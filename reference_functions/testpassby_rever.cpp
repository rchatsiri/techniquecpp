#include<iostream>
	class testpassby_ref
	{
		public:
			testpassby_ref(const std::string & value)
			{
						str_ptr = &value;
					  std::cout<<" Str Ptr : " << *str_ptr <<std::endl;
			}

			std::string const & get_str(){
				return *str_ptr;
			}
			
			void setPtr(const std::string * value)
			{
					str_ptr = value;
					std::cout<<" Str with pointer : " << *str_ptr <<std::endl;
			}
		
		private:
			const std::string * str_ptr;
};

int main()
{
		std::string value_ref = "test value ref";
		testpassby_ref t_ref(value_ref);
		std::cout<<" Print in : "<< t_ref.get_str() <<std::endl;
		t_ref.setPtr(&value_ref);

		//Pointer
	  std::string * value_ref_Ptr = &value_ref;
		t_ref.setPtr(value_ref_Ptr);
}
