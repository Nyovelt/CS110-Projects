#include<stdio.h>

int main(){
    char ** a;
    a[0][1] = "123";
    printf("%s", a[0][1]);
}