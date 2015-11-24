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

struct Class * super(const void * self);
void * super_ctor(const void * class, const void * self, va_list * args);

void * ctor(void * self, va_list * args);
void * dtor(void * self);

#endif