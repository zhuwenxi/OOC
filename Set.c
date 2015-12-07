#include <stddef.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

#include "Set.h"
#include "Set_r.h"
#include "Object.h"
#include "Class.h"
#include "Class_r.h"
#include "List.h"
#include "List_r.h"
#include "String.h"
#include "String_r.h"
#include "New.h"




#define DEFAULT_SET_SIZE 10

static void * Set_ctor(void * _self, va_list * args)
{
	struct Set * self = _self;
	struct SetItem * items;
	int capacity = va_arg(*args, int);

	capacity = capacity <= 0 ? DEFAULT_SET_SIZE : capacity;

	self->items = calloc(capacity, sizeof(void *));
	self->capacity = capacity;
	self->length = 0;

	return self;
}

static void * Set_dtor(void * _self)
{
	struct Set * self = _self;
	int i;

	for (i = 0; i < self->capacity; i++)
	{
		if (self->items[i] != NULL)
		{
			delete(self->items[i]);
		}
	}

	free(self->items);

	return self;
}

static void * Set_insert(void * _self, void * _setItem)
{
	struct Set * self = cast(Set, _self);
	struct SetClass * sc =  * (struct SetClass **)self;
	int originCapcity;
	int i;

	if (self != NULL)
	{
		self->length++;

		if (self->length > self->capacity)
		{
			originCapcity = self->capacity;
			self->capacity *= 2;
			
			self->items = realloc(self->items, self->capacity * sizeof(void *));

			for (i = originCapcity; i < self->capacity; i++)
			{
				self->items[i] = NULL;
			}

		}
		
		self->items[self->length - 1] = _setItem;

		return _setItem;
	}
	else
	{
		return NULL;
	}
}

static struct String * Set_toString(const void * _self)
{
	const struct Set * self = cast(Set, _self);
	const struct String * retVal = new (String, "", 0);
	struct String * child;
	struct String * space;
	struct String * temp;
	int i;

	if (self)
	{
		for (i = 0; i < self->length; i++)
		{
			child = toString(self->items[i]);
			temp = retVal;
			space = new (String, " ", 0);

			if (child)
			{
				retVal = add(retVal, child, space, 0);
			}
			
			delete(temp);
			delete(child);
			delete(space);
		}

		return retVal;
	}
	else
	{
		return NULL;
	}
	
}

const void * Set;

void loadSet()
{
	/*if (!SetClass)
	{
		SetClass = new (Class, "SetClass", Class, sizeof(struct SetClass), ctor, SetClass_ctor, 0);
	}*/

	if (!Set)
	{
		Set = new (List, "Set", Object, sizeof(struct Set), ctor, Set_ctor, dtor, Set_dtor, insert, Set_insert, toString, Set_toString, 0);
	}
}