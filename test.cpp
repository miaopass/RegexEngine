#include <iostream>
#include<string>
#include "parser.h"
#include "NFA.h"
using namespace std;

/*void printTree(TreeNode* root)
{
    if(root == NULL)
    {
        cout<<"NULL"<<endl;
        return;
    }
    cout<<root->getVal()<<endl;
    printTree(root->left);
    printTree(root->right);
}*/

int main()
{
    string pat;

    while(cin>>pat){
        auto p = new Parser(pat);
        auto tree = p->Exp();
        auto nfa = new NFA(tree);
        nfa->printNFA();
    }
    return 0;
}
