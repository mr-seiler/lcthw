CC=gcc
CFLAGS=-Wall -g

# this is getting ridiculous and there must be a better way
exercises = ex1 ex3 ex5 ex6 ex7 ex8 ex9 ex10 ex11

all: $(exercises)

clean:
	rm -f $(exercises)
