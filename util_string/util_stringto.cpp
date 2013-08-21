#include <iostream>
#include <sstream>
#include <numeric>
#include <cassert>
#include <string>
#include <stdexcept>

namespace utility
{

namespace internal
{
		template<typename dest_type>
		dest_type & string_to(std::string const & s, dest_type & result)
		{
				std::stringstream stream(s);
			  stream>>result;
				if((!stream)||(stream.fail())){
				throw std::invalid_argument("Error converting string \""+std::string(s)+"\"");
				}
				return result;
		}
}

}

int main()
{

	std::string value = "16";
	int a;
	int value_re = utility::internal::string_to<int>(value,a);
	std::cout<<"Result from a : "<< value_re <<std::endl;
}
