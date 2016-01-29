#ifndef __ABSTRACTSYNTAXTREE_R_H__
#define __ABSTRACTSYNTAXTREE_R_H__




#include "Object_r.h"
#include "String_r.h"

struct AbstractSyntaxTree
{
	struct Object _;
	struct AbstractSyntaxTreeNode * root;
};

struct AbstractSyntaxTreeNode
{
	struct Object _;
	struct String * operator;
	struct AbstractSyntaxTreeNodeOperator * leftOperand;
	struct AbstractSyntaxTreeNodeOperator * rightOperand;
	struct String * value;
	bool isLeaf;
};

//struct AbstractSyntaxTreeNodeOperator
//{
//	struct Object _;
//};

//struct AbstractSyntaxTreeNodeOperand
//{
//	struct Object _;
//	char * operandName;
//};

#endif