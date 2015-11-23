#ifndef __OBJECT_R_H__
#define __OBJECT_R_H__

#include <stdbool.h>

struct Object
{
	const struct Class * class;
};

void * Object_ctor(void * self, va_list * args);
void * Object_dtor(void * self);
bool Object_equals(const void * self, const void * another);
int Object_hash(const void * self);

#endif