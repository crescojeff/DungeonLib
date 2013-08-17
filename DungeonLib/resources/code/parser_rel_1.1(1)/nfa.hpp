// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// nfa template class

#ifndef NFA_HPP
#define NFA_HPP

#include "all.hpp"
#include <vector>
#include <stack>
#include <exception>

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

namespace NFA {

enum NodeFlag {
    NO_NODE_FLAG,
    CLEAR_COUNT,        // count var. has index of node w/ actual count
    INCREMENT_COUNT,    // count var. has index of node w/ actual count
};

enum EdgeFlag {
    NO_EDGE_FLAG,
    CONT_COUNT_LOOP,
    EXIT_COUNT_LOOP,
    CONT_MIN_LOOP,
    EXIT_MIN_LOOP,
    CONT_MIN_MAX_LOOP,
    EXIT_MIN_MAX_LOOP
};

enum LoopType {
    COUNT_LOOP,
    MIN_LOOP,
    MIN_MAX_LOOP
};

// Edge type
template<class T>
class Edge {

public:
    typedef T trans_type;

    Edge() : flag(NO_EDGE_FLAG) {}
    Edge(const trans_type& aTrans, int aNode, EdgeFlag aFlag = NO_EDGE_FLAG) :
        trans(aTrans), node(aNode), flag(aFlag) {}

    trans_type trans;
    int node;
    EdgeFlag flag;
};

// Node type
#if CAN_HANDLE_TEMPLATE_TEMPLATE_PARAMETERS
template<class T, class I, template<class> class E = std::vector>
#else
template<class T, class I, class E = std::vector<Edge<T> > >
#endif
class Node {

public:

#if CAN_HANDLE_TEMPLATE_TEMPLATE_PARAMETERS
    typedef T trans_type;
    typedef I input_type;
    typedef typename I::NodeInfoType info_type;
    typedef Edge<T> edge_type;
    typedef E<edge_type> edges_type;
#else
    typedef T trans_type;
    typedef I input_type;
    typedef typename I::NodeInfoType info_type;
    typedef Edge<T> edge_type;
    typedef E edges_type;
#endif

    explicit Node(bool aFinal = false) : final(aFinal), flag(NO_NODE_FLAG), count(0), min(0), max(0) {}

    Node(int aCount, int aMin, int aMax, NodeFlag aFlag = NO_NODE_FLAG) :
        final(false), flag(aFlag), count(aCount), min(aMin), max(aMax) {}

    explicit Node(const info_type& aInfo) : final(false), flag(NO_NODE_FLAG), count(0), min(0), max(0), info(aInfo) {}

    void addEdge(const edge_type& e) {edges.push_back(e);}
    void addEdge(const trans_type& aTrans, int aNode, EdgeFlag aFlag = NO_EDGE_FLAG)
        {ASSERT(!full()); edges.push_back(edge_type(aTrans, aNode, aFlag));}

    bool empty() const {return edges.empty();}
    bool full() const {return edges.size() >= edges.max_size();}
    void clear() {edges.clear(); flag = NO_NODE_FLAG;}

    bool final;
    NodeFlag flag;
    int count, min, max;
    info_type info;
    edges_type edges;
};

// NFA type
#if CAN_HANDLE_TEMPLATE_TEMPLATE_PARAMETERS
template<class T, class I, template<class> class E = std::vector, template<class> class N = std::vector>
#else
template<class T, class I, class E = std::vector<Edge<T> >, class N = std::vector<Node<T, I, E> > >
#endif
class Nfa {
public:

#if CAN_HANDLE_TEMPLATE_TEMPLATE_PARAMETERS
    typedef T trans_type;
    typedef I input_type;
    typedef Edge<T> edge_type;
    typedef E<edge_type> edges_type;
    typedef Node<T, I, E> node_type;
    typedef N<node_type> nodes_type;
#else
    typedef T trans_type;
    typedef I input_type;
    typedef Edge<T> edge_type;
    typedef E edges_type;
    typedef typename N::value_type node_type;
    typedef N nodes_type;
#endif

    Nfa() : initial(0) {}

