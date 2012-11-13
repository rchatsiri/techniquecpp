/*                       Titles                                          Authors                        Date
 *Create DFS and TypeTireries                                            Chatsiri.rat                   06/10/2012
 *Separate trie class and dfs																		         Chatsiri.rat
*/

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>

#include "gtest/gtest.h"

#include <iostream>
#include <string>
#include <list>
#include <deque>

#include <logger/clutil_logger.hpp>
#include <config/options_system.hpp>

using namespace boost;

namespace util = hnmav_util;

template<typename TypeTire, typename TypeNode>
struct node_tire {
    // data in node
    TypeNode const *data;

    int addr_node;

    // address insert next  node
    std::vector<node_tire<TypeTire, TypeNode> > addr_next_node;

    node_tire() : data(NULL) { }
};


template<typename TypeTire, typename TypeNode>
class tire
{
    public:
        tire( );
        node_tire<TypeTire, TypeNode> *check_root_node(node_tire<TypeTire, TypeNode>&   node);
        bool add_node(TypeTire const& data);
        node_tire<TypeTire, TypeNode> *recursive_node(node_tire<TypeTire, TypeNode>& node_branch, node_tire<TypeTire, TypeNode>& node_data);

    private:

        node_tire<TypeTire, TypeNode>   *node_data;

        // Root node of tire
        std::vector<node_tire<TypeTire, TypeNode>* >  node_root_vec;
        std::deque<node_tire<TypeTire, TypeNode> >    deque_node;

        // Handling node
        std::vector<shared_ptr<node_tire<TypeTire, TypeNode> > > node_root_shared_ptr;
        typedef shared_ptr<node_tire<TypeTire, TypeNode> >       node_ptr;

        // Handleing logger
        shared_ptr<util::clutil_logging<std::string, int> > *logger_ptr;
        util::clutil_logging<std::string, int> *logger;

};

template<typename TypeTire, typename TypeNode>
tire<TypeTire, TypeNode>::tire()
{

    util::options_system& op_system = util::options_system::get_instance();

    //init logger
    logger_ptr = &util::clutil_logging<std::string, int>::get_instance();
    logger = logger_ptr->get();
    std::string logger_main_file = op_system.get_logger_mainfile_path();
    std::string logger_settings  = op_system.get_logger_settingsfile_path();

    logger->add_logger(logger_main_file);
    logger->add_settings(logger_settings);
    logger->init_backend();
    logger->formatter_normal();
    logger->init_frontend();

}

// Finding data in root node before travelling in branch.
template<typename TypeTire, typename TypeNode>
node_tire<TypeTire, TypeNode> *tire<TypeTire, TypeNode>::check_root_node(node_tire<TypeTire, TypeNode>& node)
{
    int index_root_node = 0;
    node_tire<TypeTire, TypeNode> *root_vertex = NULL;

    // start node with null
    if( node_root_vec.size() == 0)
        return root_vertex;

    for(typename std::vector<node_tire<TypeTire, TypeNode>* >::iterator iter_root = node_root_vec.begin();
            iter_root != node_root_vec.end();
            ++iter_root, ++index_root_node) {

        node_tire<TypeTire, TypeNode>   *node_in_vec = *iter_root;

        TypeNode const *data = node_in_vec->data;

        if( *data == *node.data) {
            root_vertex = node_root_vec.at(index_root_node);
        }
    }

    return root_vertex;
}

template<typename TypeTire, typename TypeNode>
bool tire<TypeTire, TypeNode>::add_node(TypeTire const& input_data)
{
    node_data  = new node_tire<TypeTire, TypeNode>();
    node_tire<TypeTire, TypeNode> *vertex_root = NULL;
    node_tire<TypeTire, TypeNode> *node_temp = NULL;

    const char *input_str = input_data.c_str();

    while(*input_str != '\0') {

        if(node_data->data == NULL) {
            node_data->data = &(*input_str);

            vertex_root = check_root_node(*node_data);

            if(vertex_root == NULL) {
                node_root_vec.push_back(node_data);

                logger->write_info("Create root element ", node_data->data);
            } else {
                node_temp = node_data;

                logger->write_info("Create temp element ", node_data->data);
            }

            input_str = input_str + 1;
            continue;
        }

        // Child node creates in addr_next_node
        node_tire<TypeTire, TypeNode> *child_node = new node_tire<TypeTire, TypeNode>();
        child_node->data = &(*input_str);

        logger->write_info("@@@ Create Child node ", child_node->data);

        node_data->addr_next_node.push_back(*child_node);
        // next node
        node_data = &node_data->addr_next_node.back();

        input_str = input_str + 1;
    }

    if(vertex_root  != NULL) {
        // Next from root vertex
        vertex_root = recursive_node(*vertex_root, *node_temp);
    }

    return true;
}

template<typename TypeTire, typename TypeNode>
node_tire<TypeTire, TypeNode> *tire<TypeTire, TypeNode>::recursive_node(node_tire<TypeTire, TypeNode>& vertex_root, node_tire<TypeTire, TypeNode>& node_data)
{
    logger->write_info("### ---- Start recursive ---- ###");
    logger->write_info("---- Start recursive node with Vertex input ", vertex_root.data);
    logger->write_info("---- Start recursive node with Data input ", node_data.data);

    node_tire<TypeTire, TypeNode> temp_vertex_root = vertex_root;
    node_tire<TypeTire, TypeNode> *vertex_branch  = &vertex_root;
    node_ptr vertex_ptr(vertex_branch);


    while(vertex_branch->data != NULL) {

        // Vertex
        if( *(vertex_branch->data) == *(node_data.data)) {

            deque_node.push_back(*vertex_branch);

            // compare in branch of vertex
            for(typename std::vector<node_tire<TypeTire, TypeNode> >::iterator iter_node = vertex_branch->addr_next_node.begin();
                    iter_node != vertex_branch->addr_next_node.end();
                    ++iter_node ) {

                node_tire<TypeTire, TypeNode>& node_branch = *iter_node;
                node_data = node_data.addr_next_node.back();

                logger->write_info("### Node Branch Data ", node_branch.data);
                logger->write_info("### Node Data ", node_data.data);

                if(*(node_branch.data) == *(node_data.data)) {
            				deque_node.push_back(node_branch); 
                    logger->write_info("--- Node Branch Data ", node_branch.data);
                    logger->write_info("--- Node Data ", node_data.data);
                }
								else
								{
									  if(node_branch.addr_next_node.size() != 0)
										{
												
										}
								}

            }

        } else {

            if(vertex_branch->addr_next_node.size() != 0 )
                break;

            // Next vertex root
            std::vector<node_tire<TypeTire, TypeNode> >  node_vec = vertex_branch->addr_next_node;
            vertex_branch = &node_vec.back();
            // Next temp check
            node_data = node_data.addr_next_node.back();

        }
    }

    if(deque_node.size() != 0) {


        node_tire<TypeTire, TypeNode> node_last = deque_node.back();

        node_last.addr_next_node.push_back(node_data);

        logger->write_info("*** Node last contain data ", node_last.data);
        logger->write_info("*** Node last contain data in size ", std::to_string(node_last.addr_next_node.size()));
        logger->write_info("*** Node data add to tail ", node_data.data);

    }

    vertex_root = temp_vertex_root;
    logger->write_info("###----End of recursive add node----### ");

}
