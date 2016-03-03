#ifndef REGEX_H
#define REGEX_H
#include"NFA.h"
#include"parser.h"
#include<string>
#include<set>
#include<queue>
#include<iostream>
using std::string;
using std::set;
using std::queue;

class StateSet
{

private:
    NFA* nfa;

    void Move(char ch)
    {
        set<int> temp;
        for(auto state : states)
        {
           for(auto edge = nfa->nodes[state]->edges;edge;edge = edge->next)
           {
               if(edge->kind == CHAR && edge->val == ch)
               {
                   temp.insert({edge->to});
               }
           }
        }
        std::swap(temp,states);
    }

    void e_Closure()
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
            for(auto edge = nfa->nodes[u]->edges;edge;edge = edge->next)
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
public:
    set<int> states;
    void e_ClosureAfterMove(char ch)
    {
        Move(ch);
        e_Closure();
    }
    StateSet(NFA* _nfa) : nfa(_nfa) { states.insert({nfa->this_nfa.first});e_Closure(); }
};

class Regex
{
public:
    Regex() = default;
    virtual ~Regex()
    {
        delete nfa;
    };
    bool match(string str);
    void compile(string pattern);
private:
    NFA* nfa = NULL;

};

#endif // REGEX_H
