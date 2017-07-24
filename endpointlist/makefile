object=main.o endpoint_list.o
cc = gcc
test_list:${object}
	cc -o $@ $^
main.o:%o:%c
	cc -c $<
endpoint_list.o:%o:%c
	cc -c $<

.PHONY :clean
clean:
	rm ${object}
