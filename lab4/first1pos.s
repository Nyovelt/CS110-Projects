.data
shouldben1:	.asciiz "Should be -1, and firstposshift and firstposmask returned: "
shouldbe0:	.asciiz "Should be 0 , and firstposshift and firstposmask returned: "
shouldbe16:	.asciiz "Should be 16, and firstposshift and firstposmask returned: "
shouldbe31:	.asciiz "Should be 31, and firstposshift and firstposmask returned: "

.text
main:
	la	a1, shouldbe31
	jal	print_str
	lui	a1, 0x80000	# should be 31
	jal	first1posshift
	mv	a1, a0
	jal	print_int
	jal	print_space

	lui	a1, 0x80000
	jal	first1posmask
	mv	a1, a0
	jal	print_int
	jal	print_newline

	la	a1, shouldbe16
	jal	print_str
	lui	a1, 0x0010	# should be 16
	jal	first1posshift
	mv	a1, a0
	jal	print_int
	jal	print_space

	lui	a1, 0x0010
	jal	first1posmask
	mv	a1, a0
	jal	print_int
	jal	print_newline

	la	a1, shouldbe0
	jal	print_str
	li	a1, 1		# should be 0
	jal	first1posshift
	mv	a1, a0
	jal	print_int
	jal	print_space

	li	a1, 1
	jal	first1posmask
	mv	a1, a0
	jal	print_int
	jal	print_newline

	la	a1, shouldben1
	jal	print_str
	mv	a1, zero		# should be -1
	jal	first1posshift
	mv	a1, a0
	jal	print_int
	jal	print_space

	mv	a1, zero
	jal	first1posmask
	mv	a1, a0
	jal	print_int
	jal	print_newline

	li	a0, 10
	ecall

first1posshift:
	bne a1, zero, .L2
    li a0, -1
    ret
    
.L2:
	li a0 31
loop:
	blt a1, zero, endloop
    addi a0, a0, -1
    slli a1, a1, 1
    j loop
endloop:
	ret
    
first1posmask:
	bne a1, zero, .L3
    li a0, -1
    ret
    
.L3:
	li t0 0x80000000
	li a0 31
loop1:
	and t1, t0, a1
	bne t1, x0, endloop1
    srli t0, t0, 1
	addi a0, a0, -1
	j loop1
endloop1:
	ret
    
print_int:
	mv	a1, a0
	li	a0, 1
	ecall
	jr	ra

print_str:
	li	a0, 4
	ecall
	jr	ra

print_space:
	li	a1, ' '
	li	a0, 11
	ecall
	jr	ra

print_newline:
	li	a1, '\n'
	li	a0, 11
	ecall
	jr	ra