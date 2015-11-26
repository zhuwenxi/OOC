#include <stddef.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

#include "Set.h"
#include "Set_r.h"
#include "Object.h"
#include "Class.h"
#include "Class_r.h"

#define DEFAULT_SET_SIZE 10

void * add(void * _self, void * _setItem)
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

static void * SetClass_ctor(void * _self, va_list * args)
{
	struct SetClass * self = _self;
	va_list arg = *args;
	typedef void * (*voidf)();
	voidf selector;

	super_ctor(SetClass, _self, args);

	while ((selector = va_arg(arg, voidf)) != 0)
	{
		voidf method = va_arg(arg, voidf);
		
		if (selector == add)
		{
			self->add = method;
		}
	}

	return self;
}

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

const void * Set;

const void * SetClass;

void loadSet()
{
	/*if (!SetClass)
	{
		SetClass = new (Class, "SetClass", Class, sizeof(struct SetClass), ctor, SetClass_ctor, 0);
	}*/

	if (!Set)
	{
		Set = new (Class, "Set", Object, sizeof(struct Set), ctor, Set_ctor, dtor, Set_dtor, 0);
	}
}