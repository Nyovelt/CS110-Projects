# DO NOT REMOVE THIS LINE WHEN SUBMITTING
.import input.S
.data
    space:                  .asciiz  " "   # space
	line:                   .asciiz "\n"   # line           
.text
.globl	main # main
main:
	la t0, input_len
	lw t0, 0(t0) # input_len
	addi t1, zero, 0 # i = 0
	la t2, input # t2 = &input
	# for i in input
	1_loop:
		la t2, input # t2 = &input
		beq t1, t0, exit_1 # until
		# read input[i]
		slli t3, t1, 2 # t3 = 2*i
		add t3, t3, t2 # t3 = &input[i]
		lw t3, 0(t3)
		#pop
		li t4, -1# when input == -1
		beq  t3, t4, pop # when input == -1
		#print
		li t4, -2# when input == -2
		beq t3, t4, print# when input == -2
		# push
		mv a1, t3
		jal ra, push # push
		addi t1, t1, 1 # ++i
		j 1_loop # loop
	exit_1:
		jal ra, exit # exit


pop:
	lw t2, len # len
	beq t2, zero, flow
	# print first item 
	lw a1, heap
	li a0, 1
	ecall
	# print line
	addi a0, zero, 4# print linne
	la a1 line# print linne
	ecall # print linne
	# put ahead last item and siz --
	lw t2, len # len

	addi t2, t2, -1 # --

	la t3, len
	sw t2, 0(t3) # siz -- done
	slli t2, t2, 2 # heap[siz]
	la t3, heap # exchange item 
	add t2, t2, t3 # exchange item 
	lw t2, 0(t2) # exchange item 
	sw t2, 0(t3) # exchange item 
	addi t2, zero, 1 # t2 = 1 = i
	4_loop:
		lw t3, len 
		slli t4, t2, 1 # t4 = j = 2*i
		bgt t4, t3, 4_loop_exit
		# choose larget j
		# pick heap[j]
		addi t5, t4, -1 # t6 = heap[j]
		slli t5, t5, 2 # t6 = heap[j]
		la t6, heap # t6 = heap[j]
		add t5, t5, t6 # t6 = heap[j]
		lw t6, 0(t5) # t6 = heap[j]	
		mv t5, t4# t5 = heap[j+1]	
		slli t5, t5, 2# t5 = heap[j+1]	
		la s3, heap# t5 = heap[j+1]	
		add t5, t5, s3# t5 = heap[j+1]	
		lw t5, 0(t5) # t5 = heap[j+1]	
		bgt t5, t6, state # if heap[j+1]	 >  heap[j]	 then nothiong happen
		addi t4, t4, 1 # j++ 
		state:
		# if heap[i] > heap[j] then swap them

		addi t3, t2, -1 #  heap[i]
		slli t3, t3, 2  #  heap[i]
		la t5, heap  #  heap[i]
		add t3, t3, t5 #  heap[i]
		lw t3, 0(t3) #  t3 := heap[i]

		addi t5, t4, -1 #  heap[j]
		slli t5, t5, 2#  heap[j]
		la t6, heap #  heap[j]
		add t5, t6, t5#  heap[j]
		mv t6, t5 # t6 := &heap[j]
		lw t5, 0(t5) #  t5 := heap[j]
		bgt t5, t3, 4_loop_exit # if heapj > heapi then continuje
		addi s3, t2, -1 #  heap[i]
		slli s3, s3, 2  #  heap[i]
		la s4, heap  #  heap[i]
		add s3, s4, s3 #  heap[i]
		
		sw t5, 0(s3)
		sw t3, 0(t6)
		add t2, zero, t4 # i = j
		j 4_loop
	4_loop_exit:
		jr ra 

print:
	la t6, heap # &heap
	lw t3, len	# length
	addi t4, zero, 0	# i = 0
	3_loop:
	beq t4, t3, exit_3_loop # until
	mv t5, t4 #heap[i]
	slli t5, t5, 2 #heap[i]
	add t5, t5, t6 #heap[i]
	# print heap[i]
	addi a0, zero, 1# print heap[i]
	lw a1, 0(t5)# print heap[i]
	ecall# print heap[i]
	# print space
	addi a0, zero, 4# print linne
	la a1 space# print linne
	ecall # print linne

	addi t4, t4, 1
	j 3_loop # loop

	exit_3_loop:
		addi a0, zero, 4# print linne
		la a1 line# print linne
		ecall # print linne
		jr ra


push:
	# size += 1
	la t2, len # size += 1
	lw t3, len# size += 1
	addi t3, t3, 1# size += 1
	sw t3, 0(t2)# size += 1
	# j = size := t3
	li t2, 32
	bgt t3, t2, flow # if size > 32 then overflow
	
	lw t2, heap # t2 = &heap
	add t4, t3, zero # t4 = i 

	2_loop:
	addi t2, zero, 1
	beq t4, t2, exit_2_loop # j < 1 exit
	srli t5, t4, 1 # t5 = j /2
	# t6 = heap[j/2]
	addi t6, t5, -1# t6 = heap[1/2 j]
	slli t6, t6, 2# t6 = heap[1/2 j]
	la t2, heap# t6 = heap[1/2 j]
	add t6, t6, t2# t6 = heap[1/2 j]
	lw t6, 0(t6) # t6 = heap[1/2 j]
	bge a1, t6, exit_2_loop # if a1 >= heap[1.2 j] then break
	# t6 = &heap[j]
	mv t5, t6 # t5 = heap[0.5j]
	addi t6, t4, -1# t6 = heap[ j]
	slli t6, t6, 2# t6 = heap[ j]
	la t2, heap# t6 = heap[j]
	add t6, t6, t2# t6 = &heap[ j]
	sw t5, 0(t6)

	srli t4, t4, 1
	j 2_loop #loop
	exit_2_loop:
		# heap[i] = a1
		la t2, heap
		addi t4, t4, -1
		slli t4, t4, 2
		add t4, t4, t2
		sw a1, 0(t4)

	jr ra



flow: 
	li a1, 1 # return 0
	li a0, 17 # return 0
	ecall # return 0

exit:
	li a1, 0 # return 0
	li a0, 17 # return 0
	ecall # return 0
