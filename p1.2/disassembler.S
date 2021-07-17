.import input.S
# 输出寄存器
# 用之前要 set  a0 
# 调用时使用 jal                    !!!!!!!!!!!!
.data:
    LR:                  .asciiz  "("
    RR:                  .asciiz  ")"

print_reg:  # x0 mat 00 to x31 mat 31
    # a0 是传来匹配的数 t0是对应数字
    li t0, 0            # x0 <-- 0
    beq a0, t0, xx0     #match
    li t0, 1            # x0 <-- 0
    beq a0, t0, xx1     #match
    li t0, 2            # x0 <-- 0
    beq a0, t0, xx2     #match
    li t0, 3            # x0 <-- 0
    beq a0, t0, xx3     #match
    li t0, 4            # x0 <-- 0
    beq a0, t0, xx4     #match
    li t0, 5            # x0 <-- 0
    beq a0, t0, xx5     #match
    li t0, 6            # x0 <-- 0
    beq a0, t0, xx6     #match
    li t0, 7            # x0 <-- 0
    beq a0, t0, xx7     #match
    li t0, 8            # x0 <-- 0
    beq a0, t0, xx8     #match
    li t0, 9            # x0 <-- 0
    beq a0, t0, xx9     #match
    li t0, 10           # x0 <-- 0
    beq a0, t0, xx10    #match
    li t0, 11           # x0 <-- 0
    beq a0, t0, xx11    #match
    li t0, 12           # x0 <-- 0
    beq a0, t0, xx12    #match
    li t0, 13           # x0 <-- 0
    beq a0, t0, xx13    #match
    li t0, 14           # x0 <-- 0
    beq a0, t0, xx14    #match
    li t0, 15           # x0 <-- 0
    beq a0, t0, xx15    #match
    li t0, 16           # x0 <-- 0
    beq a0, t0, xx16    #match
    li t0, 17           # x0 <-- 0
    beq a0, t0, xx17    #match
    li t0, 18           # x0 <-- 0
    beq a0, t0, xx18    #match
    li t0, 19           # x0 <-- 0
    beq a0, t0, xx19    #match
    li t0, 20           # x0 <-- 0
    beq a0, t0, xx20    #match
    li t0, 21           # x0 <-- 0
    beq a0, t0, xx21    #match
    li t0, 22           # x0 <-- 0
    beq a0, t0, xx22    #match
    li t0, 23           # x0 <-- 0
    beq a0, t0, xx23    #match
    li t0, 24           # x0 <-- 0
    beq a0, t0, xx24    #match
    li t0, 25           # x0 <-- 0
    beq a0, t0, xx25    #match
    li t0, 26           # x0 <-- 0
    beq a0, t0, xx26    #match
    li t0, 27           # x0 <-- 0
    beq a0, t0, xx27    #match
    li t0, 28           # x0 <-- 0
    beq a0, t0, xx28    #match
    li t0, 29           # x0 <-- 0
    beq a0, t0, xx29    #match
    li t0, 30           # x0 <-- 0
    beq a0, t0, xx30    #match
    li t0, 31           # x0 <-- 0
    beq a0, t0, xx31    #match

change_reg:

xx0:                # print x0
    li a1, 'x'      # x
    li a0, 11       # print char
    ecall           # ecall
    li a1, 0        # 0
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx1:                # print ra
    li a1, 'r'      # r
    li a0, 11       # print char
    ecall           # ecall
    li a1, 'a'        # a
    li a0, 11        # print char
    ecall           # ecall
    jr ra     # end
xx2:                # print sp
    li a1, 's'      # s
    li a0, 11       # print char
    ecall           # ecall
    li a1, 'p'       # p
    li a0, 11       # print int
    ecall           # ecall
    jr ra     # end
xx3:                # print gp
    li a1, 'g'      # x
    li a0, 11       # print char
    ecall           # ecall
    li a1, 'p'        # 0
    li a0, 11        # print int
    ecall           # ecall
    jr ra     # end
xx4:                # print x0
    li a1, 't'      # x
    li a0, 11       # print char
    ecall           # ecall
    li a1, 'p'        # 0
    li a0, 11        # print int
    ecall           # ecall
    jr ra     # end