    int addNode() {nodes.push_back(node_type()); return nodes.size() - 1;}
    int addNode(const node_type& node) {nodes.push_back(node); return nodes.size() - 1;}

    int addEdge(int from, int to, const trans_type& trans)
        {nodes[from].addEdge(edge_type(trans, to)); return nodes[from].edges.size() - 1;}
    int addNullEdge(int from, int to, EdgeFlag aFlag = NO_EDGE_FLAG)
        {nodes[from].addEdge(edge_type(trans_type(), to, aFlag)); return nodes[from].edges.size() - 1;}

    int last() const {return nodes.size() - 1;}
    void clear() {nodes.clear();}

    // the transformation functions take as parameter the indices of the initial and final
    // nodes of the sub-nfa to transform.  on return, the parameters will contain the
    // indices to the new initial and final nodes of the transformed sub-nfa.
    // the functions assume that is only one final node, and that the final flag is not set.
    // the functions create only one final node.
    // the functions also assume that the given sub-nfa will contain only transitions within
    // the sub_nfa.
    // no function will set the final flag.

    // xform function to loop zero or times on the nfa
    void xFormZeroOrMore(int initial, int& final);

    // xform function to loop one or times on the nfa
    void xFormOneOrMore(int initial, int& final);

    // xform function to loop zero or once on the nfa
    void xFormZeroOrOne(int initial, int& final);

    // xform function to loop count times on the nfa
    void xFormCount(int& initial, int& final, int count);

    // xform function to loop at least min times on the nfa
    void xFormMin(int& initial, int& final, int min);

    // xform function to loop at least min and at most max times on the nfa
    void xFormMinAndMax(int& initial, int& final, int min, int max);

    // xform function to "or" to sub-nfas
    void xFormOr(int& initial, int& final, int initial2, int final2);

    // function to match input against nfa
    bool traverse(input_type& input);

    nodes_type nodes;
    int initial;

private:
    void onTrans(node_type& node, input_type& input);

    bool canTrans(node_type& node, edge_type& edge, input_type& input);

