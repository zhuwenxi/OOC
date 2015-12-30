#include "Stack.h"
#include "Stack_r.h"
#include "Class.h"
#include "Class_r.h"
#include "Object.h"
#include "Object_r.h"
#include "Set.h"
#include "Set_r.h"
#include "String.h"
#include "String_r.h"
#include "New.h"

#include <stdarg.h>
#include <assert.h>




void * pop(void * stack)
{
	struct StackClass * class = classOf(stack);

	assert(class);

	return class->pop(stack);
}

void * push(void * stack, const void * element)
{
	struct StackClass * class = classOf(stack);

	assert(class);

	return class->push(stack, element);
}

bool empty(const void * stack)
{
	struct StackClass * class = classOf(stack);

	assert(class);

	return class->empty(stack);
}

void * top(const void * stack)
{
	struct StackClass * class = classOf(stack);

	assert(class);

	return class->top(stack);
}

static void * Stack_ctor(void * _self, va_list * args)
{
	struct Stack * self = cast(Stack, _self);

	assert(self);

	self->stack = new (Set, 0);
	self->top = 0;
	
	return _self;
}

static void * Stack_dtor(void * _self)
{
	struct Stack * self = cast(Stack, _self);

	assert(self);

	delete(self->stack);

	return _self;
}

static void * Stack_pop(void * _stack)
{
	struct Stack * stack = cast(Stack, _stack);

	assert(stack);

	if (empty(stack))
	{
		// Stack is empty!
		assert(0);
	}
	else
	{
		void * topElement = clone(stack->stack->items[stack->top - 1]);

		erase(stack->stack, stack->stack->items[stack->top - 1]);
		stack->stack->items[stack->top - 1] = NULL;
		stack->top--;

		return topElement;
		
	}
}

static void * Stack_push(void * _stack, const void * _element)
{
	struct Stack * stack = cast(Stack, _stack);

	assert(stack);

	insert(stack->stack, _element);
	stack->top++;

	return _element;
}

static bool Stack_empty(const void * _stack)
{
	struct Stack * self = cast(Stack, _stack);

	assert(self);

	return !self->top;
}

static void * Stack_top(const void * _stack)
{
	struct Stack * stack = cast(Stack, _stack);

	assert(stack);

	if (empty(stack))
	{
		// Stack is empty!
		assert(0);
	}
	else
	{
		void * topElement = clone(stack->stack->items[stack->top - 1]);

		return topElement;
	}
}

static struct String * Stack_toString(const void * _stack)
{
	struct Stack * self = cast(Stack, _stack);

	assert(self);
	
	return toString(self->stack);
}

static void * StackClass_ctor(void * _self, va_list * args)
{
	struct StackClass * self = super_ctor(StackClass, _self, args);

	assert(self);

	typedef void (*voidf)();
	voidf selector;
	voidf method;
	va_list arg = *args;

	while ((selector = va_arg(arg, voidf))!= 0)
	{
		method = va_arg(arg, voidf);

		if (selector == pop)
		{
			self->pop = method;
		}
		else if (selector == push)
		{
			self->push = method;
		}
		else if (selector == empty)
		{
			self->empty = method;
		}
		else if (selector == top)
		{
			self->top = method;
		}
	}

	return _self;

}




const void * Stack;
const void * StackClass;

void loadStack()
{
	if (!StackClass)
	{
		StackClass = new (Class, "StackClass", Class, sizeof(struct StackClass), ctor, StackClass_ctor, 0);
	}

	if (!Stack)
	{
		Stack = new (StackClass, "Stack", Object, sizeof(struct Stack), ctor, Stack_ctor, dtor, Stack_dtor, pop, Stack_pop, push, Stack_push, empty, Stack_empty, top, Stack_top, toString, Stack_toString, 0);
	}
}