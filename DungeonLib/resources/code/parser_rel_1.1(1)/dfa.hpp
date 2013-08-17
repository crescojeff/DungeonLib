// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// dfa template class
// The type Dfa (Deterministic Finite Automition) is the same as the Nfa
// except there are no Null transitions, and a state (node) can have
// only one edge for a given transition symbol to another state.

#ifndef DFA_HPP
#define DFA_HPP

#include "all.hpp"
#include <set>
#include <map>
#include <stack>
#include "nfa.hpp"

// template parameters:
// T is the transition class type.
// all classes assume that T() will generate a Null transition
//
// E is the container type used to hold edges
//
// N is the container type used to hold nodes
//
// class I is the input class type
// an input type must have at least the following defined:
// SavedPosType                                 -- type used to save the input's current position
// NodeInfoType                                 -- extra information stored in a node
// bool match(trans_type& trans)                -- match (and consume) the given input
// void savePos(SavedPosType& pos)              -- saves current input position
// void RestorePos(SavedPosType& pos)           -- restores current input position
// void callback(Nfa& nfa, NodeInfoType& info)  -- called when a node is transition to.

namespace DFA {

using NFA::Edge;
using NFA::Node;

#if CAN_HANDLE_PARTIAL_TEMPLATE_SPECIALIZATION_FOR_CONSTANTS
template<class T, class I, template<class> class E = std::vector, template<class> class N = std::vector>
#else
template<class T, class I, class E = std::vector<Edge<T> >, class N = std::vector<Node<T, I, E> > >
#endif
class Dfa : public NFA::Nfa<T, I, E, N>
{
public:
    typedef NFA::Nfa<T, I, E, N> Nfa;

    Dfa() {}
    explicit Dfa(const Nfa& nfa) {nfa_to_dfa(nfa);}

private:
    // types used to convert an Nfa to a Dfa
    typedef std::set<int> NodeSet;
    typedef std::stack<int> NodeStack;
    typedef std::map<NodeSet, bool> MetaSet;
    typedef std::pair<NodeSet, T> NodeMapElement;
    typedef std::map<NodeMapElement, NodeSet> NodeMap;
    typedef std::map<NodeSet, int> NodePtrMap;
    typedef std::set<T> Alphabet;

    // function object used to push nodes onto a stack
    struct push_node {
        NodeStack& s;
        push_node(NodeStack& pS) : s(pS) {}
        void operator()(int n) {s.push(n);}
    };

    // function object used to locate an unmarked state in a meta-set
    struct is_not_marked {
        bool operator()(const MetaSet::value_type& e) {return !e.second;}
    };

    // function object used to add a node u to a set t and a stack s
    // if an edge e is a Null transition to u, and u is not already in t
    struct add_llamda_trans {
        NodeSet& t;
        NodeStack& s;
        add_llamda_trans(NodeSet& pT, NodeStack& pS) : t(pT), s(pS) {}
        void operator()(const typename Nfa::edge_type& e)
        {
            if (e.trans == T() && t.find(e.node) == t.end())
            {
                t.insert(e.node);
                s.push(e.node);
            }
        }
    };

    // function object used to find a set within a meta-set
    struct NodeSet_eq {
        const NodeSet& t;
        NodeSet_eq(const NodeSet& pT) : t(pT) {}
        bool operator()(const MetaSet::value_type& e)
        {return e.first == t;}
    };

    // function object to check all to edges in a node for a transition symbol
    // t.  for every node to which there is an edge with t, add the node to set T.
    struct check_edges {
        NodeSet& nset;
        const T& t;
        const Nfa& nfa;
        check_edges(const Nfa& pNFA, NodeSet& pT, const T& pt) : nset(pT), t(pt), nfa(pNFA) {}
        void operator()(int n)
        {
          for_each(nfa.nodes[n].edges.begin(), nfa.nodes[n].edges.end(), add_trans(nset, t));
        }

        // function object to add a node n to a set T if the given edge makes a
        // transition t to n.
        struct add_trans {
          NodeSet& nset;
          const T& t;
          add_trans(NodeSet& pT, const T& pt) : nset(pT), t(pt) {}
          void operator()(const typename Nfa::edge_type& e)
          {
              if (e.trans == t)
                  nset.insert(e.node);
          }
        };
    };

    // function object to add NodeSets to a NodeMap and a MetaSet under certain conditions
    struct add_to_map {
        NodeMap& nmap;
        MetaSet& mset;
        const NodeSet& nset;
        const Nfa& nfa;
        add_to_map(const Nfa& pNFA, NodeMap& pM, MetaSet& pE, const NodeSet& pT) :
            nmap(pM), mset(pE), nset(pT), nfa(pNFA) {}
        void operator()(const T& t)
        {
            NodeSet t1, u;

            move(nfa, nset, t, t1);
            closure(nfa, t1, u);

            if (!u.empty())
            {
                // if u is not in mset, add it as an unmarked state
                if (find_if(mset.begin(), mset.end(), NodeSet_eq(u)) == mset.end())
                    mset[u] = false;
                nmap[NodeMapElement(nset, t)] = u;
            }
        }

        // This functions returns the set of NFA states (nodes) to which there is
        // a transition on the given input symbol from some state in the set T.
        static void move(const Nfa& nfa, const NodeSet& s_in, const T& t, NodeSet& s_out)
        {
            for_each(s_in.begin(), s_in.end(), check_edges(nfa, s_out, t));
        }
    };

