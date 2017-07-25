object=main.o udpserver.o printlog.o
cc=gcc
udpservertest:${object}
	cc -o $@ $^
${object}:%.o:%.c
	cc -c $< -g

.PHONY :clean
clean:
	rm ${object}
