#include "Regex.h"
#include<iostream>
void Regex::compile(string pattern)
{
    if(nfa != NULL)
    {
        delete nfa;
        nfa = NULL;
    }
    Parser* parser = new Parser(pattern);
    TreeNode* ast = parser->Exp();
    delete parser;
    nfa = new NFA(ast);
    delete ast;
}

bool Regex::match(string str)
{
    StateSet S(nfa);
    for(auto ch : str)
    {
        S.e_ClosureAfterMove(ch);
    }
    for(auto state : S.states)
    {
        if(state == nfa->this_nfa.second)
            return true;
    }
    return false;
}
