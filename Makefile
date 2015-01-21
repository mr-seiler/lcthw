CFLAGS=-Wall -g

all: ex1

ex1:
	cc $(CFLAGS) ex1.c -o ex1

clean:
	rm -f ex1
