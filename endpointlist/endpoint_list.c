#include "endpoint_list.h"
#include <stdio.h>
#include <malloc.h>
#include <stddef.h>
#include <string.h>


#define container_of(ptr, type, member) ({                      \
		        const typeof(((type *) 0)->member) *__mptr = (ptr);     \
		        (type *) ((char *) __mptr - offsetof(type, member));})

#define container_of2(ptr, type, member) ({                      \
		        (type *) ((char *) ptr - offsetof(type, member));})

/** 
 * create a new list
 * @pararm			pplist 		[out]		return a list first member
 */
int createep( eplist **pplist)
{

	eplist *plist  = (eplist *)malloc(sizeof (eplist));
	memset(plist, 0, sizeof (eplist));
	plist->node.next = NULL;
	plist->node.prev = NULL;

	*pplist = plist;
	return 0;
}

/** 
 * get first member of the list  
 */
int epbegin(eplist *list, eplist **pplist)
{
	if( NULL == pplist ||
			NULL == list)
	{
		return -1;
	}
	// get the first node
	node_list *beginnode = &(list->node); 
	while( NULL != beginnode->prev )
	{
		beginnode = beginnode->prev;
	}

	// get the member
	*pplist = container_of( beginnode, eplist, node );
	return 0;
}

/**
 * get last member 
 */
int epend(eplist *list ,eplist **pplist)
{
	if ( NULL == list || NULL == pplist)
	{
		return -1;
	}

	// get the last node 
	node_list *lastnode = &(list->node);
	while( NULL != lastnode->next)
	{
		lastnode = lastnode->next;
	}

	// get the membet
	*pplist = container_of( lastnode, eplist, node);
	return 0;

}

/**
 * get next member 
 */
int epnext(eplist *list, eplist **pplist)
{
	if( NULL == list || NULL == pplist)
	{
		return -1;
	}

	node_list *nextnode = NULL;
	// adjust exist next 
	if(NULL != list->node.next)
	{
		nextnode = list->node.next;
		*pplist = container_of( nextnode, eplist, node);
	}
	else
	{
		return -1;
	}
}

int epprev(eplist *list, eplist **pplist)
{
	
	if( NULL == list || NULL == pplist)
	{
		return -1;
	}

	node_list *prevnode = NULL;
	// adjust exist next 
	if(NULL != list->node.prev)
	{
		prevnode = list->node.prev;
		*pplist = container_of( prevnode, eplist, node);
	}
	else
	{
		return -1;
	}
}

int pushbackep(eplist *list, eplist *newend)
{
	int err = 0;
	// get lastmember
	eplist *oldend = NULL;
	err = epend(list, &oldend);
	if( 0 == err)
	{
		// SET NEW END
		oldend->node.next = &(newend->node);
		newend->node.prev = &oldend->node;
		newend->node.next = NULL;
	}
	else
	{
		return -1;
	}

	return 0;
}

int insertep()
{
	return 0;
}

int deleteep()
{
	return 0;
}

int releaselist(eplist *list)
{
	node_list *tmpnext = &(list->node);
	eplist *prevlist = NULL;

	while( NULL != tmpnext->next )
	{
		prevlist = NULL;
		tmpnext = tmpnext->next; // cache next
		prevlist = container_of( tmpnext->prev, eplist, node);

		free((void *)prevlist);
	}

	prevlist = container_of(tmpnext, eplist, node);
	free((void *)prevlist);
}
