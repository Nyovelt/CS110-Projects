#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(){
    int *a;
    a = (int *)calloc(32, sizeof(int));
    a[0] = 1; a[1] = 2;
    for(int j=0 ,  * i = a; j < 2 ; i++,  j++){
        printf("%d ", *i);
    }
}