xx5:                # print t0
    li a1, 't'      # x
    li a0, 11       # print char
    ecall           # ecall
    li a1, 0        # 0
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx6:                # print t1
    li a1, 't'      # x
    li a0, 11       # print char
    ecall           # ecall
    li a1, 1        # 0
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx7:                # print x0
    li a1, 't'      # t
    li a0, 11       # print char
    ecall           # ecall
    li a1, 2        # 2
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx8:                # print s0
    li a1, 's'      # x
    li a0, 11       # print char
    ecall           # ecall
    li a1, 0        # 0
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx9:                # print s1
    li a1, 's'      # x
    li a0, 11       # print char
    ecall           # ecall
    li a1, 1        # 0
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx10:                # print a0
    li a1, 'a'      # a
    li a0, 11       # print char
    ecall           # ecall
    li a1, 0        # 0
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx11:                # print a1
    li a1, 'a'      # x
    li a0, 11       # print char
    ecall           # ecall
    li a1, 1        # 0
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx12:                # print a2
    li a1, 'a'      # a
    li a0, 11       # print char
    ecall           # ecall
    li a1, 2        # 2
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx13:                # print a3
    li a1, 'a'      # a
    li a0, 11       # print char
    ecall           # ecall
    li a1, 3        # 0
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx14:                # print a4
    li a1, 'a'      # x
    li a0, 11       # print char
    ecall           # ecall
    li a1, 4        # 4
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx15:                # print a5
    li a1, 'a'      # a
    li a0, 11       # print char
    ecall           # ecall
    li a1, 5        # 5
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx16:                # print a6
    li a1, 'a'      # a
    li a0, 11       # print char
    ecall           # ecall
    li a1, 6        # 6
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx17:                # print a7
    li a1, 'a'      # a
    li a0, 11       # print char
    ecall           # ecall
    li a1, 7        # 7
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx18:                # print s2
    li a1, 's'      # s
    li a0, 11       # print char
    ecall           # ecall
    li a1, 2        # 2
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx19:                # print s3
    li a1, 's'      # s
    li a0, 11       # print char
    ecall           # ecall
    li a1, 3        # 3
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx20:                # print s4
    li a1, 's'      # s
    li a0, 11       # print char
    ecall           # ecall
    li a1, 4        # 4
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx21:                # print s5
    li a1, 's'      # s
    li a0, 11       # print char
    ecall           # ecall
    li a1, 5        # 5
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx22:                # print s6
    li a1, 's'      # s
    li a0, 11       # print char
    ecall           # ecall
    li a1, 6        # 6
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx23:                # print s7
    li a1, 's'      # s
    li a0, 11       # print char
    ecall           # ecall
    li a1, 7        # 7
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx24:                # print s8
    li a1, 's'      # s
    li a0, 11       # print char
    ecall           # ecall
    li a1, 8        # 8
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx25:                # print s9
    li a1, 's'      # x
    li a0, 11       # print char
    ecall           # ecall
    li a1, 9        # 9
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx26:                # print s10
    li a1, 's'      # s
    li a0, 11       # print char
    ecall           # ecall
    li a1, 1        # 1
    li a0, 1        # print int
    ecall           # ecall
    li a1, 0        # 0
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx27:                # print s11
    li a1, 's'      # s
    li a0, 11       # print char
    ecall           # ecall
    li a1, 1        # 1
    li a0, 1        # print int
    ecall           # ecall
    li a1, 1        # 1
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx28:                # print t3
    li a1, 't'      # t
    li a0, 11       # print char
    ecall           # ecall
    li a1, 3        # 3
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx29:                # print t4
    li a1, 't'      # x
    li a0, 11       # print char
    ecall           # ecall
    li a1, 4        # 4
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx30:                # print t5
    li a1, 't'      # t
    li a0, 11       # print char
    ecall           # ecall
    li a1, 5        # 05
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end
xx31:                # print t6
    li a1, 't'      # t
    li a0, 11       # print char
    ecall           # ecall
    li a1, 6        # 6
    li a0, 1        # print int
    ecall           # ecall
    jr ra     # end

