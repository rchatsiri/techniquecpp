#include<iostream>

class BaseType{

public:
//	BaseType();
	virtual int get_data() = 0;
	virtual void set_data(int data) = 0;
//	virtual ~BaseType();
};



class ChildTypeB: public BaseType{
public:
  ChildTypeB(){ };
	~ChildTypeB(){ };
	int get_data() { return data; } 
  void set_data(int datas) { data = datas; }
  void get_base_type(BaseType *  baseType) {  std::cout<< "Get data in B = " <<  baseType->get_data() <<std::endl; }
private:
	int data;
};

class ChildTypeA: public BaseType{
public:
	ChildTypeA() : BaseType(){ };
	~ChildTypeA(){ };
	int get_data() { return data; }
  void set_data(int datas) { data = datas; }
  void get_base_type(BaseType *  baseType) { 

   std::cout<< "Get data in A = " <<  baseType->get_data() <<std::endl; }

  void get_base_cast(){
   	BaseType *  castBase = static_cast<BaseType*>(this);
    std::cout<< "Cast base data after set in TypeB = " << castBase->get_data()<<std::endl; 
		ChildTypeB * childB =  static_cast<ChildTypeB*>(castBase);
		std::cout<< "Cast to ChildB and get_data = " << childB->get_data() <<std::endl;
	}  

	void setTypeA(BaseType *  baseType){
		ChildTypeB * typeB = static_cast<ChildTypeB*>(baseType);
		std::cout<<" in ChildTypeA cast to get ChildTypeB data = " << typeB->get_data()<<std::endl; 
	  }
private:
	int data;
	ChildTypeA * typeA;
};

int main()
{
		ChildTypeB * typeB = new ChildTypeB;
		typeB->set_data(32);

		ChildTypeA * typeA = new ChildTypeA;
//    typeA->get_base_cast();
		typeA->set_data(11);
    typeA->get_base_cast();

		std::cout<< "-------------------BastType interface-------"<<std::endl;
		BaseType *  baseTypeA = new ChildTypeA;
    baseTypeA->set_data(1);
	  ChildTypeB * childB = static_cast<ChildTypeB*>(baseTypeA);
		std::cout<< " get ChildB get data = " << childB->get_data() <<std::endl;
		std::cout<< " get data chileTypeA = " << baseTypeA->get_data() <<std::endl;	
		std::cout<< "--------------------------------------------"<<std::endl;
 
    std::cout<< "---------------Cast from typeB to Bast-------"<<std::endl;	   
		BaseType * base = static_cast<BaseType*>(typeB); 
    std::cout<< " typeB default set_data = 32 " <<std::endl;	
		std::cout<< " Get data from typeB cast to Base = " << base->get_data() <<std::endl;
	  std::cout<< "---------------------------------------------"<<std::endl;
	
    std::cout<< " Set data in base 12  "<<std::endl;
	  base->set_data(12);
   	std::cout<< " Get data from typeB again  set_data member function ast to Base = " << base->get_data() <<std::endl;
    std::cout<< " Get from typeB = " << typeB->get_data() <<std::endl;

    std::cout<< "----------------------------------------------"<<std::endl;		
		std::cout<< " ChildTypeA get data = " <<  typeA->get_data() <<std::endl;
		std::cout<< " ChildTypeB get data = " <<  typeB->get_data() <<std::endl;	
	  std::cout<< "----------------------------------------------"<<std::endl;		
	
		typeA->get_base_type(base);
//	  base = static_cast<BaseType*>(typeA);
	  typeA->setTypeA(base);

    typeB->get_base_type(base);

}; 
