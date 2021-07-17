## Exercise 1: Bit Operations

## Exercise 2: Catch those bugs!

1. setting a breakpoint at main
- b { 行号 }
2. using gdb's run command
- r
3. using gdb's single-step command
- n

1. How do you pass command line arguments to a program when using gdb?
- r [args]
2. How do you set a breakpoint which only occurs when a set of conditions is true (e.g. when certain variables are a certain value)?
- b [sth] if [cond]
3. How do you execute the next line of C code in the program after stopping at a breakpoint?
- n
4. If the next line of code is a function call, you'll execute the whole function call at once if you use your answer to #3. (If not, consider a different command for #3!) How do you tell GDB that you want to debug the code inside the function instead? (If you changed your answer to #3, then that answer is most likely now applicable here.)
- s
5. How do you resume the program after stopping at a breakpoint?
- c
6. How can you see the value of a variable (or even an expression like 1+2) in gdb?
- p [expr]
7. How do you configure gdb so it prints the value of a variable after every step?
- display
8. How do you print a list of all variables and their values in the current function?
- info variables
10. How do you exit out of gdb?
- q

## Exercise 3: Memory Management
1. **ACTION ITEM**: Explain why `bad_vector_new()` and `also_bad_vector_new()` are bad and fill in the functions `vector_new()`, `vector_get()`, `vector_delete()`, and `vector_set()` in `vector.c` so that our test code vector-test.c runs without any memory management errors.
- `bad_vector_new()` Do not allocate memories for the struct. v will be unacccessable not illeagal to visit when current action record is destroyed .
- `also_bad_vector_new()` do not see the struct as a pointer, as it can't allocat memory for `v.data`. v will be unacccessable not illeagal to visit when current action record is destroyed .

- `valgrind`
    - `--tool=memcheck` 指定Valgrind使用的工具。Valgrind是一个工具集，包括Memcheck、Cachegrind、Callgrind等多个工具。memcheck是缺省项。
    - `--leak-check` 指定如何报告内存泄漏（memcheck能检查多种内存使用错误，内存泄漏是其中常见的一种），可选值有:
        - no 不报告
        - summary 显示简要信息，有多少个内存泄漏。summary是缺省值。
        - yes 和 full 显示每个泄漏的内存在哪里分配。