#################################

print_comma:#   不需要input
    li a1, ','      #comma
    li a0, 11       #print char
    ecall       #ecall
    jr ra

print_space:#   no input
    li a1, ' '  #space
    li a0, 11       #print char
    ecall 
    jr ra

print_line:#    new line
    li a1, '\n'
    li a0, 11       #print char
    ecall       #ecall
    jr ra       

print_imm:
    li t6, 2048
    blt a0, t6, L1
    li t6, 0xfff
    sub a0, a0, t6
    li t6, 1
    sub a0, a0, t6
    L1:
    mv a1, a0   # get
    li a0, 1    # print int
    ecall 
    jr ra

print_imm_sb:
    # mv a1, a0   # get
    # li a0, 1        # print int
    # ecall           # ecall
    li t6, 2048
    blt a0, t6, L7
    li t6, 0x1fff
    sub a0, a0, t6
    li t6, 1
    sub a0, a0, t6
    L7:
    mv a1, a0   # get
    li a0, 1    # print int
    ecall 
    jr ra

print_imm_j:
    li t6 0xffffe
    blt a0, t6, L3
    li t6, 0x1fffff
    sub a0, a0, t6
    li t6, 1
    sub a0, a0, t6
    L3:
    mv a1, a0   # get
    li a0, 1    # print int
    ecall 
    jr ra


print_imm_u:
    mv a1, a0   # get
    li a0, 1    # print int
    ecall 
    jr ra

print_LR:
    li      a0, 11
    li      a1, 40
    ecall 
    jr ra  


print_RR:
    li      a0, 11
    li      a1, 41
    ecall 
    jr ra  

# a0 寄存器中直接传机器码 mask截取后七位在函数中一并执行
# print instruction
match_opcode_and_print_line:
    li t0, 127      #后七位的mask
    and t0, a0, t0  # t0< == get opcode
    # R- type
    li t1, 0x33     # opcode ==  0x33   
    beq t0, t1, rtype_print     # print rtype add, or, slt, sltu, sll
    # I- type
    li t1, 0x67     # opcode == 0x67
    beq t0, t1, itype_0x67_print #print itype 0x67
    li t1, 0x13     # opcode == 0x13
    beq t0, t1, itype_0x13_print # print itype0x13
    li t1, 0x03     # opcode == 0x03
    beq t0, t1, itype_0x03_print # print itype0x03
    # S- type       
    li t1, 0x23     # opcode == 0x23
    beq t0, t1, stype_print     #print stype sb, sw
    # SB - type
    li t1, 0x63     #opcode == 0x63
    beq t0, t1, sbtype_print    #print sbtype bne blt bge beq
    # UJ - type
    li t1, 0x6f
    beq t0, t1, ujtype_print    #print ujtype jal
    # U -type 
    li t1, 0x37
    beq t0, t1, utype_print     #pritn utype lui


# match type
# 调用前 要先 a0 = 一行机器码
rtype_print: #!!这里没有判 funct7 的情况，因为rtype需要写的funct7都是0
    lw a0, -4(s11)
    lw a1, -4(s11)

    li t0, 7   #后3位的mask
    srli a7, a0, 12 # 右移12位
    and t0, a7, t0  # t0 == fucnt3
    # s1 s2 s3 对应 rs1 rs2 rd
    # 取rs2      s2 == rs2
    li t2, 31           # t2 == 后5位的mask
    srli a7, a0, 20     # a7 ==  a0右移20位 
    and s2, a7, t2      # rs2 ==> s2
    # 取rs1      s1 == rs1
    # t2 == 31
    srli a7, a0, 15     # a7 == a0 右移15位
    and s1, a7, t2      # rs1 ==> s1
    # 取rd
    # t2 == 31
    srli a7, a0, 7      # a7 == a0 右移7位
    and s3, a7, t2      # rd ==> s3

    # @!!!!!!!!!!!!!!!!!!!写到这里了
    # 这里应该开始调用 print_reg 
    # 后面每一个也都要写 匹配寄存器然后 pirnt reg打印，记得总监加comma，结尾加print_line(这个函数还没写)
    

    # 取完fucnt3 开始匹配
    li t1, 0x0      # add
    beq t0, t1, add_print   # print add
    li t1, 0x6      # or
    beq t0, t1, or_print    # print or
    li t1, 0x2      # slt
    beq t0, t1, slt_print   # print slt
    li t1, 0x3      # sltu
    beq t0, t1, sltu_print  # print sltu
    li t1, 0x1      # sll
    beq t0, t1, sll_print   # print sll


