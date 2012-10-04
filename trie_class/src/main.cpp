/* 						Titles														Authors 												Date
 *	-Add options system													Chatsiri.rat										14/09/2012
 *
 */


#include "scanner.hpp"

#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <queue>
#include <cassert>
#include <ctime>
#include <cmath>
#include <iomanip>
#include "limits.h"
#include "utils/config/options_system.hpp"
#include <boost/algorithm/string.hpp>
#include <fstream>

namespace scan 	= hnmav_algorithms::scan;
namespace util 	= hnmav_util;
namespace po 		= boost::program_options;

struct session {
    scan::scanner  scanobj;
    long int  detections;
    long int 	infected_files;
    long int  file_fial2open;
    long int  file_scanned;
    bool		  show_filescanned;
    session() {
        detections = 0;
        infected_files = 0;
        file_fial2open =0;
        file_scanned = 0;
    }
    void load_database(std::istream& database_stream) {
        scanobj.load_database( database_stream );
    }
};


void check_file(session& sessions, std::string file_name)
{
    /*buffer buffers;
    unsigned char buffer[16384];
    buffers.data = buffer;

    if(session.show_filescanned == true)
    	cout<< "Checking... " << file_name <<std::endl;

    std::fstream(file_name.c_str(), std::ios_base::in | std::ios_base::binary);
    */

}
#include <cstring>
int main(int ac, char *av[])
{

    util::options_system& op_system = util::options_system::get_instance();
    op_system.generic_options();
    op_system.configure_options();
    op_system.process_options(ac, av);

    if(!op_system.default_condition()) 
        return 0;

    std::ifstream signature_stream;
    std::string db_path = op_system.get_database_path();
    signature_stream.open(db_path.c_str(), std::ifstream::in);


    if(!signature_stream.is_open())
        throw  std::runtime_error("Cannot open file > "+op_system.get_database_path());

    session  sess;
    sess.load_database( signature_stream );
    signature_stream.close();

    std::cout<<" Close file success " <<std::endl;

}

