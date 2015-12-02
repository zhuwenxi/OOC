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




#define DEFAULT_HASH_TABLE_SIZE 701

static struct LinkList * selectSlot(void * _self, void * _data);

static void * HashTable_ctor(void * _self, va_list args)
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

static void * HashTable_search(void * _self, void * _data)
{
	struct LinkList * slot = selectSlot(_self, _data);

	return search(slot, _data);
}

static bool HashTable_insert(void * _self, void * _data)
{
	
	struct LinkList * slot = selectSlot(_self, _data);

	assert(slot);

	insert(slot, _data);

	return true;
}

static bool HashTable_erase(void * _self, void * _data)
{
	void * data = HashTable_search(_self, _data);
	struct LinkList * slot = selectSlot(_self, _data);

	if (data)
	{
		return erase(slot, data);
	}
	else
	{
		return false;
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

const void * HashTable;

void loadHashTable()
{
	if (!HashTable)
	{
		HashTable = new (List, "HashTable", Object, sizeof(struct HashTable), ctor, HashTable_ctor, dtor, HashTable_dtor, search, HashTable_search, insert, HashTable_search, erase, HashTable_erase, 0);
	}
}