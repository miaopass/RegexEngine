#ifndef NFA_H
#define NFA_H

#include<map>
#include<parser.h>
#include<iostream>


using std::map;
using std::pair;

enum EdgeKind
{
    EPSILON = 266,
    CHAR = 267,
};

struct Edge
{
    EdgeKind kind;
    char val;
    int from,to;
    Edge* next;
    Edge(EdgeKind _kind,char _val,int _from,int _to) : kind(_kind),val(_val),from(_from),to(_to),next(NULL){ }
    ~Edge()
    {
        if(next)
            delete next;
    }
};

struct Node
{
    Edge* edges;
    int num;
    Node(int _num,Edge* _edges = NULL) : num(_num),edges(_edges) { }
    ~Node()
    {
        if(edges)
            delete edges;
    }
};

class NFA
{
    friend class Regex;
    friend class StateSet;
    public:
        NFA(TreeNode* root) : ast_root(root),current_num(0) { this_nfa = createNFA(root); }
        void printNFA()
        {
            for(auto ele: nodes)
            {
                auto node = ele.second;
                for(auto edge = node->edges;edge;edge = edge->next)
                {
                    std::cout<<node->num<<"-----"<<edge->val<<"----->"<<edge->to<<std::endl;
                }
            }
        }
        virtual ~NFA();
    private:
        map<int,Node*> nodes;
        TreeNode* ast_root;
        int current_num;
        pair<int,int> this_nfa;
        int getNewNodeNum(){ return current_num++; }
        void addEdge(EdgeKind kind,char val,int from,int to);
        pair<int,int> createNFA(TreeNode* root);
};

#endif // NFA_H
