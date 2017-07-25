#ifndef		_PRINTLOG_H
#define		_PRINTLOG_H

int write_log(char *filename, int rows, char *argv[]);

int write_log_wl(char *filename, char *s);

int write_err_msg(char *filename, char *msg_format, int code);
#endif 
