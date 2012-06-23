#include<iostream>

template<typename T>
	class rlvalue_move{
		public:
				rlvalue_move(T const& value);
				void lvalue_copy(T const& lvalue);
		private:
				T lvalue_;
};

template<typename T>
	rlvalue_move<T>::rlvalue_move(T const& value)
	{
			
	}
template<typename T>
	void rlvalue_move<T>::lvalue_copy(T const& lvalue)
	{
			std::cout<<" * value : " << &lvalue <<std::endl;
 	}

int main(){
		std::string str = "data";
    rlvalue_move<std::string>  rl(str);
		std::cout<<" Before send &str : "<<&str<<std::endl;
		rl.lvalue_copy(str);
}


