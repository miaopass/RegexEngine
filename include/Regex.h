#ifndef REGEX_H
#define REGEX_H
#include"NFA.h"
#include"parser.h"
#include<string>
#include<set>
#include<queue>
#include<iostream>
#include "StateSet.h"
using std::string;
using std::set;
using std::queue;



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