print_itype_0x2_reg: 
    addi sp, sp, -4
    sw ra, 0(sp)
    lw a0, -4(s11)
    li t2, 31           # t2 == 后5位的mask
    srli a7, a0, 20     # a7 ==  a0右移20位 
    mv s2, a7           # imm ==> s2
    # 取rs1      s1 == rs1
    # t2 == 31
    srli a7, a0, 15     # a7 == a0 右移15位
    and s1, a7, t2      # rs1 ==> s1
    # 取rd
    # t2 == 31
    srli a7, a0, 7      # a7 == a0 右移7位
    and s3, a7, t2      # rd ==> s3

    mv a0, s3       # a0 == rd
    jal print_reg
    jal print_comma
    jal print_space
    mv a0, s2       # a0 == rs2
    jal print_imm   
    jal print_LR
    mv a0, s1       # a0 == rs1
    jal print_reg
    jal print_RR
    jal print_line
    j next  



print_itype_0x2_reg_u: 
    addi sp, sp, -4
    sw ra, 0(sp)
    lw a0, -4(s11)
    li t2, 31           # t2 == 后5位的mask
    srli a7, a0, 20     # a7 ==  a0右移20位 
    mv s2, a7           # imm ==> s2
    # 取rs1      s1 == rs1
    # t2 == 31
    srli a7, a0, 15     # a7 == a0 右移15位
    and s1, a7, t2      # rs1 ==> s1
    # 取rd
    # t2 == 31
    srli a7, a0, 7      # a7 == a0 右移7位
    and s3, a7, t2      # rd ==> s3

    mv a0, s3       # a0 == rd
    jal print_reg
    jal print_comma
    jal print_space
    mv a0, s2       # a0 == rs2
    jal print_imm 
    jal print_LR
    mv a0, s1       # a0 == rs1
    jal print_reg
    jal print_RR
    jal print_line
    lw ra, 0(sp)
     j next 


print_rtype_reg:
    mv a0, s3       # a0 == rd
    jal print_reg
    jal print_comma
    jal print_space
    mv a0, s1       # a0 == rs1
    jal print_reg
    jal print_comma
    jal print_space
    mv a0, s2       # a0 == rs2
    jal print_reg   
    jal print_line  #new line
    j next          # loop


# I - type print 

itype_0x67_print:   # only jalr
    j jalr_print
    

itype_0x13_print:    # itype 的判断  opcode == 0x13 addi ori
    li t0, 7   #后3位的mask
    srli a7, a0, 12 # 右移12位
    and t0, a7, t0  # t0 == fucnt3
    #addi
    li t1, 0x0      # 0x0
    beq t0, t1, addi_print  #print addi
    #ori
    li t1, 0x6      # 0x6
    beq t0, t1, ori_print   #print ori
    
itype_0x03_print:    # itype 的判断  opcode == 0x03 lb lbu lw
    li t0, 7   #后3位的mask
    srli a7, a0, 12 # 右移12位
    and t0, a7, t0  # t0 == fucnt3
    # lb 
    li t1, 0x0      #0x0
    beq t0, t1, lb_print    #print lb
    #lbu
    li t1, 0x4      #0x4
    beq t0, t1, lbu_print   #print lbu
    #lw
    li t1, 0x2      #0x2
    beq t0, t1, lw_print    #print lw
