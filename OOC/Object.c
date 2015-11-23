#include "Object.h"
#include "Class.h"
#include "Class_r.h"
#include "Object_r.h"
#include "Log.h"

void * Object_ctor(void * self, va_list * args)
{
	log("Object_ctor()\n");
	return self;
}

void * Object_dtor(void * self)
{
	log("Object_dtor()\n");
	return self;
}

bool Object_equals(const void * self, const void * another)
{
	log("Object_equals()\n");
	return self == another;
}

int Object_hash(const void * self)
{
	log("Object_hash()\n");
	return 0;
}

const struct Class object[] =
{
	{
		{ object + 1},
		"Object",
		object,
		sizeof(struct Object),
		Object_ctor,
		Object_dtor,
		Object_equals,
		Object_hash,
	},
	{
		{ object + 1 },
		"Class",
		object,
		sizeof(struct Class),
		Class_ctor,
		Class_dtor,
		Class_equals,
		Class_hash,
	}
};

const void * const Object = object;
const void * const Class = object + 1;

// TO DO
bool equals(const void * self, const void * another);
int hash(const void * self);