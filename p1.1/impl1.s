make -C test clean
make[1]: Entering directory '/home/canarypwn/p1.1_qinfr_lixz/test'
rm -rf out
make[1]: Leaving directory '/home/canarypwn/p1.1_qinfr_lixz/test'
rm -f *.o assembler
rm -rf out
rm -rf __pycache__
gcc -D DEBUG -g -std=c89 -Wpedantic -Wall -Wextra -Werror -o assembler assembler.c src/tables.c src/utils.c src/translate_utils.c src/translate.c
make -C test
make[1]: Entering directory '/home/canarypwn/p1.1_qinfr_lixz/test'
valgrind --tool=memcheck --leak-check=full --track-origins=yes ../assembler -p1 in/p1/simple.s out/p1/simple.int out/p1/simple.symtbl -log out/p1/simple.log 2> out/p1/simple.memcheck || true
Running pass one: in/p1/simple.s -> out/p1/simple.int, out/p1/simple.symtbl
assembler.c:174 a=0
token: a2
token: a0
token: a1
assembler.c:209 name:add 3 BEGIN write_pass_one
assembler.c:212 name: add, a2
assembler.c:212 name: add, a0
assembler.c:212 name: add, a1
assembler.c:174 a=0
token: a4
token: a3
token: t0
assembler.c:209 name:or 3 BEGIN write_pass_one
assembler.c:212 name: or, a4
assembler.c:212 name: or, a3
assembler.c:212 name: or, t0
assembler.c:174 a=0
token: t1
assembler.c:209 name:jr 1 BEGIN write_pass_one
assembler.c:212 name: jr, t1
Results saved to -log
valgrind --tool=memcheck --leak-check=full --track-origins=yes ../assembler -p1 in/p1/unknown_instr.s out/p1/unknown_instr.int out/p1/unknown_instr.symtbl -log out/p1/unknown_instr.log 2> out/p1/unknown_instr.memcheck || true
Running pass one: in/p1/unknown_instr.s -> out/p1/unknown_instr.int, out/p1/unknown_instr.symtbl
assembler.c:174 a=0
token: meaningless
token: line
assembler.c:209 name:a 2 BEGIN write_pass_one
assembler.c:212 name: a, meaningless
assembler.c:212 name: a, line
Results saved to -log
valgrind --tool=memcheck --leak-check=full --track-origins=yes ../assembler -p2 in/p2/labels.int in/p2/labels.symtbl out/p2/labels.out -log out/p2/labels.log 2> out/p2/labels.memcheck || true
Running pass two: in/p2/labels.int, in/p2/labels.symtbl -> out/p2/labels.out
assembler.c:262 .text
src/tables.c:222 name: label1 , address: 0 
src/tables.c:222 name: label3 , address: 0 
src/tables.c:222 name: label2 , address: 4 
assembler.c:291 name:beq 3 BEGIN translate_inst
assembler.c:294 name: beq, t0
assembler.c:294 name: beq, t1
assembler.c:294 name: beq, label2
Results saved to -log
valgrind --tool=memcheck --leak-check=full --track-origins=yes ../assembler in/full/labels.s out/full/labels.int out/full/labels.symtbl out/full/labels.out -log out/full/labels.log 2> out/full/labels.memcheck || true
Running pass one: in/full/labels.s -> out/full/labels.int, out/full/labels.symtbl
assembler.c:174 a=1
assembler.c:174 a=1
token: t0
token: t1
token: label2
assembler.c:209 name:beq 3 BEGIN write_pass_one
assembler.c:212 name: beq, t0
assembler.c:212 name: beq, t1
assembler.c:212 name: beq, label2
assembler.c:174 a=1
Running pass two: out/full/labels.int, out/full/labels.symtbl -> out/full/labels.out
assembler.c:262 .text
src/tables.c:222 name: label1 , address: 0 
src/tables.c:222 name: label3 , address: 0 
src/tables.c:222 name: label2 , address: 4 
assembler.c:291 name:beq 3 BEGIN translate_inst
assembler.c:294 name: beq, t0
assembler.c:294 name: beq, t1
assembler.c:294 name: beq, label2
Results saved to -log
valgrind --tool=memcheck --leak-check=full --track-origins=yes ../assembler in/full/simple1.s out/full/simple1.int out/full/simple1.symtbl out/full/simple1.out -log out/full/simple1.log 2> out/full/simple1.memcheck || true
Running pass one: in/full/simple1.s -> out/full/simple1.int, out/full/simple1.symtbl
assembler.c:174 a=0
token: t0
token: 0xEFFFFFFF
assembler.c:209 name:li 2 BEGIN write_pass_one
assembler.c:212 name: li, t0
assembler.c:212 name: li, 0xEFFFFFFF
translate_num: 4026531839
upper bound: 4294967295
t_num: -268435457
t_num: 4026531839 
fir: 983039 
sec: 983039 
valgrind --tool=memcheck --leak-check=full --track-origins=yes ../assembler in/full/p1_errors.s out/full/p1_errors.int out/full/p1_errors.symtbl out/full/p1_errors.out -log out/full/p1_errors.log 2> out/full/p1_errors.memcheck || true
Running pass one: in/full/p1_errors.s -> out/full/p1_errors.int, out/full/p1_errors.symtbl
assembler.c:174 a=0
token: a0
token: a0
token: a1
token: t0
assembler.c:174 a=1
assembler.c:174 a=0
token: a2
token: a3
token: t0
assembler.c:209 name:or 3 BEGIN write_pass_one
assembler.c:212 name: or, a2
assembler.c:212 name: or, a3
assembler.c:212 name: or, t0
assembler.c:174 a=0
token: t1
assembler.c:209 name:jr 1 BEGIN write_pass_one
assembler.c:212 name: jr, t1
assembler.c:174 a=-1
assembler.c:174 a=0
token: t2
token: t2
token: s0
assembler.c:209 name:slt 3 BEGIN write_pass_one
assembler.c:212 name: slt, t2
assembler.c:212 name: slt, t2
assembler.c:212 name: slt, s0
assembler.c:174 a=0
token: s1
token: s2
token: s3
token: sll
assembler.c:174 a=0
token: t3
token: 123
assembler.c:209 name:lui 2 BEGIN write_pass_one
assembler.c:212 name: lui, t3
assembler.c:212 name: lui, 123
src/tables.c:131 name already exists
assembler.c:174 a=-1
assembler.c:174 a=0
token: label
assembler.c:209 name:jal 1 BEGIN write_pass_one
assembler.c:212 name: jal, label
assembler.c:174 a=1
token: addiu
token: t3
token: t1
token: 5
assembler.c:174 a=0
token: t3
token: t2
token: 0xABC
assembler.c:209 name:ori 3 BEGIN write_pass_one
assembler.c:212 name: ori, t3
assembler.c:212 name: ori, t2
assembler.c:212 name: ori, 0xABC
assembler.c:174 a=0
token: t3
token: 99
token: 3
assembler.c:209 name:addiu 3 BEGIN write_pass_one
assembler.c:212 name: addiu, t3
assembler.c:212 name: addiu, 99
assembler.c:212 name: addiu, 3
assembler.c:174 a=0
token: t1
token: t0
token: 0xFFFFFFFF
assembler.c:209 name:ori 3 BEGIN write_pass_one
assembler.c:212 name: ori, t1
assembler.c:212 name: ori, t0
assembler.c:212 name: ori, 0xFFFFFFFF
assembler.c:174 a=0
token: t0
token: t1
token: not_found
assembler.c:209 name:bne 3 BEGIN write_pass_one
assembler.c:212 name: bne, t0
assembler.c:212 name: bne, t1
assembler.c:212 name: bne, not_found
Running pass two: out/full/p1_errors.int, out/full/p1_errors.symtbl -> out/full/p1_errors.out
assembler.c:262 .text
src/tables.c:222 name: label , address: 0 
src/tables.c:222 name: l1 , address: 20 
assembler.c:291 name:or 3 BEGIN translate_inst
assembler.c:294 name: or, a2
assembler.c:294 name: or, a3
assembler.c:294 name: or, t0
rd: 12
rs: 13
rt: 5
assembler.c:291 name:jalr 3 BEGIN translate_inst
assembler.c:294 name: jalr, zero
assembler.c:294 name: jalr, t1
assembler.c:294 name: jalr, 0
src/translate.c:339 BEGIN write_itype
translate_num: 0
upper bound: 2047
assembler.c:291 name:slt 3 BEGIN translate_inst
assembler.c:294 name: slt, t2
assembler.c:294 name: slt, t2
assembler.c:294 name: slt, s0
rd: 7
rs: 7
rt: 8
assembler.c:291 name:lui 2 BEGIN translate_inst
assembler.c:294 name: lui, t3
assembler.c:294 name: lui, 123
translate_num: 123
upper bound: 1048575
assembler.c:291 name:jal 2 BEGIN translate_inst
assembler.c:294 name: jal, ra
assembler.c:294 name: jal, label
assembler.c:291 name:ori 3 BEGIN translate_inst
assembler.c:294 name: ori, t3
assembler.c:294 name: ori, t2
assembler.c:294 name: ori, 0xABC
src/translate.c:339 BEGIN write_itype
translate_num: 2748
upper bound: 4294967295
src/translate.c:399 imme: -1348
assembler.c:291 name:addiu 3 BEGIN translate_inst
assembler.c:294 name: addiu, t3
assembler.c:294 name: addiu, 99
assembler.c:294 name: addiu, 3
assembler.c:298 raise_instruction_error
assembler.c:291 name:ori 3 BEGIN translate_inst
assembler.c:294 name: ori, t1
assembler.c:294 name: ori, t0
assembler.c:294 name: ori, 0xFFFFFFFF
src/translate.c:339 BEGIN write_itype
translate_num: 4294967295
upper bound: 4294967295
src/translate.c:399 imme: -1
assembler.c:291 name:bne 3 BEGIN translate_inst
assembler.c:294 name: bne, t0
assembler.c:294 name: bne, t1
assembler.c:294 name: bne, not_found
assembler.c:298 raise_instruction_error
Results saved to -log
valgrind --tool=memcheck --leak-check=full --track-origins=yes ../assembler in/full/p2_errors.s out/full/p2_errors.int out/full/p2_errors.symtbl out/full/p2_errors.out -log out/full/p2_errors.log 2> out/full/p2_errors.memcheck || true
Running pass one: in/full/p2_errors.s -> out/full/p2_errors.int, out/full/p2_errors.symtbl
assembler.c:174 a=0
token: t0
token: t3
token: t3
assembler.c:209 name:addi 3 BEGIN write_pass_one
assembler.c:212 name: addi, t0
assembler.c:212 name: addi, t3
assembler.c:212 name: addi, t3
assembler.c:174 a=1
assembler.c:209 name:jal 0 BEGIN write_pass_one
assembler.c:219 raise_instruction_error
assembler.c:174 a=0
token: t2
token: 99
token: 0xAB
assembler.c:209 name:ori 3 BEGIN write_pass_one
assembler.c:212 name: ori, t2
assembler.c:212 name: ori, 99
assembler.c:212 name: ori, 0xAB
assembler.c:174 a=0
token: t0
token: t1
token: not_found
assembler.c:209 name:bne 3 BEGIN write_pass_one
assembler.c:212 name: bne, t0
assembler.c:212 name: bne, t1
assembler.c:212 name: bne, not_found
assembler.c:174 a=0
token: t3
token: t2
token: 0x80808080
assembler.c:209 name:addi 3 BEGIN write_pass_one
assembler.c:212 name: addi, t3
assembler.c:212 name: addi, t2
assembler.c:212 name: addi, 0x80808080
Running pass two: out/full/p2_errors.int, out/full/p2_errors.symtbl -> out/full/p2_errors.out
assembler.c:262 .text
src/tables.c:222 name: label , address: 4 
assembler.c:291 name:addi 3 BEGIN translate_inst
assembler.c:294 name: addi, t0
assembler.c:294 name: addi, t3
assembler.c:294 name: addi, t3
src/translate.c:339 BEGIN write_itype
translate_num: 0
upper bound: 2047
translate_num: ERR
assembler.c:298 raise_instruction_error
assembler.c:291 name:ori 3 BEGIN translate_inst
assembler.c:294 name: ori, t2
assembler.c:294 name: ori, 99
assembler.c:294 name: ori, 0xAB
src/translate.c:339 BEGIN write_itype
assembler.c:298 raise_instruction_error
assembler.c:291 name:bne 3 BEGIN translate_inst
assembler.c:294 name: bne, t0
assembler.c:294 name: bne, t1
assembler.c:294 name: bne, not_found
assembler.c:298 raise_instruction_error
assembler.c:291 name:addi 3 BEGIN translate_inst
assembler.c:294 name: addi, t3
assembler.c:294 name: addi, t2
assembler.c:294 name: addi, 0x80808080
src/translate.c:339 BEGIN write_itype
translate_num: 2155905152
upper bound: 4294967295
assembler.c:298 raise_instruction_error
Results saved to -log
[pass] p1/simple - Answers
[pass] p1/simple - Memory Check
[pass] p1/unknown_instr - Answers
[pass] p1/unknown_instr - Memory Check
[pass] p2/labels - Answers
[pass] p2/labels - Memory Check
[pass] full/labels - Answers
[pass] full/labels - Memory Check
[FAIL] full/simple1 - Answers
[----] full/simple1 - Memory Check
[pass] full/p1_errors - Answers
[pass] full/p1_errors - Memory Check
[pass] full/p2_errors - Answers
[pass] full/p2_errors - Memory Check
12 of 14 tests passed
make[1]: Leaving directory '/home/canarypwn/p1.1_qinfr_lixz/test'
