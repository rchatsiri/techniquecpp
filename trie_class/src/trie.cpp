/* 						Titles														Authors 												Date
 * -trieac                    									Chatsiri.rat										 - 
 *
 *
 */



#include "trie.hpp"

namespace hnmav_algorithms
{

    namespace trieac
    {
			
				// trie vector iterator 

        trie_vectoriterator::trie_vectoriterator(const trievector  *tv)
        {
            m_tvector = tv;
            first();
        }

        void trie_vectoriterator::first()
        {
            m_index = 0;
        }

        void trie_vectoriterator::next()
        {
            if(!is_done()) {
                m_index++;
            }
        }

        bool trie_vectoriterator::is_done()const
        {
            if(m_index < 256)
                return false;
            else
                return true;
        }
        // set current position
        transition_map& trie_vectoriterator::current() const
        {
            if(!is_done()) {
                m_tmap.c = (unsigned char)m_index;
                m_tmap.dest = m_tvector->vector_[m_index];
                return m_tmap;
            } else {
                throw std::out_of_range("Iterator out of range - Current not valid");
            }
        }

        /* end of trie_vectoriterator */

        // trie digit iterator 
        trie_digititerator::trie_digititerator(const triedigit  *t_digit)
        {

            index = 0;
            m_tdigit  = t_digit;

        }

        void trie_digititerator::first()
        {
            index = 0;
        }

        void trie_digititerator::next()
        {
            if(!is_done())
                index++;
        }

        bool trie_digititerator::is_done() const
        {

            if( index == 0 )
                return false;
            else
                return true;
        }

        transition_map&  trie_digititerator::current() const
        {
            if( !is_done() ) {
                m_tmap.c 		=  (unsigned char)m_tdigit->digit_;
                m_tmap.dest =  m_tdigit->dest;
                return m_tmap;
            } else {
                throw std::out_of_range("Iterator out of range - trie_digititerator");
            }
        }


        trienode::trienode(node_type t)
        {
            type = t;
            match_ = NULL;
            set_fail(NULL);
        }

        node_type trienode::get_type()
        {
            return type;
        }

        void trienode::set_fail(trienode *tnode)
        {
            fail = tnode;
        }

        trienode  *trienode::get_fail()
        {
            return fail;
        }

        void  trienode::set_match(triematch *tmatch)
        {
            match_ = tmatch;
        }

        triematch *trienode::get_match()
        {
            return match_;
        }
				
				/* end of trienode */


        // trie 
        void trie::set_transition(trienode ***last_link, unsigned char c)
        {
            trievector   *vector;
            triematch    *match;
            triedigit    *digit;

            if(**last_link == 0) {
                triedigit *d = new triedigit(c);
                **last_link = d;
                *last_link = &d->dest;
            }

        }

        trie::trie() : current(0), duplicates(0)
        {
            root = new trievector;
        }

        void trie::test()
        {
            std::cout<<" test in trie " <<std::endl;
        }

        void trie::add(const pattern *pat)
        {
            size_t i = 0;
            trienode   *n = root;
            trienode **last_link = &n;
            unsigned char c;

            while( i < pat->m_len) {
                c = pat->m_pattern[i];
                set_transition(&last_link, c);
                i++;
            }
        } 


         /* end of trie */
		
				//   trie match 
        triematch::triematch() : trienode(match)
        {
            set_match(this);
        }

        trienode *triematch::advance(unsigned c)
        {
            static_cast<void>(c);
            return NULL;
        }

        trie_iterator *triematch::get_iterator()const
        {
            return new trie_nulliterator(this);
        }
   
    		/* end of triematch */

				//  trie vector
        trievector::trievector() : trienode(vector)
        {
            for(int i = 0; i < 256; ++i)
                vector_[i] = NULL;
        }

        // send c character to trienode
        trienode *trievector::advance(unsigned c)
        {
            return vector_[c];
        }

        void trievector::iterate(functor& f)
        {

            int i;

            for( i = 0; i < 256; ++i) {
                transition_map m = { (unsigned char)i, vector_[i] };
                f(m);
            }

        }

        void trievector::set_transition(unsigned c, trienode *target)
        {
            vector_[c] = target;
        }

        trie_iterator *trievector::get_iterator()const
        {
            return new trie_vectoriterator(this);
        }


				/* end of trievector */


        triedigit::triedigit(unsigned char d) : trienode(digit)
        {
            digit_ = d;
            dest  = NULL;
        }


        trienode *triedigit::advance(unsigned c)
        {
            return c == digit ? dest : NULL;
        }

        trie_iterator *triedigit::get_iterator()const
        {
            return new trie_digititerator(this);
        }

        void triedigit::set_transition(unsigned char  c, trienode *target)
        {
            digit_ = c;
            std::cout<< " triedigit " <<std::endl;
            dest  = target;
        }

        void triedigit::iterate( functor&  f)
        {
            transition_map m  = {digit, dest};
            f(m);
        }


				/* end of triedigit */


    } /* end of trieac */

}/* end of hnmav_algorithms  */
