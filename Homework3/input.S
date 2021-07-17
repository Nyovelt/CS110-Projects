.data

# Input array
# Non-negative integers are insert operations.
# -1 is the pop operation.
# You should print the popped (smallest) item, while maintaining the heap property.
# -2 is the print heap operation.
# You should the print the internal representation (array) of the heap.
# DO NOT MODIFY THIS VARIABLE
.globl  input
input:
    #.word   0 2 13 38 16 27 21 19 1 28 15 18 14 12 35 31 9 17 25 32 36 39 5 33 29 37 3 40 24 34 8 30 10 11 22 7 20 23 26 4 6 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 
	#.word 8 11 2 25 24 1 18 7 19 12 10 6 31 3 26 22 16 21 9 29 13 14 15 28 30 4 17 23 20 5 27 0 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 
.word  5 20 29 11 3 18 8 13 9 15 7 0 1 14 23 25 19 12 10 22 31 26 17 24 16 28 6 27 21 30 2 4 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 
# Constant integer specifying the number of operations
# DO NOT MODIFY THIS VARIABLE
.globl  input_len
input_len:
.word 64

# Statically allocated array for the heap data structure
# You may assume that the maximum capacity is 32.
# Any operation that causes the array to hold more than 32 elements is an overflow.
.globl  heap
heap:
    .word   0 0  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

# Global variable that holds the current length of the heap
# You should modify this variable accordingly when inserting or popping elements.
.globl  len
len:
    .word   0