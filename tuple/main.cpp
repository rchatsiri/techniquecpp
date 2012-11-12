#include <boost/tuple/tuple.hpp> 
#include <boost/tuple/tuple_io.hpp> 
#include <string> 
#include <iostream> 

void make_pair()
{
  std::string s = "Boris"; 
  std::cout << boost::make_tuple(boost::ref(s), "Schaeling", 43) << std::endl; 
}

int main() 
{ 
  typedef boost::tuple<std::string, std::string, int> person; 
  person p("Boris", "Schaeling", 43); 
  std::cout << p << std::endl; 

	make_pair();
	
} 
