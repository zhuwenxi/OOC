#include "Object.h"
#include "Class.h"
#include "Class_r.h"
#include "Object_r.h"
#include "Log.h"

#include <assert.h>

void * Object_ctor(void * self, va_list * args)
{
	log("Object_ctor()\n");
	return self;
}

void * Object_dtor(void * self)
{
	log("Object_dtor()\n");
	return self;
}

bool Object_equals(const void * self, const void * another)
{
	log("Object_equals()\n");
	return self == another;
}

int Object_hash(const void * self)
{
	log("Object_hash()\n");
	return 0;
}

static const struct Class object[] =
{
	{
		{ object + 1},
		"Object",
		object,
		sizeof(struct Object),
		Object_ctor,
		Object_dtor,
		Object_equals,
		Object_hash,
	},
	{
		{ object + 1 },
		"Class",
		object,
		sizeof(struct Class),
		Class_ctor,
		Class_dtor,
		Class_equals,
		Class_hash,
	}
};

const void * const Object = object;
const void * const Class = object + 1;

bool equals(const void * self, const void * another)
{
	log("equals()\n");
	return self == another;
}

int hash(const void * self)
{
	log("hash()\n");
	return 0;
}

struct Class * super(const void * _self)
{
	const struct Class * self = _self;

	assert(self->super);

	return self->super;
}

void * super_ctor(const void * class, const void * self, va_list * args)
{
	const struct Class * superclass = super(class);

	assert(superclass && superclass->ctor);

	return superclass->ctor(self, args);
}

void * super_dtor(const void * class, const void * self)
{
	const struct Class * superclass = super(class);

	assert(superclass && superclass->dtor);

	return superclass->dtor(self);
}

void * ctor(void * self, va_list * args)
{

}

void * dtor(void * self)
{

}

/*
* Dynamic Type Checking:
*/

bool isA(const void * _self, const void * class)
{
	return _self && classOf(_self) == class;
}

bool isOf(const void * _self, const void * _class)
{
	if (_self != NULL)
	{
		struct Class * class = classOf(_self);

		while (class != _class)
		{
			if (class != Object)
			{
				class = super(class);
			}
			else
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

void * cast(const void * class, const void * _self)
{
	if (isOf(_self, class))
	{
		return _self;
	}
	else
	{
		return NULL;
	}
}

void * classOf(const void * self)
{
	const struct Object * obj = self;

	assert(obj && obj->class);

	return obj->class;
}
