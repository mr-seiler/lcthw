CC=gcc
CFLAGS=-Wall -g

# HEADERS = someheader.h otherheader.h


exercises = ex1 ex3 ex5 ex6 ex7 ex8

all: $(exercises)

clean:
	rm -f $(exercises)
