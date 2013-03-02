#include <time.h>
#include <stdio.h>

char * recuperarFecha()
{
	struct tm *ptr;
	time_t lt;

	lt = time(NULL);
	ptr = localtime(&lt);

	return asctime(ptr);
}

