#ifndef __CLASS_R_H__
#define __CLASS_R_H__

#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>

#include "Object_r.h"

struct Class
{
	struct Object _;
	char * name;
	const struct Class * const super;
	const size_t size;
	void * (*ctor)(void * self, va_list * args);
	void * (*dtor)(void *self);
	bool (*equals)(const void * self, const void * another);
	int (*hash)(const void * self);

};

void * Class_ctor(void * self, va_list * args);
void * Class_dtor(void * self);
bool Class_equals(const void * self, const void * another);
int Class_hash(const void * self);

#endif