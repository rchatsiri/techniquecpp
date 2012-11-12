#include <iostream>
#include <string>
void test() {
//    int n;
    for( int i = 0; i < 100; i++ ) {
       int  n = i + 2;
        std::cout << "Address of n is: " << &n << std::endl;
    }
}

int main()
{

	test();
	return 0;
}

