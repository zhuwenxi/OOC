#include "Class.h"
#include "Class_r.h"
#include "Log.h"

void * Class_ctor(void * self, va_list * args)
{
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