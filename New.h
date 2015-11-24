#ifndef __NEW_H__
#define __NEW_H__

#include <stdarg.h>

void * new(void * class, ...);
void delete(void * obj);

#endif