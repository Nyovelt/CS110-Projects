.data

# Constant integer specifying the lines of machine codes

# DO NOT MODIFY THIS VARIABLE
.globl lines_of_machine_codes
lines_of_machine_codes:
    .word 8


# 32-bits machine codes
# A 32-bits hexadecimal number represents one line of machine code.
# You can suppose all of the input machine codes are valid. 

# DO NOT MODIFY THIS VARIABLE
.globl machine_codes
machine_codes:
    .word 0x000502B3    # add  t0, a0, x0
    .word 0x00100313    # addi t1, x0, 1
    .word 0x00028863    # beq  t0, x0, 16
    .word 0x01DE13B3    # sll  t2, t3, t4
    .word 0xFFF28293    # addi t0, t0, -1
    .word 0xFF5FF06F    # jal  x0, -12    Here we use offset instead of label.
    .word 0x00600533    # add  a0, x0, t1
    .word 0x00008067    # jalr x0, ra, 0