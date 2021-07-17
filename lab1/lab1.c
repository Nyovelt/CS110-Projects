#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define getsize(x) (printf("Size of " #x ": %ld\n",(unsigned long)sizeof(x))) 

int main(){
    getsize(char);
    getsize(short);
    getsize(short int);
    getsize(int);
    getsize(long int);
    getsize(unsigned int);
    getsize(void* );
    getsize(size_t);
    getsize(float);
    getsize(double);
    getsize(int8_t);
    getsize(int16_t);
    getsize(int32_t);
    getsize(int64_t);
    getsize(time_t);
    getsize(clock_t);
    getsize(struct tm);
    getsize(NULL);
    return 0;
}
