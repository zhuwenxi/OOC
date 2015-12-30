#ifndef __STACK_R_H__
#define __STACK_R_H__




#include "Object_r.h"
#include "Class_r.h"
#include "Set_r.h"




struct Stack
{
	struct Object _;
	unsigned int top;
	struct Set * stack;
};

struct StackClass
{
	struct Class _;
	void * (*pop)(void * stack);
	void * (*push)(void * stack, const void * element);
	bool (*empty)(const void * stack);
	void * (*top)(const void * stack);
};
#endif