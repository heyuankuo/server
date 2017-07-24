#include <stdio.h>
#include "endpoint_list.h"

int main(int argc, char *argv[])
{
	eplist *list = NULL;
	createep(&list);
	
	list->port = 6000;

	releaselist(list);
	return 0;
}
