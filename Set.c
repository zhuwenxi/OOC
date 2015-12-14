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
#include "Iterator.h"
#include "Iterator_r.h"



/*
 * Interface:
 */
bool swap(void * _self, int one, int another)
{
	struct Set * self = cast(Set, _self);

	if (self)
	{
		if (one < self->length && another < self->length)
		{
			void * temp = self->items[one];
			self->items[one] = self->items[another];
			self->items[another] = temp;

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

int indexOf(const void * _self, const void * _token)
{
	struct Set * self = cast(Set, _self);

	assert(self);
	assert(_token);

	int index;

	for (index = 0; index < self->length; index ++)
	{
		if (_token == self->items[index])
		{
			return index;
		}
	}

	return -1;
}




#define DEFAULT_SET_SIZE 10

static void resizeCapacity(struct Set * set);

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

static struct Set * Set_clone(const struct Set * _self)
{
	struct Set * self = cast(Set, _self);
	struct Set * copy;

	if (self)
	{
		copy = new (Set, 0);
		
		struct SetIterator * iter = new (SetIterator, self, 0);
		void * data;

		for (data = start(iter); data != end(iter); data = next(iter))
		{
			insert(copy, clone(data));
		}

		delete(iter);

		return copy;
	}
	else
	{
		return NULL;
	}
}

static bool Set_equals(const void * _self, const void * _another)
{
	struct Set * self = cast(Set, _self);
	struct Set * another = cast(Set, _another);

	if (self && another)
	{
		if (self->length == another->length)
		{
			int i;

			for (i = 0; i < self->length; i++)
			{
				if (!equals(self->items[i], another->items[i]))
				{
					return false;
				}
			}

			return true;
		}
		else
		{
			return false;
		}
	}
	else if (!self && !another)
	{
		return true;
	}
	else
	{
		return false;
	}
}

static void * Set_insert(void * _self, void * _setItem)
{
	struct Set * self = cast(Set, _self);

	if (self != NULL)
	{
		self->length++;

		resizeCapacity(self);
		
		self->items[self->length - 1] = _setItem;

		return _setItem;
	}
	else
	{
		return NULL;
	}
}

static bool Set_insertAt(void * _self, void * _data, int index)
{
	struct Set * self = cast(Set, _self);
	int i;

	if (self && index >= 0 && index <= self->length)
	{
		Set_insert(_self, NULL);

		for (i = self->length - 1; i > index; i--)
		{
			self->items[i] = self->items[i - 1];
		}

		self->items[index] = _data;

		return true;
	}
	else
	{
		return false;
	}
}

static void * Set_search(void * _self, void * _data)
{
	struct Set * self = cast(Set, _self);
	struct Iterator * iterator;
	void * data;

	if (self)
	{
		iterator = new (SetIterator, self, 0);

		for (data = start(iterator); data != end(iterator); data = next(iterator))
		{
			if (equals(data, _data))
			{
				delete(iterator);

				return data;
			}
		}

		delete(iterator);

		return false;
	}
	else
	{
		return NULL;
	}
}

static void Set_merge(void * _self, void * _another, ...)
{
	struct Set * self = cast(Set, _self);
	struct Set * another = cast(Set, _another);
	struct SetIterator * iter;
	void * data;
	

	if (self && another)
	{
		iter = new (SetIterator, another);

		for (data = start(iter); data != end(iter); data = next(iter))
		{
			if (!search(self, data))
			{
				insert(self, clone(data));
			}
			
		}
	}

}

static struct Object * Set_start(struct Iterator * iter)
{
	struct Set * set = iter->data;

	assert(set);

	return set->items[0];
}

static struct Object * Set_end(struct Iterator * iter)
{
	struct Set * set = iter->data;

	assert(set);

	return set->items[set->length];
}

static struct Object * Set_next(struct Iterator * iter)
{
	struct Set * set = iter->data;

	assert(set);

	iter->index = iter->index + 1;

	return set->items[iter->index];
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

static void * SetIterator_ctor(void * _self, va_list * args)
{
	return super_ctor(SetIterator, _self, args);
}

static void * SetIterator_dtor(void * _self)
{
	return super_dtor(SetIterator, _self);
}

static void resizeCapacity(struct Set * set)
{
	int capacity = set->capacity;
	int i;

	if (set->length > set->capacity)
	{
		do
		{
			set->capacity = set->capacity * 2;
		} 
		while (set->length > set->capacity);
		

		set->items = realloc(set->items, set->capacity * sizeof(void *));

		for (i = capacity; i < set->capacity; i++)
		{
			set->items[i] = NULL;
		}
	}
}

const void * Set;

const void * SetIterator;

void loadSet()
{
	if (!Set)
	{
		Set = new (List, "Set", Object, sizeof(struct Set), ctor, Set_ctor, dtor, Set_dtor, insert, Set_insert, insertAt, Set_insertAt, toString, Set_toString, search, Set_search, merge, Set_merge, clone, Set_clone, equals, Set_equals, 0);
	}

	if (!SetIterator)
	{
		SetIterator = new (IteratorClass, "SetIterator", Iterator, sizeof(struct SetIterator), start, Set_start, end, Set_end, next, Set_next,0);
	}
}