###################################################################
print_itype_0x67_13_reg:
    lw a0, -4(s11)               # a0 = input[0]
    # s1 s2 s3 对应 rs1 rs2 rd
    # 取rs2      s2 == rs2
    li t2, 31           # t2 == 后5位的mask
    srli a7, a0, 20     # a7 ==  a0右移20位 
    mv s2, a7           # imm ==> s2
    # 取rs1      s1 == rs1
    # t2 == 31
    srli a7, a0, 15     # a7 == a0 右移15位
    and s1, a7, t2      # rs1 ==> s1
    # 取rd
    # t2 == 31
    srli a7, a0, 7      # a7 == a0 右移7位
    and s3, a7, t2      # rd ==> s3

    mv a0, s3       # a0 == rd
    jal print_reg
    jal print_comma
    jal print_space
    mv a0, s1       # a0 == rs1
    jal print_reg
    jal print_comma
    jal print_space
    mv a0, s2       # a0 == rs2
    jal print_imm   
    jal print_line  #new line
    j next          # loop




print_stype_reg: 
    addi sp, sp, -4
    sw ra, 0(sp)
    lw a0, -4(s11)
    mv t0, a0
    srli t0, t0, 20
    andi t0, t0, 0b11111
    mv s1, t0

    mv t0, a0
    srli t0, t0, 7
    andi t0, t0, 0b11111
    add s2, x0, t0
    mv t0, a0
    srli t0, t0, 25
    andi t0, t0, 0b1111111
    slli t0, t0, 5
    add s2, s2, t0


    mv t0, a0
    srli t0, t0, 15
    andi t0, t0, 0b11111
    mv s3, t0

    mv a0, s1
    jal print_reg
    jal print_comma
    jal print_space
    mv a0, s2
    jal print_imm
    jal print_LR

    mv a0, s3
    jal print_reg

    jal print_RR
    jal print_line
    j next


print_sbtype_reg: 
    lw a0, -4(s11)               # a0 = input[i]
    # 取 rs2    
    li t2, 0b11111 #后五位
    srli a7, a0, 20
    and s2, a7, t2  #后五位
    # 取 rs1    
    li t2, 0b11111 #后五位
    srli a6, a0, 15
    andi s1, a6, 0b11111 #后五位
    # mv a1, s2
    # li a0, 1        # print int
    # ecall           # ecall
    # 取 imm
    lw a0, -4(s11)  #1:4
    mv t0, a0
    srli t0, t0, 8
    andi t0, t0, 0b1111
    slli t0, t0, 1
    add s3, x0, t0

    mv t0, a0  # 11
    srli t0, t0, 7
    andi t0, t0, 0b1
    slli t0, t0, 11
    add s3, s3, t0

    mv t0, a0  # 10:5
    srli t0, t0, 25
    andi t0, t0, 0b111111
    slli t0, t0, 5
    add s3, s3, t0

    mv t0, a0  # 12
    srli t0, t0, 31
    andi t0, t0, 0b1
    slli t0, t0, 12
    add s3, s3, t0



    mv a0, s1  # a0 == rs1
    jal print_reg  # jump to print_reg and save position to ra
    jal print_comma

    jal print_space
    mv a0, s2       # a0 == rs2
    jal print_reg
    jal print_comma  #new comma
    jal print_space
    # li a0, 1
    # mv a1, s3
    # ecall           # ecall
    mv a0, s3
    jal print_imm_sb #print imm
    jal print_line   #new line
    j next #loop

stype_print:
    addi sp, sp, -4
    sw ra, 0(sp)
    li t0, 7   #后3位的mask
    srli a7, a0, 12 # 右移12位
    and t0, a7, t0  # t0 == fucnt3
    # sb
    li t1, 0x0      #0x0
    beq t0, t1, sb_print    #print sb
    # sw
    li t1, 0x2      #0x2
    beq t0, t1, sw_print    #print sw
        lw ra, 0(sp)
    addi sp, sp, 4
    jr ra


sbtype_print:# 0x63

    li t0, 7   #后3位的mask
    srli a7, a0, 12 # 右移12位
    and t0, a7, t0  # t0 == fucnt3
    # beq 
    li t1, 0x0      #0x0
    beq t0, t1, beq_print # print
    # bne
    li t1, 0x1      #0x1
    beq t0, t1, bne_print #print
    # blt
    li t1, 0x4       # 0x4
    beq t0, t1, blt_print   #print
    # bge
    li t1, 0x5
    beq t0, t1, bge_print   #print
    li a0, 1    
    li a1, 1
    ecall           # ecall


