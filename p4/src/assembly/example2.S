.section .text
.globl thisloop2
.type thisloop2, @function

	# The above lines declares a function that can be accessed from C code.
	# When you're implementing your own function, you make a new file in
	# this folder, copy the above 4 lines, and replace all
	# "your_function_name" to your function's name.

	# Then you can add code after the label on line 4.

	# The rest of things work the same as in Venus, except that the directive
	# ".asciiz" is removed. Use ".string" instead.

	# Also, please make sure that each assembly function has a filename with 
	# extension name ".S", not ".s". Otherwise it will not be recognized
	# by the riscv-nuclei-elf-as and will throw an error.

	# You're free to remove this function after you've read the above.


thisloop2:
        addi    sp,sp,-32              #init
        sw      ra,28(sp)              #init
        sw      s0,24(sp)#init
        addi    s0,sp,32#init
        li      a5,23#init
        sw      a5,-20(s0)#init
        j       .L2#init
.L3:
        lui     a5,%hi(j)
        sw      zero,%lo(j)(a5)
        lui     a5,%hi(j)
        lw      a5,%lo(j)(a5)
        mv      a1,a5
        lw      a0,-20(s0)
        call    get#ret
        lui     a5,%hi(j)
        li      a4,1
        sw      a4,%lo(j)(a5)
        lui     a5,%hi(j)
        lw      a5,%lo(j)(a5)
        mv      a1,a5
        lw      a0,-20(s0)
        call    get#ret
        lui     a5,%hi(j)
        li      a4,2
        sw      a4,%lo(j)(a5)
        lui     a5,%hi(j)
        lw      a5,%lo(j)(a5)
        mv      a1,a5
        lw      a0,-20(s0)
        call    get#ret
        lui     a5,%hi(j)
        li      a4,3
        sw      a4,%lo(j)(a5)
        lui     a5,%hi(j)
        lw      a5,%lo(j)(a5)
        mv      a1,a5
        lw      a0,-20(s0)
        call    get#ret
        lui     a5,%hi(j)
        li      a4,4
        sw      a4,%lo(j)(a5)
        lui     a5,%hi(j)
        lw      a5,%lo(j)(a5)
        mv      a1,a5
        lw      a0,-20(s0)
        call    get#ret
        lui     a5,%hi(j)
        li      a4,5
        sw      a4,%lo(j)(a5)
        lui     a5,%hi(j)
        lw      a5,%lo(j)(a5)
        mv      a1,a5
        lw      a0,-20(s0)
        call    get#ret
        lui     a5,%hi(j)
        li      a4,6
        sw      a4,%lo(j)(a5)
        lui     a5,%hi(j)
        lw      a5,%lo(j)(a5)
        mv      a1,a5
        lw      a0,-20(s0)
        call    get#ret
        lui     a5,%hi(j)
        li      a4,7
        sw      a4,%lo(j)(a5)#ret
        lui     a5,%hi(j)
        lw      a5,%lo(j)(a5)#ret
        mv      a1,a5
        lw      a0,-20(s0)
        call    get#ret
        lui     a5,%hi(j)
        li      a4,8
        sw      a4,%lo(j)(a5)
        lui     a5,%hi(j)
        lw      a5,%lo(j)(a5)
        mv      a1,a5
        lw      a0,-20(s0)
        call    get#ret
        lui     a5,%hi(j)
        li      a4,9
        sw      a4,%lo(j)(a5)
        lui     a5,%hi(j)
        lw      a5,%lo(j)(a5)#ret
        mv      a1,a5#ret
        lw      a0,-20(s0)
        call    get#ret
        lui     a5,%hi(j)#ret
        
.L2:
        lw      a4,-20(s0)
        li      a5,39#ret
        ble     a4,a5,.L3
        nop
        lw      ra,28(sp)
        lw      s0,24(sp)
        addi    sp,sp,32
        jr      ra#ret