    // xForm function to loop count, min, or min & max times on the nfa
    void xFormLoop(int& initial, int& final, LoopType loop, int min, int max = 0);
};

template<class T, class I, TEMPLATE_PARAM(E), TEMPLATE_PARAM(N) >
inline void Nfa<T, I, E, N>::xFormZeroOrMore(int initial, int& final)
{
    const int new_final = addNode();
    addNullEdge(initial, new_final);
    addNullEdge(final, initial);
    addNullEdge(final, new_final);
    final = new_final;
}

template<class T, class I, TEMPLATE_PARAM(E), TEMPLATE_PARAM(N) >
inline void Nfa<T, I, E, N>::xFormOneOrMore(int initial, int& final)
{
    const int new_final = addNode();
    addNullEdge(final, initial);
    addNullEdge(final, new_final);
    final = new_final;
}

template<class T, class I, TEMPLATE_PARAM(E), TEMPLATE_PARAM(N) >
inline void Nfa<T, I, E, N>::xFormZeroOrOne(int initial, int& final)
{
    const int new_final = addNode();
    addNullEdge(initial, new_final);
    addNullEdge(final, new_final);
    final = new_final;
}

template<class T, class I, TEMPLATE_PARAM(E), TEMPLATE_PARAM(N) >
void Nfa<T, I, E, N>::xFormLoop(int& initial, int& final, LoopType loop, int min, int max)
{
    const int new_initial_node_index = addNode();   // new initial node
    const int check_node_index = addNode(node_type(0, min, max));   // node to check counter
    const int zero_node_index = addNode(node_type(check_node_index, 0, 0, CLEAR_COUNT));    // node to zero counter
    const int loop_node_index = addNode(node_type(check_node_index, 0, 0, INCREMENT_COUNT));    // node to inc. counter and loop back
    const int new_final_node_index = addNode(); // new final node

    // move all edges from initial node to new initial node
    nodes[new_initial_node_index] = nodes[initial];
    nodes[initial].clear();

    // add Null edges
    addNullEdge(initial, zero_node_index);
    addNullEdge(zero_node_index, check_node_index);
    addNullEdge(final, loop_node_index);
    addNullEdge(loop_node_index, check_node_index);

    // add check count edges.
    EdgeFlag flag1, flag2;
    if (loop == COUNT_LOOP)
    {
        flag1 = CONT_COUNT_LOOP;
        flag2 = EXIT_COUNT_LOOP;
    }
    else if (loop == MIN_LOOP)
    {
        flag1 = CONT_MIN_LOOP;
        flag2 = EXIT_MIN_LOOP;
    }
    else
    {
        flag1 = CONT_MIN_MAX_LOOP;
        flag2 = EXIT_MIN_MAX_LOOP;
    }

    addNullEdge(check_node_index, new_initial_node_index, flag1);
    addNullEdge(check_node_index, new_final_node_index, flag2);

    initial = new_initial_node_index;
    final = new_final_node_index;
}

template<class T, class I, TEMPLATE_PARAM(E), TEMPLATE_PARAM(N) >
inline void Nfa<T, I, E, N>::xFormCount(int& initial, int& final, int count)
{
    xFormLoop(initial, final, COUNT_LOOP, count);

}

template<class T, class I, TEMPLATE_PARAM(E), TEMPLATE_PARAM(N) >
inline void Nfa<T, I, E, N>::xFormMin(int& initial, int& final, int min)
{
    xFormLoop(initial, final, MIN_LOOP, min);

}

template<class T, class I, TEMPLATE_PARAM(E), TEMPLATE_PARAM(N) >
inline void Nfa<T, I, E, N>::xFormMinAndMax(int& initial, int& final, int min, int max)
{
    xFormLoop(initial, final, MIN_MAX_LOOP, min, max);

}

template<class T, class I, TEMPLATE_PARAM(E), TEMPLATE_PARAM(N) >
inline void Nfa<T, I, E, N>::xFormOr(int& initial, int& final, int initial2, int final2)
{
    addNullEdge(initial, initial2);
    addNullEdge(final, final2);
    initial = initial2;
    final = final2;
}

template<class T, class I, TEMPLATE_PARAM(E), TEMPLATE_PARAM(N) >
inline Nfa<T, I, E, N>& operator<<(Nfa<T, I, E, N>& nfa, const typename Nfa<T, I, E, N>::node_type& node)
{
    nfa.addNode(node);
    return nfa;
}

template<class T, class I, TEMPLATE_PARAM(E) >
inline Node<T, I, E>& operator<<(Node<T, I, E>& node, const Edge<T>& edge)
{
    node.addEdge(edge);
    return node;
}

template<class T>
inline bool operator==(const Edge<T>& e1, const Edge<T>& e2)
{
    return e1.node == e2.node && e1.trans == e2.trans;
}

template<class T>
inline bool operator!=(const Edge<T>& e1, const Edge<T>& e2)
{
    return e1.node != e2.node || e1.trans != e2.trans;
}

template<class T, class I, TEMPLATE_PARAM(E), TEMPLATE_PARAM(N) >
std::ostream& operator<<(std::ostream& out, const Nfa<T, I, E, N>& nfa)
{
    for (int i = 0; i < nfa.nodes.size(); ++i)
        out << "Node #" << i << ": " << std::endl << nfa.nodes[i] << std::endl;
    return out;
}

template<class T, class I, TEMPLATE_PARAM(E) >
std::ostream& operator<<(std::ostream& out, const Node<T, I, E>& node)
{
    out << "Flag: ";
    switch (node.flag)
    {
    case NO_NODE_FLAG: out << "None" << std::endl; break;
    case CLEAR_COUNT: out << "Clear Count (" << node.count << ")" << std::endl; break;
    case INCREMENT_COUNT: out << "Inc. Count (" << node.count << ")" << std::endl; break;
    default: out << "UNKNOWN" << std::endl; break;
    }

    out << "{" << node.min << "," << node.max << "}" << std::endl;

    if (node.final)
        out << "(final)" << std::endl;

    for (int i = 0; i < node.edges.size(); ++i)
        out << "  Edge #" << i << ": " << node.edges[i] << std::endl;
    return out;
}

template<class T>
inline std::ostream& operator<<(std::ostream& out, const Edge<T>& edge)
{
    out << edge.trans << " --> " << edge.node;
    out << "  Flag: ";
    switch (edge.flag)
    {
    case NO_EDGE_FLAG: out << "None" << std::endl; break;
    case CONT_COUNT_LOOP: out << "Count Loop Check" << std::endl; break;
    case EXIT_COUNT_LOOP: out << "Exit Count Loop" << std::endl; break;
    case CONT_MIN_LOOP: out << "Min. Loop" << std::endl; break;
    case EXIT_MIN_LOOP: out << "Exit Min. Loop" << std::endl; break;
    case CONT_MIN_MAX_LOOP: out << "Min. & Max. Loop" << std::endl; break;
    case EXIT_MIN_MAX_LOOP: out << "Exit Min. & Max. Loop" << std::endl; break;
    default: out << "UNKNOWN" << std::endl; break;
    }
    return out;
}

template<class I>
struct SavedPos {
    int node, edge, count;
    typename I::SavedPosType saved_pos;
};

template<class T, class I, TEMPLATE_PARAM(E), TEMPLATE_PARAM(N) >
bool Nfa<T, I, E, N>::traverse(input_type& input)
{
    typedef SavedPos<I> saved_type;

    std::stack<saved_type> back; // used for backtracking w/o recursion
    int node_index = initial;
    int edge_index = 0;

    saved_type pos;

    for (;;)
    {
        if (node_index < 0 || node_index >= int(nodes.size()))
            return false;

        node_type& node = nodes[node_index];

        onTrans(node, input);

        if (node.final)
            return true;

        pos.node = node_index;
        pos.count = node.count;
        input.savePos(pos.saved_pos);

        node_index = -1;
        while (edge_index < int(node.edges.size()))
        {
            edge_type& edge = node.edges[edge_index++];
            if (canTrans(node, edge, input))
            {
                // save position for backtracking
                if (edge_index < int(node.edges.size()))
                {
                    pos.edge = edge_index;
                    back.push(pos);
                }

                node_index = edge.node;
                edge_index = 0;
                break;
            }
        }

        if (node_index == -1)
        {
            // no usable transition was found, try to backtrack
            if (!back.empty())
            {
                pos = back.top();
                back.pop();
                node_index = pos.node;
                edge_index = pos.edge;
                nodes[node_index].count = pos.count;
                input.restorePos(pos.saved_pos);
            }
            else
                return false;
        }
    }
}

template<class T, class I, TEMPLATE_PARAM(E), TEMPLATE_PARAM(N) >
inline void Nfa<T, I, E, N>::onTrans(node_type& node, input_type& input)
{
    switch (node.flag)
    {
    case NO_NODE_FLAG:
        break;

    case CLEAR_COUNT:
        nodes[node.count].count = 0;
        break;

    case INCREMENT_COUNT:
        ++nodes[node.count].count;
        break;
    }

    input.callback(*this, node.info);
}

template<class T, class I, TEMPLATE_PARAM(E), TEMPLATE_PARAM(N) >
inline bool Nfa<T, I, E, N>::canTrans(node_type& node, edge_type& edge, input_type& input)
{
    if (edge.flag == NO_EDGE_FLAG)
        return input.match(edge.trans);
    else if (edge.flag == CONT_COUNT_LOOP)
        return (node.count < node.min) ? true : false;
    else if (edge.flag == EXIT_COUNT_LOOP)
        return (node.count >= node.min) ? true : false;
    else if (edge.flag == CONT_MIN_LOOP)
        return true;
    else if (edge.flag == EXIT_MIN_LOOP)
        return (node.count >= node.min) ? true : false;
    else if (edge.flag == CONT_MIN_MAX_LOOP)
        return (node.count < node.max) ? true : false;
    else if (edge.flag == EXIT_MIN_MAX_LOOP)
        return (node.count >= node.min) ? true : false;
    else
        return false;
}

} // namespace NFA

#endif // NFA_HPP
