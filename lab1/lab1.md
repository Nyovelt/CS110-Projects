## Exercise 3: Binary Alphabet

- The pattern is letter 'A'
- 二进制数字:
    - 6
    - 9
    - 15
    - 9
    - 9
- 十六进制数字:
    - 6
    - 9
    - F
    - 9
    - 9
- 1,1,9,9,6:
    - 0 0 0 1
    - 0 0 0 1
    - 1 0 0 1
    - 1 0 0 1
    - 0 1 1 0
    - It's 'J'
- 0xF8F88
    - 1 1 1 1
    - 1 0 0 0 
    - 1 1 1 1
    - 1 0 0 0
    - 1 0 0 0
    - It's 'F'
- B
    - 0x65656
- N
    - 0x575

## Exercise 4: 1,000 $1 Bills
- 1
- 2
- 4
- 8
- 16
- 32
- 64
- 128
- 256
- 489

## Exercise 5: Sizes

```C

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

```

