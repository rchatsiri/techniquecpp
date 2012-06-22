/* Prove concepts of protected type of class */

#include <iostream>

namespace virtual_encap
{

template<typename T, typename OBJECT_CONTROL = virtual_encap::object_control<T1> >
class vir_encap
{
public:
    vir_encap(T& obj_one) : object_control(obj_one) {};
    virtual process_controller(object_control&  objcontrol)=0;
    virtual object_control& get_objcontrol()=0;
protected:
    object_control_one& process_control_one();
private:
    OBJECT_CONTROL * object_control_;
};

template<typename T, typename OBJECT_CONTROL = virtual_encap::object_control<T1> >
class vir_inheritance : protected vir_encap
{
public:
    vir_inheritance(T& objT1) : vir_encap(objT1) {}
    virtual process_controller(object_control<T>& objcontrol){
		//	message_object msgobj = objectcontrol::	
		}

		virtual object_control& get_objcontrol(){
			return  object_control;
		} 
private:
    OBJECT_CONTROL * object_control_;		
};

template<typname T>
class object
{
public:
    object();
    virtual object&  control()=0;
    virtual void set_control(object_const& objcol)=0;
private:
    object<T> *objcol = NULL;
};

template<typename T>
class object_control public object
{
public:
    object_control(std::string name_object);
    virtual object_control& control_object() {
        return this;
    }
    virtual void set_object_control(object_const& objcol) {
        this.obj_one = objcol;
    }

private:
    message_object msg_obj;
    object_one<T> * obj_one = NULL;

};

typedef struct {
    std::string name_object;
    std::string behavoir;
} message_object;

}
