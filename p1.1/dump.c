#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
int translate_num(long int* output, const char* str, long int upper_bound,
    long int lower_bound) {
    /* YOUR CODE HERE */
    char* end_ptr;
    long int res;
    if (!str || !output) {
        return -1;
    }
    res = strtol(str, &end_ptr, 0);
    if (*end_ptr != '\0') {
        return -1;
    }
    if (res > upper_bound || res < lower_bound) {
        return -1;
    }
    *output = res;
    return 0;
}

int main(){
    // char a[20] = "-12";
    char a[20] = "0x61";
    long int b = 0 ;
    translate_num(&b, a, 99999999, -99999);
    printf("%ld", b);
}