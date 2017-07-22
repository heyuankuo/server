object=test.o printlog.o tcpserver.o
gcc=cc
tmp:${object}
	cc -o $@ ${object}
test.o:%o:%c
	cc -c $< -g
printlog.o:%o:%c
	cc -c $< -g
tcpserver.o:%o:%c
	cc -c $< -g

.PHONY :clean
clean:
	rm ${object}
