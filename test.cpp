#include <iostream>
#include<string>
#include "parser.h"
#include "NFA.h"
#include "Regex.h"
using namespace std;


int main()
{
    string pat,str;
    while(cin>>pat>>str)
    {
        Regex re;
        re.compile(pat);
        if( re.match(str))
            cout<<"true"<<endl;
        else cout<<"false"<<endl;
    }
    system("pause");
    return 0;
}
