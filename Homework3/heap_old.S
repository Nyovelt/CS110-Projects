# DO NOT REMOVE THIS LINE WHEN SUBMITTING
.import input.S
.data
    space:                  .asciiz  " "   # space
	line:                   .asciiz "\n"   # line           
.text
.globl	main # main
main:
	la t0, input # input[]
	li t1, 0 # i = 0
	lw t2, input_len # t2 = input_len
	.mainloop:
		beq t1, t2, .mainloopexit # if(t1 == t2)
		slli t3, t1, 2 # t3 = &input[i]
		add t3, t0, t3 # t3 += t0
		lw t3, 0(t3)  # t3 = input[i]

		# pop
		li t4, -1 # t4 = -1
		beq t3, t4, pop  #input -1

		# print
		li t4, -2 # t4 = -2 
		beq t3, t4, print #input -2

		mv a1, t3 # a = input[i]
		jal ra, push  # push(a1)

		addi t1, t1, 1 # t1++
		j .mainloop

	.mainloopexit:
		# exit with no error
		mv	a1, zero # a1 = 0
		li	a0, 17 # a0 =17
		ecall # exit

push: 
	# ++size = j
	la t3 len# size
	lw t4 len# size
	addi t4, t4, 1 # t4 = size
	li t5, 33 # t5 = 33



	beq t4, t5, error # size != 32
	sw t4, 0(t3) #size = t4

	la t3 heap # &heap
	lw t4 len  # size
	
	# for (; j != 1 && e < heap[j / 2]; j /= 2)
	push_loop:
	li t5, 1	# t5 = 1
	beq t4, t5, exit_push_loop	# j!=1
	li t5, 2 # t5 = 2
	divu t6, t4, t5 # t6 = j/2
	addi t6, t6, -1 # t6 -- 
	slli t6, t6, 2  # t6 *= 2
	add t6, t3, t6 # t6 += t3
	lw t6 0(t6) # t6 = heap[j/2]
	bgt a1, t6, exit_push_loop # if a1 > t6 then exit
	
	# heap[j] = heap[j / 2];
	mv t5 t4 # t5 = j
	addi t5, t5, -1 # t5--
	slli t5, t5, 2 # t5 *= 2
	add t5, t3, t5 # t5 = &heap[j]
	sw t6, 0(t5) # heap[j] = heap[j / 2];

	# mv 		s6, a1
	# li      a0, 1
    # mv      a1, t6
    # ecall
	# mv a1,s6
	
	li t6, 2 # j/=2
	divu t4, t4, t6 # t4 /= t6
	j push_loop # while()
	
	exit_push_loop: # heap[j] = a1;
		la t3 heap
		addi t4, t4, -1 # t4--
		slli t4, t4, 2 # t4 * 4
		add t4, t4, t3	# t4 + heap
		sw a1 0(t4) # 
	jr ra #
	

pop:
	# int ans = heap[1];

	# print first
	lw t3, len # t3 = size
	beq t3, zero, error # ==0 -> underbuff
	li a0, 1 # a0 = 1
	lw a1, heap	# a1 = &heap
	ecall	# print
	li a0, 4 #
	la a1, line #
	ecall # print

	addi t3, t3, -1	# size--
	la t4 len # t4 = siz
	sw t3, 0(t4) # siz 

	# heap[1] = heap[size];
	la t5, heap # heap
	la s5 heap	# heap
	slli t3, t3, 2 # *2
	add t3, t3, t5 #t3 = &heap[siz]
	lw t4, 0(t3) # siz
	sw t4, 0(t5)	# siz

	lw t6 len
	li t3, 1 # i=1
	loop_pop:
		slli t4, t3, 1 # j = 2 * t3
		lw t6 len
		bgt t4, t6, exit_loop_pop # if 2*t3 > size then exit
		# if(heap[j] > heap[j+1] && j+1<=siz){
        #     j++;
        # }
		addi t5, t4, 1 # t5 := j+1 t4:= j
		bgt t5, t6, .L1 # if j+1 > siz then .L1
		mv s3 t4 #s3:=j
		mv s4 t5 #s4:=j+1
		# heap[j] & heap[j+1]
		addi s3, s3, -1# heap[j] & heap[j+1]
		addi s4, s4, -1 # 
		slli s3, s3, 2# heap[j] & heap[j+1]
		slli s4, s4, 2# heap[j] & heap[j+1]
		add s3, s5, s3# heap[j] & heap[j+1]
		add s4, s5, s4# heap[j] & heap[j+1]
		# heap[j] > heap[j+1]
		lw s3, 0(s3) # heap[j]
		lw s4, 0(s4) # heap[j+1]

		blt s3, s4, .L1 # if s3 < s4 then .L1

		addi t4, t4, 1 # j++;
		.L1:
		# if (heap[j] > heap[i]) break; s3:= heap[j]
		mv s4, t3 # s4 = i
		addi s4, s4, -1
		slli s4, s4, 2
		la s5 heap
		add s4, s4, s5 # heap[i] := s4
		lw s4, 0(s4)
		mv s3 t4 #s3:=j
		addi s3, s3, -1# heap[j] & heap[j+1]
		slli s3, s3, 2# heap[j] & heap[j+1]
		add s3, s5, s3# heap[j] & heap[j+1]
		lw s3, 0(s3)
		bgt s3, s4, exit_loop_pop # heap[j] > heap[i] then exit

		# swap(heap[i], heap[j]); s3:= heap[j] s4:= heap[i] t4 := j t3 := i
		mv t6, t3# t6 = &heap[i]
		mv t5, t4# t5 = &heap[j]
		addi t6, t6, -1# t6 = &heap[i]
		addi t5, t5, -1# t5 = &heap[j]
		slli t6, t6, 2# t6 = &heap[i]
		slli t5, t5, 2# t5 = &heap[j]
		add t6, t6, s5 # t6 = &heap[i]
		add t5, t5, s5 # t5 = &heap[j]
		lw s3, 0(t5)# exchange
		lw s4, 0(t6)# exchange
		sw s4, 0(t5)# exchange
		sw s3, 0(t6)# exchange
		# i *= 2
		
		mv t3 t4
		j loop_pop
	exit_loop_pop:
		jr ra


exit_pop:	
	jr ra

print: 
	# print array
	la t3 heap # A for A[0]
	lw t4 len
	li t5, 0 # t2 for i
	printloop:
		beq t4, t5, printloopexit # break
		slli t6, t5, 2 # heap[i]
		add t6, t3, t6# heap[i]
		lw t6, 0(t6)# heap[i]
		addi sp, sp, -4# heap[i]
        li      a0, 1# print
        mv      a1, t6# print
        ecall

        # print space
        li      a0, 4 # print
        la      a1, space # print
        ecall	# print

		addi t5, t5, 1 #print
		j printloop

	printloopexit:
			li a0, 4 #
		la a1, line #
		ecall # print
		jr ra # ret
		
exit:
	# exit with no error
	mv	a1, zero # ret
	li	a0, 17# ret
	ecall# ret

error:
	# exit with  error
	li 	a1, 1	# err
	li	a0, 17# err
	ecall # err
