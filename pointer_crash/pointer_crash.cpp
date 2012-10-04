#include <iostream>
#include <vector>

class pointer_crash 
{
public:
	 pointer_crash();
	 void insert_data();
	 void test_pointer();
private:
	std::vector<int> v_insert;
};

void pointer_crash::test_pointer()
{
  int value = 5;
	int *  pointer_addr = &value;
	std::cout<< "& value = " << &value <<", pointer_addr = "<<  pointer_addr <<", &pointer_addr = " <<&pointer_addr << ", *pointer_addr = " << *pointer_addr <<std::endl;
}

void pointer_crash::insert_data()
{
	int data_1 = 1;
  int data_2 = 2;
	int data_3 = 3;
	v_insert.push_back(data_1);
  v_insert.push_back(data_2);
	v_insert.push_back(data_3);

	int & type_insert2 = v_insert[2];
	std::cout<<" type_insert_2 = " << type_insert2 << " ,address = " << &type_insert2 <<std::endl;


	int * type_insert =  &v_insert[2];
  std::cout<<" type_insert = " << type_insert <<std::endl;


}

pointer_crash::pointer_crash()
{
	std::cout<<"test test"<<std::endl;
}

int main()
{
      pointer_crash p_crash;
			p_crash.insert_data();
			p_crash.test_pointer();
} 

	

