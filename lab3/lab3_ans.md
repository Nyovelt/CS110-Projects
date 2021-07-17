## Ex.1
- What do the .data, .word, .text directives mean (i.e. what do you use them for)? Hint: think about the 4 sections of memory.
    - `.data`: emit .data section (if not present) and make current. .data section is global data section.
    - `.word`: 32-bit comma separated words storing.
    - `.text`: emit .text section (if not present) and make current. .text section is code section.

- Run the program to completion. What number did the program output? What does this number represent?
    - 34, The ninth fib number.
- At what address is n stored in memory? Hint: Look at the contents of the registers.
    - `0x10000010`

- Without using the “Edit” tab, have the program calculate the 13th fib number (0-indexed) by manually modifying the value of a register. You may find it helpful to first step through the code. If you prefer to look at decimal values, change the “Display Settings” option at the bottom.
    - t3 (x28) = 13 
    - After `lw t3, 0(t3)`

## Ex.2
1. `t0`
2. `t5` to source, `t6` to dest
3. 
```
loop:
	slli t3, t0, 2
	add t4, t1, t3
	lw t5, 0(t4)
	beq t5, x0, exit
	add t6, t2, t3
	sw t5, 0(t6)
	addi t0, t0, 1
	jal x0, loop
```
4. 
```
	slli t3, t0, 2
	add t4, t1, t3
```
means *(source+1)