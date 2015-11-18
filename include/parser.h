#ifndef PARSER_H
#define PARSER_H
#include<string>
#include<vector>
#include<iostream>

using std::string;
using std::vector;

class Token;
class Parser;

enum TokenKind
{
    ID,
    STAR,
    LEFT,
    RIGHT,
    UPRIGHT,
    DOLLAR,
};

enum TreeNodeKind
{
    LEAF,
    NODE,
};

class Token
{
private:
    TokenKind kind;
    string val;
public:
    Token(TokenKind k,string v) : kind(k),val(v){}
    Token(const Token& s) = default;
    const string& getVal() const { return this->val; }
    TokenKind getKind() const { return this->kind; }
    bool operator==(const Token& rhs) const
    {
        return this->kind == rhs.kind && this->val == rhs.val;
    }
};

class TreeNode
{
private:
    TreeNodeKind kind;
    string val;
public:
    TreeNode* left;
    TreeNode* right;
public:
    TreeNode(TreeNodeKind k,string v,TreeNode* l,TreeNode* r) :kind(k),val(v),left(l),right(r){ }
    string getVal() { return val; }
    TreeNodeKind getKind() { return kind; }
    ~TreeNode()
    {
        if(left != NULL)
            delete left;
        if(right != NULL)
            delete right;
    }
};





class Parser
{
    public:
        Parser(const string& pat) : pattern(pat),AST_root(NULL) {scan();}
        virtual ~Parser()
        {
            if(AST_root)
                delete AST_root;
        }
        TreeNode* Exp();
    private:
        TreeNode* Term();
        TreeNode* ExpR(TreeNode* inh);
        TreeNode* TermR(TreeNode* inh);
        TreeNode* Rep();
        TreeNode* RepR(TreeNode* inh);
        TreeNode* Factor();
    private:
        TreeNode* AST_root;
        string pattern;
        vector<Token> tokens;
        vector<Token>::iterator lookhead;
        void match(const Token&);
        void scan();
        bool isID(char ch)
        {
            return ch <= '9' && ch >= '0' || ch <='z' && ch >='a' || ch <='Z' && ch >= 'A';
        }
        void error(const string& exp,const string& but)
        {
            std::cout<<"expected "<<exp<<",but got "<<but<<std::endl;
            exit(0);
        }

};

#endif // PARSER_H
