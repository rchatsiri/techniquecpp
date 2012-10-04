#include<iostream>


class trienode
{
public:
    virtual std::string* get_value() = 0;
    virtual void processs() = 0;
    virtual void set_value(std::string*) = 0;
protected:
    trienode(std::string value = "test") : value_(value) { }
private:
    std::string value_;
};

class trievector : public trienode
{
private:
    std::string * value;
public:
    trievector(std::string);
    std::string * get_value();
    void 					process();
    void					set_value(std::string* value);
};

trievector::trievector(std::string vector = "vector") : trienode(vector) 
{

}

std::string* trievector::get_value()
{
    return  value;
}

void trievector::process()
{
    std::string changevalue = "change value in process";
    value = &changevalue;

}

void trievector::set_value(std::string* _value)
{
		std::cout<<" prepairing set value ... " <<std::endl;
    value = _value;
}

/* end of trievector */

class trie
{
   private:
			trievector *root;
	 public:
			trie();
			void initial();
};

trie::trie()
{
	std::cout<<" gen class trie " <<std::endl;
}

void trie::initial()
{
		trievector *n = root;
    std::cout<< "---------------------------" <<std::endl;
		std::cout<< "  trievector *n = root " <<std::endl;
		std::cout<< "value of root = " << root <<",  address of &root = " << &root <<std::endl;
		std::cout<< "Address of &n = " << &n << ",  value  to root (n) =  " << n  <<std::endl; 
		std::cout<< "----------------------------" <<std::endl;
    trievector **last_link = &n;
    std::cout<< "**last_link = &n" <<std::endl;
		std::cout<< "value of last_link =  " << last_link << ", address of last_link = " << &last_link << std::endl; " , value of *last_link = ";// << *last_link  <<std::endl;
    // interface class 
//		std::string xvalue = "value n";
//    trievector tvector(xvalue);
//		trienode* tnode = dynamic_cast<trienode*>(n);
		
//		trienode * tnode = n;
//		  std::string str_ = "value";
//      tnode->set_value(&str_); 
}



int main()
{
	 trie t;
	 t.initial();

	  std::cout<< "----------------------------------------------test address-------------------------------------" <<std::endl;
    /* test pointer */
		char a = '1';
		char *b = &a;
		std::cout<< " value of a = " << a <<std::endl;
    std::cout<< "  value of *b = " << *b << ", address of b = "<< &b << ", address of a = " << b <<std::endl;

}
