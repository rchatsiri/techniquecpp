#ifndef  HNMAV_ALGORITHMS_TRIEAC_TRIE_HPP
#define  HNMAV_ALGORITHMS_TRIEAC_TRIE_HPP
/* 						Titles														Authors 												Date
 *  -Trie A-C               									Chatsiri.rat										initialization version of A-C
 *  -OpenCL util 															Chatsiri.rat											20/08/2012
 */
 
#include <iostream>
#include <list>
#include <stdexcept>
#include "buffer.hpp"
#include "CL/cl.h"
namespace hnmav_algorithms
{

    namespace trieac
    {

        class trienode;
        class triematch;
        class triedigit;
        class trievector;
        class trie;

        class trie_iterator;

        struct pattern {
            std::string    m_name;
            unsigned char   *m_pattern;
            size_t         m_len;
        };

        struct transition_map {
            unsigned  char c;
            trienode  *dest;
        };

        struct functor {
            virtual void operator()( const transition_map& t ) = 0;
        };

        enum node_type { match, vector, digit };

        class trienode
        {
            public:
                node_type get_type();

                virtual void set_fail(trienode *tnode);
                virtual trienode *get_fail();

                virtual void set_match(triematch *tmatch);
                virtual triematch *get_match();

                virtual trie_iterator *get_iterator() const = 0;
                virtual void iterate( functor& func) = 0;

                virtual trienode *advance(unsigned c) =0;
                virtual void set_transition(unsigned  c, trienode *target) {
                    (void)c;
                    (void)target;
                }

            protected:
                trienode(node_type t);
            private:
                node_type type;
                trienode  *fail;
                triematch *match_;
        };

        /* end trienode */

        class trie
        {
            private:
                trievector *root;
                trienode   *current;
                unsigned long int duplicates;
                void set_transition(trienode ***last_link, unsigned char c);
            public:
                trie();
                void test();
                //    ~trie();
                void add(const pattern  *sig);
                void reset();
                bool find(buffer *b, std::list<const pattern *> **patterns);
                //    void initialise();
                unsigned long get_duplicateds() const {
                    return duplicates;
                };
                trienode *find_fail(trienode  *parent, unsigned short symbol );
        };/* end of trie */


        class triematch : public trienode
        {
            public:
                triematch();
                virtual trienode *advance(unsigned c);
                virtual void      iterate(functor& func) {
                    (void)func; // not iterate
                }
                virtual trie_iterator *get_iterator()const;
                std::list<const pattern *> patterns;
        };/* end triematch */

        class trievector : public trienode
        {
            private:
            protected:
            public:
                trienode *vector_[256];
                trievector();

                virtual trienode *advance(unsigned c);
                virtual void      iterate(functor& f);
                virtual trie_iterator *get_iterator()const;

                virtual void set_transition(unsigned c, trienode *target);
        };/* end trie vector */


        class triedigit : public trienode
        {
            public:
                unsigned char digit_;
                trienode		  *dest;

                triedigit(unsigned char d);

                virtual trienode *advance(unsigned  c);
                virtual trie_iterator   *get_iterator() const;
                virtual void set_transition(unsigned char c, trienode *target);
                virtual void iterate(functor& f);

        };/* end of triedigit */




        /* ####################################   iterator package ################################## */

        /* look like trie iterator */
        class trie_iterator
        {
            public:
                /* interface class not define ctor */
                virtual void first() = 0;
                virtual void next()   = 0;
                virtual bool  is_done() const = 0;
                virtual transition_map& current() const =0;
        };

        class trie_nulliterator : public trie_iterator
        {
            public:
                trie_nulliterator( const trienode *tv) {
                    (void)tv;
                }
                virtual void first() { }
                virtual void  next() { }
                virtual bool  is_done() const {
                    return true;
                }
                virtual transition_map& current() const {
                    throw std::out_of_range(" Iterator out of range - Current not valid ");
                }

        };/*  end  trie_mull iterator */

        //   vector iterator is look like  root node ???
        class trie_vectoriterator : public trie_iterator
        {
            public:
                trie_vectoriterator(const trievector *tv);
                virtual void first();//{ }
                virtual void next();// { }
                virtual bool is_done() const;
                virtual transition_map& current() const;
            private:
                size_t   m_index;
                const trievector	*m_tvector;
                mutable transition_map  m_tmap;  // can access and cache value in const class or const member function.
         };/* end of trie_vectoriterator */

        class trie_digititerator : public trie_iterator
        {
            public:
                trie_digititerator(const triedigit *t_digit);
                virtual void  first();
                virtual void  next();
                virtual bool  is_done() const;
                virtual transition_map& current() const;
            private:
                int index;
                const triedigit  *m_tdigit;
                mutable transition_map   m_tmap;
        };/* end of trie_digitierator */

    }  /* end of trieac */

} /* end of hnmav_algorithms */

#endif /* HNMAV_ALGORITHMS_TRIE_HPP */


