#include "udpserver.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "printlog.h"

int udpserver_echo(int s, struct sockaddr *client);

char *logfile = "udpserverlog.log";

int start_udpserver()
{
	int ss;
	int err;
	struct sockaddr_in addr_serv;
	struct sockaddr_in addr_clie;

	ss = socket(AF_INET, SOCK_DGRAM, 0);
	if( -1 == ss)
	{
		// create socket fail
		write_err_msg(logfile, "create socket err, err code %d\n", errno);	
		return -1;
	}

	addr_serv.sin_family = AF_INET;
	addr_serv.sin_port = htons(6000);
	addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);

	err = bind(ss, (struct sockaddr*)&addr_serv, sizeof (struct sockaddr));
	if( -1 == err)
	{
		write_err_msg( logfile, "bind err, err code %d\n", errno);
		close(ss);
		return -1;
	}

	udpserver_echo( ss, (struct sockaddr*)&addr_clie);

	return 0;
}

int udpserver_echo(int s, struct sockaddr *client)
{
	int n;
	char buffer[1024];

	int len;
	while(1)
	{
		len = sizeof( struct sockaddr);
		memset(buffer, 0, 1024);
		n = recvfrom( s, buffer, 1024, 0, (struct sockaddr*)&client, &len);
		if( -1 == n)
		{
			write_err_msg( logfile, "recvfrom err, err code %d\n", errno);
			close(s);
			return -1;
		}
		else
		{
			printf( "%s", buffer);
		}
	}
}
