gcc -c doubll2d.c 
ar rc liblist.a doubll2d.o
gcc -o staticlist doubll2d.o test.c -L./liblist.a