#ifndef		_ENDPOINT_LIST
#define		_ENDPOINT_LIST

typedef struct _node_list
{

	struct _node_list	*next;
	struct _node_list 	*prev;
}node_list;

typedef struct _eplist
{

	node_list node;
	int port;
	char ip[16];
}eplist;

int createep( eplist **pplist);

// get first member
int epbegin(eplist *list, eplist **pplist);

// get last member
int epend(eplist *list, eplist **pplist);

// get next member
int epnext(eplist *list, eplist **pplist);

// get prev member
int epprev(eplist *list, eplist **pplist);

int pushbackep( eplist *list, eplist *newend);

int insertep();

int deleteep();

int releaselist( eplist *list);

#endif
