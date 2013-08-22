#include <iostream>
#include <boost/type_traits.hpp>
#include <vector>

template <typename T>
class ctr{
	public:
		void addValue(const T& t)
		{
			values_.push_back(t);
		}
	void print()
	{
			typedef boost::integral_constant<bool, boost::is_pointer<T>::value> truth_type;
			
			for(unsigned int  i = 0; i < values_.size(); i++)
			{
						doPrint(values_[i], truth_type());	
			}
	}

	private:
		std::vector<T> values_;
		void doPrint(const T& t, const boost::false_type&)
		{
				std::cout<<" Not pointer . value : " << t <<std::endl;
		}
			
		void doPrint(const T& t, const boost::true_type&)
		{
				std::cout<< "Pointer. vaue : " << *t <<std::endl;
				//test pointer change value
				*t = 6;
		}
};

int main()
{

	ctr<int*> tr;
	int three = 3;
	int five  = 5;
	tr.addValue(&three);
	tr.addValue(&five);
	tr.print();
	tr.print();

	ctr<int> tronPtr;
	tronPtr.addValue(3);
	tronPtr.addValue(5);
	tronPtr.print();

	
}	
