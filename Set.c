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

	if (self != NULL)
	{
		assert(sc && sc->add);

		return sc->add(_self, _setItem);
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

	self->items = calloc(capacity, sizeof(SetItem));

	return self;
}

static void * Set_dtor(void * _self)
{
	struct Set * self = _self;

	free(self->items);

	return self;
}

const void * Set;

const void * SetClass;

void loadSet()
{
	if (!SetClass)
	{
		SetClass = new (Class, "SetClass", Class, sizeof(struct SetClass), ctor, SetClass_ctor, 0);
	}

	if (!Set)
	{
		Set = new (SetClass, "Set", Object, sizeof(struct Set), ctor, Set_ctor, dtor, Set_dtor, 0);
	}
}