ujtype_print:# 0x6f
    addi sp, sp, -4
    sw ra, 0(sp)
    jal ra, jal_print     #print jal
    lw a0, -4(s11)
    # print  rd
    # rd: 11-7
    mv t0, a0
    srli t0, t0, 7
    andi t0, t0, 0b11111
    mv s3, t0

    # imm: [20]: 32
    mv t0, a0
    srli t0, t0, 31
    andi t0, t0, 1
    slli t0, t0, 20
    add s2, zero, t0
    # imm:[10:1] : 31 - 21
    mv t0, a0
    srli t0, t0, 21
    andi t0, t0, 0b1111111111
    slli t0, t0, 1
    add s2, s2, t0
    # imm:[11]: 20
    mv t0, a0
    srli t0, t0, 20
    andi t0, t0, 0b1
    slli t0, t0, 11
    add s2, s2, t0
    # imm[19:12]: 19 - 12
    mv t0, a0
    srli t0, t0, 12
    andi t0, t0, 0b11111111
    slli t0, t0, 12
    add s2, s2, t0
    # lw a0, -4(s11)
    # srli t0, a0, 31
    # mv a1, t0
    # li a0, 1
    # ecall           # ecall
    # bnez t0, L2

    mv a0, s3
    jal print_reg
    jal print_comma
    jal print_space
    mv a0, s2
    jal print_imm_j
    jal print_line
    lw ra, 0(sp)
    addi sp, sp, 4
     j next 


     
    # L2: 
    #     addi sp, sp, -4
    #     sw ra, 0(sp)
    #     li t1, 2047
    #     slli t1, t1, 21
    #     add s2, s2, t1
    #     lw ra, 0(sp)
    #     addi sp, sp, 4
    #     jr ra           #retrun


utype_reg_print: 
    addi sp, sp, -4
    sw ra, 0(sp)
    lw a0, -4(s11)
    mv t0, a0
    srli t0, t0, 7
    andi t0, t0, 0b11111
    add s1, zero, t0
    mv t0, a0
    srli t0, t0, 12
    mv s2, t0

    mv a0, s1       
    jal print_reg
    jal print_comma
    jal print_space
    mv a0, s2
    jal print_imm_u
    jal print_line
    lw ra, 0(sp)
    addi sp, sp, 4
     j next 

utype_print:# 0x37
    j lui_print     #print lui



# print 
add_print:
    li a0, 11       # print char
    li a1, 'a'      # a
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'd'      # d
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'd'      # d
    ecall           # ecall
    jal print_space
    j print_rtype_reg   #jump to print reg



or_print:
    li a0, 11       # print char
    li a1, 'o'      # o
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'r'      # r
    ecall           # ecall
    jal print_space
    j print_rtype_reg   #jump to print reg

slt_print:
    li a0, 11       # print char
    li a1, 's'      # s
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'l'      # l
    ecall           # ecall
    li a0, 11       # print char
    li a1, 't'      # t
    ecall           # ecall
    jal print_space
    j print_rtype_reg   #jump to print reg
sltu_print:
    li a0, 11       # print char
    li a1, 's'      # s
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'l'      # l
    ecall           # ecall
    li a0, 11       # print char
    li a1, 't'      # t
    ecall           # ecall
    li a0, 11       #print char
    li a1, 'u'      #u
    ecall
    jal print_space
    j print_rtype_reg   #jump to print reg
sll_print:
    li a0, 11       # print char
    li a1, 's'      # s
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'l'      # l
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'l'      # l
    ecall           # ecall
    jal print_space
    j print_rtype_reg   #jump to print reg
jalr_print:
    li a0, 11       # print char
    li a1, 'j'      # j
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'a'      # a
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'l'      # l
    ecall           # ecall
    li a0, 11       # pirnt char
    li a1, 'r'      # r
    ecall
    jal print_space
    j print_itype_0x67_13_reg   #jump to print reg
