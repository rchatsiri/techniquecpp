#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

using boost::lexical_cast;
using boost::bad_lexical_cast;

class typecasting_test
{
    public:
        typecasting_test(std::string str): str_(str) { };
        void casting2float();
				void casting2short();
				void casting2int();
    private:
        std::string str_;

};

void typecasting_test::casting2float()
{
    try {
        float data_f = lexical_cast<float>(str_);
        std::cout<<"String to float = " << data_f <<std::endl;

    } catch(bad_lexical_cast&) {
        std::cout<< "cannot cast " <<std::endl;
    }

}


void typecasting_test::casting2short()
{
    try {
        short data_f = lexical_cast<short>(str_.c_str());
        std::cout<<"String to short  = " << data_f <<std::endl;

    } catch(bad_lexical_cast&) {
        std::cout<< "cannot cast " <<std::endl;
    }

}

void typecasting_test::casting2int()
{
    try {

//				for(std::size_t i = 0; i <  str_.size(); i++)
//				{
					  int  data_f = lexical_cast<int>("123A");
        		std::cout<<"String to short  = " << data_f; // <<std::endl;
						
//				}
      
    } catch(bad_lexical_cast&) {
        std::cout<< "cannot cast " <<std::endl;
    }

}





