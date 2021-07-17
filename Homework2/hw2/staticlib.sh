gcc -c doubll2d.c 
ar rc liblist.a doubll2d.o
gcc -c test.c 
gcc -o staticlist doubll2d.o -L./liblist.a