addi_print:
    li a0, 11       # print char
    li a1, 'a'      # a
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'd'      # d
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'd'      # d
    ecall           # ecall
    li a0, 11       # pirnt char
    li a1, 'i'      # i
    ecall
    jal print_space
    j print_itype_0x67_13_reg   #jump to print reg
ori_print:
    li a0, 11       # print char
    li a1, 'o'      # o
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'r'      # r
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'i'      # i
    ecall           # ecall
    jal print_space
    j print_itype_0x67_13_reg   #jump to print reg
lb_print:
    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 11       # print char
    li a1, 'l'      # l
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'b'      # b
    ecall           # ecall
    jal print_space
    jal print_itype_0x2_reg   #jump to print reg
    lw ra, 0(sp)
    addi sp, sp, 4
    jr ra           #retrun
lbu_print:
    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 11       # print char
    li a1, 'l'      # l
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'b'      # b
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'u'      # u
    ecall           # ecall
    jal print_space
    jal print_itype_0x2_reg_u   #jump to print reg
    lw ra, 0(sp)
    addi sp, sp, 4
    jr ra           #retrun
lw_print:
    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 11       # print char
    li a1, 'l'      # l
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'w'      # w
    ecall           # ecall
    jal print_space
    jal print_itype_0x2_reg   #jump to print reg
    lw ra, 0(sp)
    addi sp, sp, 4
    jr ra           #retrun
sb_print:
    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 11       # print char
    li a1, 's'      # s
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'b'      # b
    ecall           # ecall
    jal print_space
    jal print_stype_reg
    lw ra, 0(sp)
    addi sp, sp, 4
    jr ra           #retrun
sw_print:
    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 11       # print char
    li a1, 's'      # s
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'w'      # w
    ecall           # ecall
    jal print_space
    jal print_stype_reg
    lw ra, 0(sp)
    addi sp, sp, 4
    jr ra           #retrun
beq_print:
    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 11       # print char
    li a1, 'b'      # b
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'e'      # e
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'q'      # q
    ecall           # ecall
    jal print_space
    j print_sbtype_reg
bne_print:
    li a0, 11       # print char
    li a1, 'b'      # b
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'n'      # n
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'e'      # e
        ecall           # ecall
    jal print_space
    j print_sbtype_reg           #retrun
blt_print:
    li a0, 11       # print char
    li a1, 'b'      # b
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'l'      # l
    ecall           # ecall
    li a0, 11       # print char
    li a1, 't'      # t
        ecall           # ecall
    jal print_space
        j print_sbtype_reg           #retrun
bge_print:
    li a0, 11       # print char
    li a1, 'b'      # b
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'g'      # g
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'e'      # e
    ecall           # ecall
    jal print_space
        j print_sbtype_reg           #retrun
jal_print:
    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 11       # print char
    li a1, 'j'      # j
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'a'      # a
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'l'      # l
    ecall           # ecall
    jal print_space
    lw ra, 0(sp)
    addi sp, sp, 4
    jr ra           #retrun
lui_print:
    addi sp, sp, -4
    sw ra, 0(sp)
    li a0, 11       # print char
    li a1, 'l'      # l
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'u'      # u
    ecall           # ecall
    li a0, 11       # print char
    li a1, 'i'      # i
    ecall           # ecall
    jal print_space
    jal utype_reg_print
    lw ra, 0(sp)
    addi sp, sp, 4
    jr ra           #retrun

.globl main
main:  
    li s10, 0                       #s10 == i = 0 
    la s9, lines_of_machine_codes   # s9 = &lines
    lw s9, 0(s9)                    # s9 = n
    la s11, machine_codes       # load inputs
next:   # for here is a loop 循环PC+=4 然后调用 match——code 然后读数
    beq s10, s9, end_main       # end of the function
    addi s10, s10, 1              # i++
    lw a0, 0(s11)               # a0 = input[0]
    addi s11, s11, 4             # PC += 4
    j match_opcode_and_print_line   #print line
end_main:
    add	   a1, x0, x0		# You can move these line freely
	addi   a0, x0, 17
	ecall      
