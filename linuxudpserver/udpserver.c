#include "udpserver.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "printlog.h"

#define		PIDNUMB 1000
#define		BUFFERLEN		1024
#define		SERVERPORT		6000

int udpserver_echo(int s);

char *logfile = "udpserverlog.log";

int handle_connect(int s_s)
{
	struct sockaddr_in from;
	int len = sizeof from;
	int n = 0;
	char buffer[BUFFERLEN];
	time_t now;

	// main proc
	while(1)
	{
		memset( buffer, 0, BUFFERLEN);
		n = recvfrom(s_s, buffer, BUFFERLEN, 0, (struct sockaddr *)&from, &len);
		if( -1 == n)
		{
			// recvfrom err	
			write_err_msg(logfile, "recvfrom err, err code %d\n", errno);	
		}
		else if( 0 == n)
		{
			// client close
		}
		else
		{
			// recv is ok
			printf("%s", buffer);
		}
	}
}

void sig_int( int num)
{
	exit(1);
}

int start_udpserver()
{
	int ss;
	int err;
	struct sockaddr_in addr_serv;
	signal( SIGINT, sig_int);

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

	// bind server address to socket
	err = bind(ss, (struct sockaddr*)&addr_serv, sizeof (struct sockaddr));
	if( -1 == err)
	{
		write_err_msg( logfile, "bind err, err code %d\n", errno);
		close(ss);
		return -1;
	}

	// concurrent
	pid_t pid[PIDNUMB];
	int i = 0;

	memset ( pid, 0, sizeof pid);
	for( i=0;i < PIDNUMB; i++)
	{
		pid[i]  = fork();
		if( 0 == pid[i])
		{
			handle_connect(ss);
		}
	}

	while(1);

	return 0;
}
