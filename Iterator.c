#include <stdarg.h>
#include <assert.h>
#include <stddef.h>

#include "Iterator.h"
#include "Iterator_r.h"
#include "Object.h"
#include "Class.h"
#include "New.h"




const void * Iterator;

const void * IteratorClass;



struct Object * start(const struct Iterator * iter)
{
	struct IteratorClass * class = classOf(iter);

	if (class)
	{
		return class->start(iter);
	}
	else
	{
		return NULL;
	}
}

struct Object * end(const struct Iterator * iter)
{
	struct IteratorClass * class = classOf(iter);

	if (class)
	{
		return class->end(iter);
	}
	else
	{
		return NULL;
	}
}

struct Object * next(struct Iterator * iter)
{
	struct IteratorClass * class = classOf(iter);

	if (class)
	{
		return class->next(iter);
	}
	else
	{
		return NULL;
	}
}




static void * IteratorClass_ctor(const void * _self, va_list * _args)
{
	struct IteratorClass * ic = super_ctor(IteratorClass, _self, _args);
	typedef void (*voidf)();
	voidf selector;
	voidf method;
	va_list args = *_args;

	assert(ic);

	while ((selector = va_arg(args, voidf)) != 0)
	{
		method = va_arg(args, voidf);

		if (selector == start)
		{
			ic->start = method;
		}
		else if (selector == end)
		{
			ic->end = method;
		}
		else if (selector == next)
		{
			ic->next = method;
		}
	}

	return ic;
	
}




static void * Iterator_ctor(const void * _self, va_list * args)
{
	struct Iterator * self = cast(Iterator, _self);
	void * data = va_arg(*args, void *);

	assert(self);
	
	self->data = data;
	self->index = 0;

	
	return _self;
}

static void * Iterator_dtor(const void * _self)
{
	struct Iterator * self = cast(Iterator, _self);
	void * data = self->data;

	delete(data);

	return _self;
}

static struct Object * Iterator_start(const struct Iterator *iter)
{
	return NULL;
}

static struct Object * Iterator_end(const struct Iterator *iter)
{
	return NULL;
}

static struct Object * Iterator_next(const struct Iterator *iter)
{
	return NULL;
}





void loadIterator()
{
	if (!IteratorClass)
	{
		IteratorClass = new (Class, "IteratorClass", Class, sizeof(struct IteratorClass), ctor, IteratorClass_ctor, 0);
	}

	if (!Iterator)
	{
		Iterator = new (IteratorClass, "Iterator", Object, sizeof(struct Iterator), ctor, Iterator_ctor, dtor, Iterator_dtor, start, Iterator_start, end, Iterator_end, next, Iterator_next, 0);
	}
}


