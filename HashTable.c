#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>

#include "HashTable.h"
#include "HashTable_r.h"
#include "LinkList.h"
#include "LinkList_r.h"
#include "List.h"
#include "List_r.h"
#include "Object.h"
#include "Object_r.h"
#include "Class.h"
#include "Class_r.h"
#include "String.h"
#include "String_r.h"
#include "New.h"




#define DEFAULT_HASH_TABLE_SIZE 701

static struct Pair * searchPair(const struct LinkList * slot, void * _key);
static struct LinkList * selectSlot(void * _self, void * _data);

static void * HashTable_ctor(void * _self, va_list * args)
{
	struct HashTable * self = cast(HashTable, _self);
	struct LinkList ** slots;
	int i;

	assert(self);

	slots = (struct LinkList **)calloc(DEFAULT_HASH_TABLE_SIZE, sizeof(struct LinkList * ));

	for (i = 0; i < DEFAULT_HASH_TABLE_SIZE; i++)
	{
		slots[i] = new (LinkList, 0);
	}

	self->slots = slots;
	
	return self;
}

static void * HashTable_dtor(void * _self)
{
	struct HashTable * self = cast(HashTable, _self);
	struct LinkList ** slots;
	int i;

	assert(self);
	assert(self->slots);

	slots = self->slots;

	for (i = 0; i < DEFAULT_HASH_TABLE_SIZE; i++)
	{
		delete(slots[i]);
	}

	free(slots);

	return self;
}

static void * Pair_ctor(void * _self, va_list * args)
{
	struct Pair * self = cast(Pair, _self);

	assert(self);

	self->key = va_arg(*args, void *);
	self->value = va_arg(*args, void *);

	return _self;
}

static void * Pair_dtor(void * _self)
{
	struct Pair * self = cast(Pair, _self);

	assert(self);

	delete(self->key);
	delete(self->value);

	return _self;
}

static void * HashTable_search(void * _self, void * _key)
{
	struct LinkList * slot = selectSlot(_self, _key);
	
	if (slot)
	{
		struct Pair * pair = searchPair(slot, _key);

		return pair;
	}
	else
	{
		return NULL;
	}
}

static bool HashTable_insert(void * _self, void * _pair)
{
	struct Pair * pair = cast(Pair, _pair);

	if (pair && pair->key && pair->value)
	{
		struct LinkList * slot = selectSlot(_self, pair->key);

		assert(slot);

		insert(slot, pair);

		return true;
	}
	else
	{
		return false;
	}
}

static bool HashTable_erase(void * _self, void * _key)
{
	struct LinkList * slot = selectSlot(_self, _key);

	if (slot)
	{
		struct Pair * pair = searchPair(slot, _key);

		if (pair)
		{
			erase(slot, pair);
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

static struct String * HashTable_toString(const void * _self)
{
	struct HashTable * self = cast(HashTable, _self);
	struct LinkList ** slots;
	struct String * slotString;
	struct String * retVal;
	struct String * prevRetVal;
	struct String * lineFeed = new (String, "\n", 0);
	int i;

	if (self)
	{
		slots = self->slots;

		if (slots)
		{
			retVal = new (String, "", 0);

			for (i = 0; i < DEFAULT_HASH_TABLE_SIZE; i++)
			{
				slotString = toString(slots[i]);

				prevRetVal = retVal;

				if (slotString)
				{
					retVal = add(retVal, slotString, lineFeed, 0);
					delete(prevRetVal);
				}

			}

			delete(lineFeed);

			return retVal;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}

static struct String * Pair_toString(const void * _self)
{
	struct Pair * self = cast(Pair, _self);

	if (self && self->key && self->value)
	{
		struct String * keyStr = toString(self->key);
		struct String * valueStr = toString(self->value);
		struct String * space = new (String, "\n", 0);
		struct String * retVal;

		retVal = add(new(String, "(KEY):\n"), keyStr, space, new(String, "(VALUE):\n"), valueStr, space, 0);

		delete(keyStr);
		delete(valueStr);
		delete(space);

		return retVal;
	}
	else
	{
		return NULL;
	}
}

static struct LinkList * selectSlot(void * _self, void * _data)
{
	struct HashTable * self = cast(HashTable, _self);
	struct LinkList ** slots;
	struct LinkList * slot;
	struct Object * data = _data;
	int index;

	assert(self);
	assert(self->slots);
	assert(data);

	slots = self->slots;
	index = hash(data) % DEFAULT_HASH_TABLE_SIZE;

	slot = slots[index];

	return slot;
}

static struct Pair * searchPair(const struct LinkList * slot, void * _key)
{
	if (slot && isA(slot, LinkList))
	{
		struct LinkListItem * head = cast(LinkListItem, slot->head);

		if (head)
		{
			struct LinkListItem * next = head;
			struct Pair * pair;

			while (next)
			{
				pair = next->data;

				if (pair && isA(pair, Pair) && equals(pair->key, _key))
				{
					return pair;
				}

				next = next->next;
			}

			return NULL;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}




const void * HashTable;

const void * Pair;

void loadHashTable()
{
	if (!HashTable)
	{
		HashTable = new (List, "HashTable", Object, sizeof(struct HashTable), ctor, HashTable_ctor, dtor, HashTable_dtor, search, HashTable_search, insert, HashTable_insert, erase, HashTable_erase, toString, HashTable_toString, 0);
	}

	if (!Pair)
	{
		Pair = new (Class, "HashTable", Object, sizeof(struct Pair), ctor, Pair_ctor, dtor, Pair_dtor, toString, Pair_toString, 0);
	}
}