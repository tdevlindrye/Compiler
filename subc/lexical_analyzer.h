//
// Created by Tiffany Devlin-Drye on 2018-12-09.
//

#ifndef COP4020_LEXICAL_ANALYZER_H
#define COP4020_LEXICAL_ANALYZER_H
#include <string>
using namespace std;

class Node{

public:
    string nodeName;
    int nodeChildren;

    Node* child;
    Node* sibling;

    Node(string passed_name, int passed_children);
};

Node::Node(string passed_name, int passed_children) {
    this->nodeName = passed_name;
    this->nodeChildren = passed_children;

}


void build_Tree(string nodeName, int functionCalls);
void print_Tree_standard();
void print_Tree();
void Tiny();
void Consts();
void Const();
void ConstValue();
void Types();
void Type();
void LitList();
void SubProgs();
void Fcn();
void Params();
void Dclns();
void Dcln();
void Body();
void Statement();
void OutExp();
void StringNode();
int Caseclauses();
void Caseclause();
void CaseExpression();
int OtherwiseClause();
void Assignment();
void ForStat();
void ForExp();
void Expression();
void Term();
void Factor();
void Primary();
void Name();

#endif //COP4020_LEXICAL_ANALYZER_H