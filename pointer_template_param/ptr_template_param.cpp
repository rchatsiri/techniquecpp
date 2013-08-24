#include <iostream>

template<typename T>
class PtrParam
{
	public:
			void test(){  std::cout<<"Print ptrParam not pointer" <<std::endl; }
};

template<typename T>
class PtrParam<T*>
{
	public:
			void test(){ std::cout<<"Print ptrParam as pointer" <<std::endl; }
};


int main()
{
		PtrParam<int*> ptrparam;
		ptrparam.test();
		PtrParam<int>  notPtr;
		notPtr.test();
}
