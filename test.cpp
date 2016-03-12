#include <iostream>
#include<string>
#include "Regex.h"

using std::cout;
using std::endl;
using std::string;

int main(int argc,char** argv)
{
    if(argc != 3)
    {
        cout<<"arguments error\n";
        return 0;
    }
    string pat = string(argv[1]);
    string str = string(argv[2]);
    Regex re = Regex();
    re.compile(pat);
    if(re.match(str))
        cout<<"true\n";
    else cout<<"false\n";
    return 0;
}
