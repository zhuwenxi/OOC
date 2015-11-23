#include "New.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

#include "Class_r.h"
#include "Object_r.h"

static void * ctor(void * self, va_list * args);
static void * dtor(void * self);
static void * classOf(void * self);

void * new(void * _class, ...)
{
	const struct Class * class = _class;
	size_t size;
	struct Object * obj;
	va_list args;

	assert(class->ctor);
	
	if (class != NULL)
	{
		size = class->size;

		obj = (struct Object *)calloc(1, size);
		obj->class = class;

		va_start(args, _class);
		obj = ctor(obj, &args);
		va_end(args);

		return obj;
	}
	else
	{
		return NULL;
	}
}

void delete(void * obj)
{
	if (obj != NULL)
	{
		free(dtor(obj));
	}
}

/*
 * Helper functions: 
 */

void * ctor(void * self, va_list * args)
{
	const struct Class * class = classOf(self);

	assert(class && class->ctor);

	return class->ctor(self, args);
}

void * dtor(void * self)
{
	const struct Class * class = classOf(self);

	assert(class && class->dtor);

	return class->dtor(self);
}

void * classOf(void * self)
{
	const struct Object * obj = self;

	assert(obj && obj->class);

	return obj->class;
}