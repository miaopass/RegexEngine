#ifndef STATESET_H
#define STATESET_H
#include<set>
#include"NFA.h"

using std::set;

class StateSet
{

friend class Regex;

private:

    set<int> states;
    NFA* nfa;
    void Move(char ch);
    void e_Closure();
    void e_ClosureAfterMove(char ch);
    StateSet(NFA* _nfa) : nfa(_nfa) { states.insert({nfa->this_nfa.first});e_Closure(); }
};

#endif // STATESET_H
