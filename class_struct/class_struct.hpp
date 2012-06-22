#include <iostream>
#include <string>
#include <map>
namespace class_struct
{

template<typename T>
class iMainClass
{
protected:
    typedef struct {
        T  str_data;
        int value_data;
    } stmsg;
		std::map<int, stmsg> stmsg_map;
public:
    iMainClass();
    ~iMainClass();
    void   set_stmsg(T const& str);
//		std::map<int, stmsg>& get_stmsg_map();
//  	stmsg& get_stmsg_map();
private:
    std::string value_str;
};

}
