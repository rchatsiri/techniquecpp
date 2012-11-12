#include <iostream>
#include <tire.hpp>

#include <iostream>
#include <stdexcept>
#include <vector>
 
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <config/options_system.hpp> 


namespace po = boost::program_options;
 
template<typename ReturnType, typename T1, typename T2>
class Dispatcher
{
  public:
    struct UnhandledDispatch : std::runtime_error
    {
      UnhandledDispatch()
        : std::runtime_error("Uknown dispatch for given arguments")
      {
      }
    };
 
    template<typename I1, typename I2>
    void addHandler(const boost::function<ReturnType (const I1 &, const I2 &)> &h)
    {
      myHandlers.push_back(boost::shared_ptr<Handler>(new HandlerImpl<I1, I2>(h)));
    }
 
    template<typename I1, typename I2>
    void addHandler(ReturnType (*fp)(const I1&, const I2&))
    {
      myHandlers.push_back(
          boost::shared_ptr<Handler>(
            new HandlerImpl<I1, I2>(boost::function<ReturnType (const I1 &, const I2 &)>(fp))));
    }
 
 
 
    ReturnType operator()(const T1 &t1, const T2 &t2)
    {
      for (typename std::vector<boost::shared_ptr<Handler> >::iterator itr = myHandlers.begin();
          itr != myHandlers.end();
          ++itr)
      {
        try {
          return (*itr)->go(t1, t2);
        } catch (std::bad_cast &) {
          //The current function did not match!
          //keep truckin and try the next one
        }
      }
 
      throw UnhandledDispatch();
    }
 
  private:
    struct Handler
    {
      virtual ReturnType go(const T1 &, const T2 &) = 0;
    };
 
    template<typename I1, typename I2>
      struct HandlerImpl : Handler
    {
      HandlerImpl(const boost::function<ReturnType (I1, I2)> &f)
        : myFunction(f)
      {
      }
 
      virtual ReturnType go(const T1 &t1, const T2 &t2)
      {
        // this only succeeds if the dynamic_cast succeeds. Otherwise bad_cast is thrown
        // and caught by Dispatcher::operator()
        return myFunction(dynamic_cast<const I1 &>(t1), dynamic_cast<const I2 &>(t2));
      }
 
      private:
        boost::function<ReturnType (I1, I2)> myFunction;
    };
 
    std::vector<boost::shared_ptr<Handler> > myHandlers;
};
 
// Everything above this line is implementation details, everything below is what the user
// of the dispatcher needs to know.
 
struct Thing {
  virtual ~Thing()
  {
  }
};
 
struct Rock : Thing {};
struct Paper : Thing {};
struct Scissors : Thing {};
 
 
bool defeats(const Thing &, const Thing &) { return false; }
bool defeats(const Paper &, const Rock &) { return true; }
bool defeats(const Rock &, const Scissors &) { return true; }
bool defeats(const Scissors &, const Paper &) { return true; }


int main(int ac, char* av[])
{

/*  Dispatcher<bool, Thing, Thing> myDispatcher; // the dispatcher returns a bool and takes two "Thing" classes
  myDispatcher.addHandler<Paper, Rock>(&defeats); //Add paper, rock version
  myDispatcher.addHandler<Rock, Scissors>(&defeats); // add rock, scissors version
  myDispatcher.addHandler<Scissors, Paper>(&defeats); // add scissors, paper version
  myDispatcher.addHandler<Thing, Thing>(&defeats); // add generic version
 
  Paper paper;
  Rock rock;
 
  Thing &thing1(paper);
  Thing &thing2(rock);
 
  std::cout << std::boolalpha;
  std::cout << myDispatcher(thing1, thing2) << std::endl; // decide (at runtime) which version to call
  std::cout << myDispatcher(rock, paper) << std::endl;
*/

//foo();

util::options_system & op_system = util::options_system::get_instance();
//						std::string opencl_file = op_system.get_openclfile_path();

op_system.generic_options();
op_system.configure_options();
op_system.process_options(ac, av);

if(!op_system.default_condition())
{
	std::cout<<"Default error " <<std::endl;
	return 0;
}
tire<std::string, char> tire_node;

std::string str_test = "ABCD";
tire_node.add_node(str_test);

//std::string str_test2 = "GAB";
//tire_node.add_node(str_test2);

std::string str_test3 = "ABEF";
tire_node.add_node(str_test3);



//std::string str_test4 = "ABG";
//tire_node.add_node(str_test4);

//std::string str_test5 = "BGG";
//tire_node.add_node(str_test5);

//std::string str_test6 = "BGC";
//tire_node.add_node(str_test6);

std::string str_test7 = "ABEG";
tire_node.add_node(str_test7);

}

