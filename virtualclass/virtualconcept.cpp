#include <iostream>

using namespace std;
namespace concept{
template <typename T>
class A{
public:
    virtual void func1(const T& p)
    {
        cout<<"A:"<<p<<endl;
    }
};

template <typename T>
class B
: public A<T>
{
public:
    virtual void func1(const T& p)
    {
        cout<<"A<--B:"<<p<<endl;
    } 
};

}

int main(int argc, char** argv)
{
    concept::A<string> a;
    concept::B<int> b;
    concept::B<string> c;

    concept::A<string>* p = &a;
    p->func1("A<string> a");
    p = dynamic_cast<concept::A<string>*>(&c);
    p->func1("B<string> c");
    concept::B<int>* q = &b;
    q->func1(3);
}
