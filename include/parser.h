#ifndef PARSER_H
#define PARSER_H

#include<string>
#include<vector>
#include<iostream>
#include<unistd.h>
#include<cstdlib>
#include<stdio.h>

using std::string;
using std::vector;

class Token;
class Parser;

enum TokenKind
{
    ID = 256,
    STAR = 257,
    LEFT = 258,
    RIGHT = 259,
    UPRIGHT = 260,
    DOLLAR = 261,
};

enum TreeNodeKind
{
    CONNECT = 262,
    OR = 263,
    REPEAT = 264,
    LEAF = 265,
};

class Token
{
private:
    TokenKind kind;
    char val;
public:
    Token(TokenKind k,char v) : kind(k),val(v){}
    Token(const Token& s) = default;
    char getVal() const { return this->val; }
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
    char val;
public:
    TreeNode* left;
    TreeNode* right;
public:
    TreeNode(TreeNodeKind k,char v,TreeNode* l,TreeNode* r) :kind(k),val(v),left(l),right(r){ }
    char getVal() { return val; }
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
        virtual ~Parser() = default;
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
            fprintf(stderr,"expected '%s' before '%s'\n",exp.c_str(),but.c_str());
            exit(0);
        }

};

#endif // PARSER_H
