#ifndef __STACK_H__
#define __STACK_H__




#include <stdbool.h>




extern const void * Stack;
extern const void * StackClass;

void * pop(void * stack);
void * push(void * stack, const void * element);
bool empty(const void * stack);
void * top(const void * stack);

void loadStack();




#endif