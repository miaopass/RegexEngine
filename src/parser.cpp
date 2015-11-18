#include "parser.h"

void Parser::scan()
{
    for(auto ch : pattern)
    {
        switch(ch)
        {
            case '(' : tokens.push_back(Token(LEFT,"("));break;
            case ')' : tokens.push_back(Token(RIGHT,")"));break;
            case '*' : tokens.push_back(Token(STAR,"*"));break;
            case '|' : tokens.push_back(Token(UPRIGHT,"|"));break;
            case '$' : tokens.push_back(Token(DOLLAR,"$"));break;
            default : tokens.push_back(Token(ID,string(1,ch)));break;
        }
    }
    lookhead = tokens.begin();
}

void Parser::match(const Token& t)
{
    if(t.getKind() == ID)
        ++lookhead;
    else if(t == *lookhead)
        ++lookhead;
    else
        error(t.getVal(),lookhead->getVal());
}

TreeNode* Parser::Exp()
{
    if(lookhead->getKind() == ID ||lookhead->getKind() == LEFT)
    {
        return ExpR(Term());
    }
    else error("ID or (",lookhead->getVal());//error
}

TreeNode* Parser::ExpR(TreeNode* inh)
{

    switch(lookhead->getKind())
    {
        case UPRIGHT : match(Token(UPRIGHT,"|"));return ExpR(new TreeNode(NODE,"|",inh,Term()));break;
        case RIGHT :
        case DOLLAR : return inh;break;
        default : error("| or ) or $",lookhead->getVal());break;
    }
}

TreeNode* Parser::Term()
{
    if(lookhead->getKind() == ID || lookhead->getKind() == LEFT)
    {
        return TermR(Rep());
    }
    else error("ID or (",lookhead->getVal());//error
}

TreeNode* Parser::TermR(TreeNode* inh)
{
    switch(lookhead->getKind())
    {
        case ID:
        case LEFT : return TermR(new TreeNode(NODE,"+",inh,Rep()));break;
        case UPRIGHT :
        case RIGHT :
        case DOLLAR : return inh;break;
        default : error("ID,(,|,),$",lookhead->getVal());break;
    }
}

TreeNode* Parser::Rep()
{
    if((lookhead)->getKind()== ID || (lookhead)->getKind() == LEFT)
    {
        return RepR(Factor());
    }
    else error("ID,(",lookhead->getVal());//error
}

TreeNode* Parser::RepR(TreeNode* inh)
{
    if((lookhead)->getKind() == STAR)
    {
        match(Token(STAR,"*"));
        return new TreeNode(NODE,"*",inh,NULL);
    }
    else return inh;
}

TreeNode* Parser::Factor()
{
    if(lookhead->getKind() == ID )
    {
        auto temp = new TreeNode(LEAF,lookhead->getVal(),NULL,NULL);
        match(*lookhead);
        return temp;
    }
    else if( lookhead->getKind() == LEFT )
    {
        match(Token(LEFT,"("));
        TreeNode* temp = Exp();
        match(Token(RIGHT,")"));
        return temp;
    }
    else error("ID,(",lookhead->getVal());//error
}
