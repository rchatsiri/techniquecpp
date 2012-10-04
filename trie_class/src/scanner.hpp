#ifndef HNMAV_ALGORITHMS_SCANNER_HPP
#define HNMAV_ALGORITHMS_SCANNER_HPP

#include <iostream>
#include <list>

#include "trie.hpp"
#include "buffer.hpp"

#include "limits.h"
#include "stdlib.h"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/find_iterator.hpp>

namespace ac = hnmav_algorithms::trieac;

namespace hnmav_algorithms
{
    namespace scan
    {

        class scanner
        {
            private:
                std::list<ac::pattern> m_patterns;
                size_t 			  shortest_sig;
                size_t				longest_sig;
                ac::trie m_trie;
                void add(const std::string& name, const std::string& signature);
                std::string   virus_name;
                std::string   signature_name;
            public:
                scanner();
                scanner(std::istream& in);
                //    ~scanner();
                void load_database(std::istream& in);
        };


    } /* end of scan */

} /* end of hnmav_algorithms */

#endif  /*  HNMAV_ALGORITHMS_TRIEAC_SCANNER_HPP */

