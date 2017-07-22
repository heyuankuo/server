#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include "printlog.h"

char *serverlog = "serverlog.log";


int process_connect_server(int sc);

int start_server()
{
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	int ss, sc; // server&client  socket desc
	int err; // error flag

	pid_t pid;

	ss = socket(AF_INET, SOCK_STREAM, 0 );
	if( ss < 0)
	{
		
		write_err_msg(serverlog, "server socket create fail, error code is %d\n", errno);
		return -1;
	}

	bzero(&server_addr, sizeof(struct sockaddr_in));
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(6000);

	err = bind(ss, (struct sockaddr*)&server_addr, sizeof (struct sockaddr));
	if( -1 == err)
	{
		
		write_err_msg(serverlog, "server socket bind fail, error code is %d\n", errno);
		return -1;
	}

	err = listen(ss, 2);
	if( -1 == err)
	{
		
		write_err_msg(serverlog, "server socket listen fail, error code is %d\n", errno);
		return -1;
	}

	for(;;)
	{
		int addrlen = sizeof (struct sockaddr);
		sc = accept(ss, (struct sockaddr*)&client_addr, &addrlen);
		if( -1 == sc)
		{
			write_err_msg(serverlog, "server socket accept fail, error code is %d\n", errno);
			return 0;
		}

		pid = fork();

		if( pid == 0)
		{
			// child process
			close(ss);
			process_connect_server(sc);

		}
		else
		{
			// father process
			close(sc);
		}
	}
	return 0;
}

int process_connect_server(int sc)
{
	// create buffer

	ssize_t size = 0;
	char buffer[1024];

	for(;;)
	{
		memset(buffer, 0, 1024);
		size = read( sc, buffer, 1024);
		if( 0 == size )
		{
			return 0;
		}
		else if(-1 == size)
		{
			
			write_err_msg(serverlog, "server socket read fail, error code is %d\n", errno);
			close(sc);
			return -1;
		}
		else
		{
			printf("%s\n", buffer);
		}
	}
	
}
