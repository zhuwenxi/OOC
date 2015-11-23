#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <stdarg.h>
#include <stdbool.h>

// Caution: these representation file should be private to users. 
// This would rely on the "cast" function?
#include "Class_r.h"
#include "Object_r.h"

extern const void * const Object;

bool equals(const void * self, const void * another);
int hash(const void * self);

#endif