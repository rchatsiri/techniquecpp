#include<iostream>

int main()
{

		std::string data =  std::string("data");
		std::cout<< " size of data = " << data.size() <<std::endl;
	  std::cout<<  " char size of data = " << sizeof(char) * data.size() <<std::endl;
		std::cout<< "Floating size " << 30 * sizeof(float) <<std::endl;
		const char * data_char = "data_in_char"; // data.c_str();
		std::cout<< data_char <<std::endl;
}
