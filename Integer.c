#include "Integer.h"
#include "Integer_r.h"
#include "String.h"
#include "String_r.h"
#include "Class.h"
#include "Class_r.h"
#include "Object.h"
#include "Object_r.h"
#include "New.h"

#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>



const void * Integer;

static void * Integer_ctor(void * _self, va_list * args)
{
	struct Integer * self = cast(Integer, _self);

	assert(self);

	int value = va_arg(*args, int);

	self->value = value;

	return self;
}

static struct String * Integer_toString(const void * _self)
{
	struct Integer * self = cast(Integer, _self);

	assert(self);

	return NULL;
}




void loadInteger()
{
	if (!Integer)
	{
		Integer = new (Class, "Integer", Object, sizeof(struct Integer), ctor, Integer_ctor, toString, Integer_toString, 0);
	}
}