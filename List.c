#include <stddef.h>
#include <assert.h>

#include "List.h"
#include "List_r.h"
#include "Object.h"
#include "Object_r.h"
#include "Class.h"




void * search(void * _self, void * _data)
{
	const struct Object * self = cast(Object, _self);
	const struct List * class = cast(List, self->class);

	if (class)
	{
		return class->listSearch(_self, _data);
	}
	else
	{
		return NULL;
	}

}

bool insert(void * _self, void * _data)
{
	const struct Object * self = cast(Object, _self);
	const struct List * class = cast(List, self->class);

	if (class)
	{
		return class->listInsert(_self, _data);
	}
	else
	{
		return false;
	}
}

bool erase(void * _self, void * _data)
{
	const struct Object * self = cast(Object, _self);
	const struct List * class = cast(List, self->class);

	if (class)
	{
		return class->listDelete(_self, _data);
	}
	else
	{
		return false;
	}
}

bool insertAt(void * _self, void * _data, int index)
{
	const struct Object * self = cast(Object, _self);
	const struct List * class = cast(List, self->class);

	if (class)
	{
		return class->insertAt(_self, _data, index);
	}
	else
	{
		return false;
	}
}

void merge(void * _self, void * _another)
{
	const struct Object * self = cast(Object, _self);
	const struct List * class = cast(List, self->class);

	if (class)
	{
		return class->merge(_self, _another);
	}
	else
	{
		return false;
	}
}

static void * List_ctor(void * _self, va_list * _args)
{
	struct List * self = super_ctor(List, _self, _args);
	typedef void(*voidf)();
	voidf selector;
	va_list args = *_args;

	while ((selector = va_arg(args, voidf)) != 0)
	{
		voidf method = va_arg(args, voidf);

		if (selector == search)
		{
			self->listSearch = method;
		}
		else if (selector == insert)
		{
			self->listInsert = method;
		}
		else if (selector == erase)
		{
			self->listDelete = method;
		}
		else if (selector == insertAt)
		{
			self->insertAt = method;
		}
		else if (selector == merge)
		{
			self->merge = method;
		}
	}

	return self;

}

const void * List;

void loadList()
{
	if (!List)
	{
		List = new (Class, "ListClass", Class, sizeof(struct List), ctor, List_ctor, 0);
	}
}