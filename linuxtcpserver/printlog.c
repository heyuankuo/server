#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "printlog.h"
#include <string.h>

int write_log(char *filename, int rows, char *argv[])
{
	// check log_file is exist
	int fd;
	int err = access( filename, W_OK);
	if( -1 == err)
	{
		// Create W_ok log_file
 		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IWUSR );
		if( -1 == fd)
		{
		
			printf( " log_flie create has a fail\n");
			return -1;
		}
	}
	else
	{
		// open logfile
		fd = open(filename, O_WRONLY | O_APPEND );
		if( -1 == fd)
		{
			printf( " log_flie open has a fail\n");
			return -1;
		}
			
	}
	for(int i = 0; i < rows; ++i)
	{
		err = write(fd, argv[i], strlen(argv[i]));
		if( -1 == err )
		{
			printf( " log_write has a fail\n");
		}
	}

}

// write a line to the log
int write_log_wl(char *filename, char *s)
{
	
	return write_log(filename, 1, &s);
}

// write err message to the log
int write_err_msg(char *filename, char *msg_format, int code)
{
	char buffer[128];
	memset( buffer, 0, sizeof buffer);
	sprintf(buffer, msg_format, code);
	char *s = buffer;
	return write_log(filename, 1, &s);
}
