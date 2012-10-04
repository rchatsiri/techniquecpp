#include "list.hpp"

#include "StartConv.h"

int main()
{

    list<int>  order ;// = list<int>();

    for( int i = 0; i < 5 ; i++) {
        std::cout<< " the_list.insert ( " << i << " ) " << std::endl;
//        order.push_back(i);
					order.push_front(i);
    }

    print_collection(order);

}

#include "EndConv.h"
