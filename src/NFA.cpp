#include "NFA.h"


NFA::~NFA()
{
    //dtor
    for(auto node : nodes)
        delete node.second;
}

void NFA::addEdge(EdgeKind kind,char val,int from,int to)
{
    auto edge = new Edge(kind,val,from,to);
    if(nodes.find(from) == nodes.end())
    {
        nodes.insert({from,new Node(from,edge)});
    }
    else
    {
        auto node = nodes[from];
        edge->next = node->edges;
        node->edges = edge;
    }
    if(nodes.find(to) == nodes.end())
    {
        nodes.insert({to,new Node(to)});
    }
}


pair<int,int> NFA::createNFA(TreeNode* root)
{
    switch(root->getKind())
    {
        case CONNECT : {
                auto left_nfa = createNFA(root->left);
                auto right_nfa = createNFA(root->right);

                addEdge(EPSILON,' ',left_nfa.second,right_nfa.first);

                return {left_nfa.first,right_nfa.second};
        }
        case OR : {
                auto left_nfa = createNFA(root->left);
                auto right_nfa = createNFA(root->right);

                int new_left = getNewNodeNum();
                int new_right = getNewNodeNum();

                addEdge(EPSILON,' ',new_left,left_nfa.first);
                addEdge(EPSILON,' ',new_left,right_nfa.first);
                addEdge(EPSILON,' ',left_nfa.second,new_right);
                addEdge(EPSILON,' ',right_nfa.second,new_right);

                return {new_left,new_right};
        }
        case REPEAT : {
                auto nfa = createNFA(root->left);

                int new_left = getNewNodeNum();
                int new_right = getNewNodeNum();

                addEdge(EPSILON,' ',new_left,nfa.first);
                addEdge(EPSILON,' ',new_left,new_right);
                addEdge(EPSILON,' ',nfa.second,nfa.first);
                addEdge(EPSILON,' ',nfa.second,new_right);

                return {new_left,new_right};
        }
        case LEAF : {
                int new_left = getNewNodeNum();
                int new_right = getNewNodeNum();
                addEdge(CHAR,root->getVal(),new_left,new_right);
                return {new_left,new_right};
        }
    }
}
