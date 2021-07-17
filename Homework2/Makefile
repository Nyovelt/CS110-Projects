# CC=gcc
# CFLAGS= -std=c99

# doubll2d.o: doubll2d.c doubll2d.h
# 	${CC} ${CFLAGS} doubll2d.c -o  doubll2d.o

objects = test.o doubll2d.o
test: $(objects)
	gcc $(objects) -g -o test -std=c89
	rm -f *.o
test.o: test.c
doubll2d.o: doubll2d.c doubll2d.h
