#include<iostream>
	class testpassby_ref
	{
		public:
			testpassby_ref(std::string const& value)
			{
						str_ptr = &value;
			}
			std::string& get_str(){
				return str_ptr;
			}
		private:
			std::string const str_ptr;
};

int main()
{
		std::string value_ref = "test value ref";
		testpassby_ref t_ref(value_ref);
}
