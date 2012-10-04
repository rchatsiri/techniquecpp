#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>
#include <vector>
#include <ext/malloc_allocator.h>


/*template<typename T>
	struct _Select1st
		{
				T value;
		};

template<typename T>
	struct _Select2st
		{
				T value;
		};
*/

template<typename T>
	class _Select1st
		{
				T value;
			public:
				 _Select1st(){};
		};

template<typename T>
	class _Select2st
		{
				T value;
			public:
				_Select2st(){};
		};


template<class  Value>
 struct Directory
	{
			typedef std::map< std::string, Value, std::less<std::string>, 	__gnu_cxx::malloc_allocator<std::string> > type;
			typedef _Select1st<typename type::value_type> KeySelector;
			typedef _Select2st<typename type::value_type> ValueSelector;
	};


int main(){
Directory<int>::type  row_data;
			
std::transform(row_data.begin(), row_data.end(), 
											std::ostream_iterator<std::string>(std::cout,"\n"),
											Directory<int>::KeySelector());
 
}
			 

	
