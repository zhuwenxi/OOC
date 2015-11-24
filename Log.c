#include "Log.h"

#include "stdio.h"

static bool debug_tag = false;

void set_debug_tag(bool tag)
{
	debug_tag = tag;
}

void log(char *msg)
{
	if (debug_tag)
	{
		printf(msg);
	}
}