/*  Get device info */

#include <iostream>
#include <map>
#include "device_create_context.hpp"

template<typename T>
struct msg_info;




template<typename key, typename T,typename Container> 
msg_display<key,T,Container>::msg_display()
{

}


//------------------------------------Device context info---------------------------------------
template<typename key, typename T,typename Container> 
void msg_display<key,T,Container>::contain_info()

{
   // return Container;
}


template<typename key, typename T,typename Container> 
void msg_display<key, T,  Container>::map_info(T const& msgs,key keys)
{
    msgdisplay_contains[keys] = { msgs.id, msgs.info, msgs.str, msgs.num_device,  msgs.platform_ids};
}








int main()
{
         msg_display<int, msg_info<int>, std::map<int, msg_info<int> > > msgdis();
}



