gcc -c doubll2d.c
gcc -fPIC -shared -o liblist.so doubll2d.c
gcc -o dynamiclist test.c -L./liblist.so