    friend struct add_to_map;

    // function object to create a DFA node from a MetaSetElement, and save its
    // address in a map
    struct make_dfa_node {
        NodePtrMap& p;
        const Nfa& nfa;
        const NodeSet& i;
        Dfa& dfa;

        make_dfa_node(NodePtrMap& pP, const Nfa& pNFA, const NodeSet& pI, Dfa& pDFA) :
        p(pP), nfa(pNFA), i(pI), dfa(pDFA) {}
        void operator()(const MetaSet::value_type& e)
        {
            const int n = dfa.nodes.size();
            dfa << node_type();
            const NodeSet& t = e.first;

            p[t] = n;

            const bool initial = t == i;    // true if t is the initial state of dfa

            // check if t is a final node.  it is if it contains a final node of the nfa
            dfa.nodes[n].final = find_if(t.begin(), t.end(), is_final(nfa)) != t.end();

            if (initial)
                dfa.initial = n;
        }

        // function object to return true if node is a final node
        struct is_final {
          const Nfa& nfa;
          is_final(const Nfa& pNFA) : nfa(pNFA) {}
          bool operator()(int n) {return nfa.nodes[n].final;}
        };
    };

    // function object to add edges to the DFA based on the node map
    struct add_edges {
        NodePtrMap& p;
        Dfa& dfa;

        add_edges(Dfa& pDFA, NodePtrMap& pP) : p(pP), dfa(pDFA) {}
        void operator()(const typename NodeMap::value_type& e)
        {
            // function makes an edge from s to u, on t
            const NodeSet& s = e.first.first;
            const NodeSet& u = e.second;
            const typename Dfa<T, I, E, N>::trans_type& t = e.first.second;

            NodePtrMap::iterator ps = p.find(s);
            NodePtrMap::iterator pu = p.find(u);
            const int ns = ps->second;
            const int nu = pu->second;

            dfa.nodes[ns] << edge_type(t, nu);
        }
    };

    void nfa_to_dfa(const Nfa& nfa);
    static void build_alphabet(const Nfa& nfa, Alphabet& alpha);
    static void closure(const Nfa& nfa, const NodeSet& s_in, NodeSet& s_out);
    void create_dfa(const NodeMap& nmap, const MetaSet& mset, const Nfa& nfa, const NodeSet& nset);
};

// creates a set of the given NFA's alphabet (the set of all transitions
// used in the NFA
template<class T, class I, TEMPLATE_PARAM(E), TEMPLATE_PARAM(N) >
void Dfa<T, I, E, N>::build_alphabet(const Nfa& nfa, Alphabet& alpha)
{
    for (typename nodes_type::const_iterator n = nfa.nodes.begin(); n != nfa.nodes.end(); ++n)
        for (typename edges_type::const_iterator e = n->edges.begin(); e != n->edges.end(); ++e)
            if (e->trans != T())
                alpha.insert(e->trans);
}

template<class T, class I, TEMPLATE_PARAM(E), TEMPLATE_PARAM(N) >
void Dfa<T, I, E, N>::nfa_to_dfa(const Nfa& nfa)
{
    MetaSet mset;
    NodeMap nmap;

    // initial node set of dfa
    NodeSet nset;

    // build alphabet of nfa
    Alphabet alphabet;
    build_alphabet(nfa, alphabet);

    // initially, closure of nfa's initial state is the only state in E and becomes E's
    // initial state
    {
        NodeSet t;
        t.insert(nfa.initial);
        closure(nfa, t, nset);
        mset[nset] = false;
    }

    // while there is an unmarked node in E
    MetaSet::iterator i;
    while ((i = find_if(mset.begin(), mset.end(), is_not_marked())) != mset.end())
    {
        // mark node
        i->second = true;

        const NodeSet& t = i->first;
        for_each(alphabet.begin(), alphabet.end(), add_to_map(nfa, nmap, mset, t));
    }

    create_dfa(nmap, mset, nfa, nset);
}

// This function computes the E-closure of a set of NFA nodes.
// The E-closure is the set of Nfa states (nodes) reachable from
// some Nfa state in the set T on a Null-transition alone.
template<class T, class I, TEMPLATE_PARAM(E), TEMPLATE_PARAM(N) >
void Dfa<T, I, E, N>::closure(const Nfa& nfa, const NodeSet& s_in, NodeSet& s_out)
{
    NodeStack s;

    // push all the nodes of the set s_in onto the stack
    for_each(s_in.begin(), s_in.end(), push_node(s));

    // initialize E-closure(s_out) to s_in
    s_out = s_in;

    while (!s.empty())
    {
        int t = s.top();
        s.pop();
        for_each(nfa.nodes[t].edges.begin(), nfa.nodes[t].edges.end(), add_llamda_trans(s_out, s));
    }
}

// This function will create an DFA out of a NodeMap, where [T, t] = U.
template<class T, class I, TEMPLATE_PARAM(E), TEMPLATE_PARAM(N) >
void Dfa<T, I, E, N>::create_dfa(const NodeMap& nmap, const MetaSet& mset, const Nfa& nfa, const NodeSet& nset)
{
    NodePtrMap p;

    clear();
    for_each(mset.begin(), mset.end(), make_dfa_node(p, nfa, nset, *this));
    for_each(nmap.begin(), nmap.end(), add_edges(*this, p));
}



} // namespace dfa

#endif // DFA_HPP
