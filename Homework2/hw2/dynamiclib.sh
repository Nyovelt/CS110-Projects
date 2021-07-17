gcc -c doubll2d.c
gcc -shared -o liblist.so doubll2d.o
gcc -c test.c
gcc -o dynamiclist test.o -L./liblist.so