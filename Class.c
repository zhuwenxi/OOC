#include "Class.h"
#include "Class_r.h"
#include "Object.h"
#include "Object_r.h"
#include "Log.h"
#include "String.h"
#include "String_r.h"

#include <stdarg.h>
#include <string.h>
#include <assert.h>


void * Class_ctor(void * _self, va_list * args)
{
	struct Class * self = _self;
	typedef void (*voidf)();
	voidf selector;
	va_list arg;

	log("Class_ctor()\n");

	self->name = va_arg(*args, char *);
	self->super = va_arg(*args, struct Class *);
	self->size = va_arg(*args, size_t);

	size_t offset = offsetof(struct Class, ctor);

	memcpy((char *)self + offset, (char *)self->super + offset, sizeOf(self->super) - offset);
	
	arg = *args;
	while ((selector = va_arg(arg, voidf)))
	{
		voidf method = va_arg(arg, voidf);

		if (selector == ctor)
		{
			self->ctor = method;
		} 
		else if (selector == dtor)
		{
			self->dtor = method;
		}
		else if (selector == hash)
		{
			self->hash = method;
		}
		else if (selector == equals)
		{
			self->equals = method;
		}
		else if (selector == toString)
		{
			self->toString = method;
		}
	}

	return self;
}

void * Class_dtor(void * self)
{
	log("Class_dtor()\n");
	return self;
}

bool Class_equals(const void * self, const void * another)
{
	log("Class_equals()\n");
	return self == another;
}

int Class_hash(const void * self)
{
	log("Class_hash()\n");
	return 0;
}

struct String * Class_toString(const void * _self)
{
	const struct Class * self = _self;

	if (self)
	{
		return new (String, self->name, strlen(self->name), 0);
	}
	else
	{
		return NULL;
	}
}

size_t sizeOf(const void * _class)
{
	const struct Class ** cp = _class;

	assert(cp && *cp);

	return (*cp)->size;
}