#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

#include "String.h"
#include "String_r.h"
#include "Object.h"
#include "Object_r.h"
#include "Class.h"




void * add(const void * _one, const void * _another, ...)
{
	struct String * one = cast(String, _one);
	struct String * another = cast(String, _another);
	struct String * next;
	size_t size;
	char * target;
	va_list args;

	if (one && another)
	{
		size = strlen(one->text) + strlen(another->text) + 1;
		target = (char *)calloc(size, sizeof(char));

		strcat_s(target, size, one->text);
		strcat_s(target, size, another->text);

		va_start(args, _another);

		while ((next = va_arg(args, struct String *)) != 0)
		{
			size = strlen(target) + strlen(next->text) + 1;
			target = (char *)realloc(target, size * sizeof(char));

			strcat_s(target, size, next->text);
		}

		va_end(args);


		return new (String, target, 0);
	}
	else
	{
		return NULL;
	}
}

static void * String_ctor(void * _self, va_list * args)
{
	struct String * self = super_ctor(Object, _self, args);

	char * text = va_arg(*args, char *);
	int length = va_arg(*args, int);

	int i;

	assert(text != NULL);

	if (length == 0)
	{
		length = strlen(text);
	}
	else
	{
		if (length > strlen(text))
		{
			length = strlen(text);
		}
	}

	self->text = calloc(length + 1, sizeof(char));

	for (i = 0; i < length; i++)
	{
		self->text[i] = text[i];
	}

	self->text[i] = '\0';

	return self;
}

static void * String_dtor(void * _self)
{
	struct String * self = _self; 
	
	free(self->text);

	self = super_dtor(Object, self);

	return self;
}

static int String_hash(const void * _self)
{
	struct String * self = cast(String, _self);
	size_t size;
	int i;
	int hashCode = 0;

	if (self)
	{
		size = strlen(self->text);

		for (i = 0; i < size; i++)
		{
			hashCode = 128 * hashCode + self->text[i];
		}
	}
	
	return hashCode;
}

static bool String_equals(const void * _self, const void * _another)
{
	struct String * self = cast(String, _self);
	struct String * another = cast(String, _another);

	return self && another && !strcmp(self->text, another->text);
}

static void * String_clone(const void * _self)
{
	struct String * self = cast(String, _self);

	return new (String, self->text, 0);
}

static struct String * String_toString(const void * _self)
{
	struct String * self = cast(String, _self);

	if (self)
	{
		return new (String, self->text, strlen(self->text), 0);
	}
	else
	{
		return NULL;
	}
}


const void * String;

void loadString()
{
	if (!String)
	{
		String = new (Class, "String", Object, sizeof(struct String), ctor, String_ctor, dtor, String_dtor, toString, String_toString, hash, String_hash, equals, String_equals, clone, String_clone, 0);
	}
}