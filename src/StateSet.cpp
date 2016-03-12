#include "StateSet.h"
#include <queue>
using std::queue;

void StateSet::Move(char ch)
{
    set<int> temp;
    for(auto state : states)
    {
        for(auto edge = nfa->nodes[state]->edges; edge; edge = edge->next)
        {
            if(edge->kind == CHAR && edge->val == ch)
            {
                temp.insert({edge->to});
            }
        }
    }
    std::swap(temp,states);
}

void StateSet::e_Closure()
{
    set<int> temp = states;
    queue<int> Q;
    for(auto state : states)
    {
        Q.push(state);
    }
    while(!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for(auto edge = nfa->nodes[u]->edges; edge; edge = edge->next)
        {
            if(edge->kind == EPSILON)
            {
                temp.insert({edge->to});
                Q.push(edge->to);
            }
        }
    }
    std::swap(states,temp);
}


void  StateSet::e_ClosureAfterMove(char ch)
{
    Move(ch);
    e_Closure();
}
