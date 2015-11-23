#ifndef __NEW_H__
#define __NEW_H__

#include <stdarg.h>

void * new(void * class, ...);
void delete(void * obj);

void * ctor(void * self, va_list *args);
void * dtor(void * self);

#endif