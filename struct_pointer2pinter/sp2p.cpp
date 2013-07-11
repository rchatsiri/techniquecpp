#include<iostream>
#include<string>

struct data_a{
	int * pattern;
};

class read_struct
{
public:
	read_struct();
	int operate_struct();
	~read_struct();
private:
struct data_a ** data_ppa;
struct data_a  * data_pa;
};

read_struct::~read_struct()
{
	 data_a ** pa = data_ppa;
	 data_a *  p  = *pa;
	 delete p;
	 //delete data_pa;
}

read_struct::read_struct()
{
	 data_pa = new data_a();
	 data_pa->pattern = new int;
	*data_pa->pattern = 16;

	 data_ppa = &data_pa;	 
}

int read_struct::operate_struct()
{
   data_a ** pa = data_ppa;
	 data_a * ppa = *pa;
	 std::cout<<" Int value : "<< *ppa->pattern <<std::endl;
	 return 0;
}

int main()
{
	read_struct rstr;
	rstr.operate_struct();

}
