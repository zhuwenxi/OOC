#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <stdarg.h>
#include <stdbool.h>

extern const void * const Object;

bool equals(const void * self, const void * another);
int hash(const void * self);
void * clone(const void * self);
struct String * toString(const void * self);
/*
 * Dynamic Type Checking:
 */
bool isA(const void * _self, const void * class);
bool isOf(const void * _self, const void * class);
void * cast(const void * class, const void * _self);

void * classOf(const void * self);

#endif