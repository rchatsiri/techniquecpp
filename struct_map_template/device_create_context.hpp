#include <iostream>
#include <fstream>
#include <iterator>
#include <map>
template<typename T>
struct msg_info {
    int   id;
    int info;
    int    str;
    int        num_device;
    int  platform_ids;
};


template<typename key, typename T,typename Container = std::map<key,T> > 
class msg_display
{
public:
    msg_display();
		void map_info(T const& msgs, key keys);
		void contain_info();
private:
	  Container& msgdisplay_contains;
};

