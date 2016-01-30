#include <assert.h>
#include <stdarg.h>

#include "New.h"
#include "AbstractSyntaxTree.h"
#include "AbstractSyntaxTree_r.h"
#include "Object.h"
#include "Object_r.h"
#include "Class.h"
#include "Class_r.h"
#include "String.h"
#include "String_r.h"

void * AbstractSyntaxTree_ctor(void * _self, va_list * args)
{
	struct AbstractSyntaxTreeNode * root = va_arg(*args, struct AbstractSyntaxTreeNode *);

	struct AbstractSyntaxTree * self = cast(AbstractSyntaxTree, _self);
	assert(self);

	self->root = root;

	return _self;
}

void * AbstractSyntaxTree_dtor(void * _self)
{
	struct AbstractSyntaxTree * self = cast(AbstractSyntaxTree, _self);
	assert(self);
	
	if (self->root)
	{
		delete(self->root);
	}

	return self;
}

struct String * AbstractSyntaxTree_toString(const void * _self)
{
	struct AbstractSyntaxTree * self = cast(AbstractSyntaxTree, _self);
	assert(self);

	if (self->root)
	{
		return toString(self->root);
	}
	else
	{
		return NULL;
	}
}

void * AbstractSyntaxTreeNode_ctor(void * _self, va_list * args)
{
	struct AbstractSyntaxTreeNode * self = cast(AbstractSyntaxTreeNode, _self);
	assert(self);

	bool isLeaf = va_arg(*args, bool);

	return self;
}

void * AbstractSyntaxTreeNode_dtor(void * _self)
{
	struct AbstractSyntaxTreeNode * self = cast(AbstractSyntaxTreeNode, _self);
	assert(self);
	
	struct AbstractSyntaxTreeNodeOperator * leftOperand = self->leftOperand;
	struct AbstractSyntaxTreeNodeOperator * rightOperand = self->rightOperand;
	struct String * operator = self->operator;
	struct String * value = self->value;

	if (leftOperand)
	{
		delete(leftOperand);
	}

	if (rightOperand)
	{
		delete(rightOperand);
	}

	if (operator)
	{
		delete(operator);
	}

	if (value)
	{
		delete(value);
	}

	return self;
}

struct String * AbstractSyntaxTreeNode_toString(const void * _self)
{
	struct AbstractSyntaxTreeNode * self = cast(AbstractSyntaxTreeNode, _self);
	assert(self);

	struct String * selfStr = clone(self->value);
	
	if (self->leftOperand)
	{
		struct String * tmp = selfStr;
		struct String * lineFeed = new (String, "\n", 0);
		struct String * leftOperandStr = toString(self->leftOperand);
		
		selfStr = add(selfStr, lineFeed, leftOperandStr, 0);

		delete(tmp);
		delete(lineFeed);
	}

	if (self->rightOperand)
	{
		struct String * tmp = selfStr;
		struct String * lineFeed = new (String, "\n", 0);
		struct String * rightOperandStr = toString(self->rightOperand);

		selfStr = add(selfStr, lineFeed, rightOperandStr, 0);

		delete(tmp);
		delete(lineFeed);
	}

	return selfStr;
}


const void * AbstractSyntaxTree;
const void * AbstractSyntaxTreeNode;
//const void * AbstractSyntaxTreeNodeOperator;
//const void * AbstractSyntaxTreeNodeOperand;

void loadAbstractSyntaxTree()
{
	if (!AbstractSyntaxTree)
	{
		AbstractSyntaxTree = new (Class, "AbstractSyntaxTree", Object, sizeof(struct AbstractSyntaxTree), ctor, AbstractSyntaxTree_ctor, dtor, AbstractSyntaxTree_dtor, toString, AbstractSyntaxTree_toString, 0);
	}

	if (!AbstractSyntaxTreeNode)
	{
		AbstractSyntaxTreeNode = new (Class, "AbstractSyntaxTreeNode", Object, sizeof(struct AbstractSyntaxTreeNode), ctor, AbstractSyntaxTreeNode_ctor, dtor, AbstractSyntaxTreeNode_dtor, toString, AbstractSyntaxTreeNode_toString, 0);
	}

	/*if (!AbstractSyntaxTreeNodeOperator)
	{

	}

	if (!AbstractSyntaxTreeNodeOperand)
	{

	}*/
}