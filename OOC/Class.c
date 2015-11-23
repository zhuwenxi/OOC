#include "Class.h"
#include "Class_r.h"
#include "Log.h"

#include <stdarg.h>

void * Class_ctor(void * _self, va_list * args)
{
	struct Class * self = _self;

	self->name = va_arg(*args, char *);
	self->super = va_arg(*args, struct Class *);
	self->size = va_arg(*args, size_t);

	log("Class_ctor()\n");
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