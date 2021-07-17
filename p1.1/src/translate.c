/* This project is based on the MIPS Assembler of CS61C in UC Berkeley.
   The framework of this project is been modified to be suitable for RISC-V
   in CS110 course in ShanghaiTech University by Zhijie Yang in March 2019.
   Updated by Chibin Zhang and Zhe Ye in March 2021.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tables.h"
#include "translate.h"
#include "translate_utils.h"

/* Writes instructions during the assembler's first pass to OUTPUT. The case
   for general instructions has already been completed, but you need to write
   code to translate the li, bge and mv pseudoinstructions. Your
   pseudoinstruction expansions should not have any side effects.

   NAME is the name of the instruction, ARGS is an array of the arguments, and
   NUM_ARGS specifies the number of items in ARGS.

   Error checking for regular instructions are done in pass two. However, for
   pseudoinstructions, you must make sure that ARGS contains the correct number
   of arguments. You do NOT need to check whether the registers / label are
   valid, since that will be checked in part two.

   Also for li:
    - make sure that the number is representable by 32 bits. (Hint: the number
        can be both signed or unsigned).
    - if the immediate can fit in the imm field of an addiu instruction, then
        expand li into a single addi instruction. Otherwise, expand it into
        a lui-addi pair.

   And for bge and move:
    - your expansion should use the fewest number of instructions possible.

   venus has slightly different translation rules for li, and it allows numbers
   larger than the largest 32 bit number to be loaded with li. You should follow
   the above rules if venus behaves differently.

   Use fprintf() to write. If writing multiple instructions, make sure that
   each instruction is on a different line.

   Returns the number of instructions written (so 0 if there were any errors).
 */

unsigned write_pass_one(FILE *output, const char *name, char **args,
                        int num_args) {
  long int t_num; /* string to long */
  char str[256];
  char *tmp[3] ;
  char str1[256];
  /* check null ptr */
  if (!output || !name || !args)
    return 0;

  /* Deal with pseudo-instructions. */
  if (strcmp(name, "li") == 0) {

    /* li reg imm */
    if (num_args != 2) {
      return 0;
    }

    /* check imm */
    /* 32 bits */
    if (strlen(args[1]) > 2 && args[1][0] == '0' &&
        args[1][1] == 'x') { /* HEX */
      if (translate_num(&t_num, args[1], 0, 0xFFFFFFFF) ==
          -1) /* bound may contains error */
        return 0;
      if (t_num > 2147483647) /* < 0 */
        t_num = t_num - 0xFFFFFFFF - 1;
    } else { /* DEC */
      if (translate_num(&t_num, args[1], -2147483648, 2147483647) ==
          -1) /* bound may contains error */
        return 0;
    }
    printf("t_num: %ld\n", t_num);
    if (-2048 <= t_num && t_num <= 2047) { /* 12 bit imm */
      args[2] = args[1];
      args[1] = "x0";
      write_inst_string(output, "addi", args, 3);
    } else {                    /* 32 bit imm */
      long fir,sec;
      t_num = (unsigned int)t_num;
      printf("t_num: %lu \n", t_num);
      fir = t_num >> 12;   /* high 20 bit */
      
       sec = t_num & 0xFFF; /* low 12 bit */
      if ((t_num >> 11 & 1 ))    /* */
      {
        ++fir;
        sec = sec - 4096;
      }
      /*printf("fir: %li \n", fir);
      printf("sec: %li \n", sec);*/
      /*  */
      sprintf(str, "%ld", fir);
      /* load agrs */
      tmp[0] = args[0];
      tmp[1] = str;
      /* printf("%s\n", tmp[1]); */
      write_inst_string(output, "lui", tmp, 2);
      /* printf("here2\n");*/
      sprintf(str1, "%ld", sec);
      /* load */
      tmp[0] = args[0];
      tmp[1] = args[0];
      tmp[2] = str1;
      /* write */
      write_inst_string(output, "addi", tmp, 3);
    }
  } else if (strcmp(name, "beqz") == 0) { /*beqz*/
    if (num_args != 2) {
      return 0;
    }
    /* load args */
    args[2] = args[1];
    args[1] = "x0";
    /* write*/
    write_inst_string(output, "beq", args, 3);
  } else if (strcmp(name, "mv") == 0) {
    /*special cases*/
    if (num_args != 2) {
      return 0;
    }
    args[2] = "0";
    /*write*/
    write_inst_string(output, "addi", args, 3);
  } else if (strcmp(name, "j") == 0) {
    /*special cases*/
    if (num_args != 1)
      return 0;
    /*load args*/
    args[1] = args[0];
    args[0] = "zero";
    /*trans str*/
    write_inst_string(output, "jal", args, 2);
  } else if (strcmp(name, "jr") == 0) {
    /* check */
    if (num_args != 1)
      return 0;
    /*load args*/
    args[1] = args[0];
    args[0] = "zero";
    args[2] = "0";
    /*write*/
    write_inst_string(output, "jalr", args, 3);
  } else if (strcmp(name, "jal") == 0) {

    /*type of args*/
    if (num_args == 2) {
      write_inst_string(output, "jal", args, 2);
      return 1;
    }
    if (num_args == 1) /* 1 */
    {
      args[1] = args[0];
      args[0] = "ra";
      write_inst_string(output, "jal", args, 2);
      return 1;
    }

    return 0; /* ret */
  }
  /*jalr*/
  else if (strcmp(name, "jalr") == 0) {
    if (num_args == 3) /*3*/
    {
      write_inst_string(output, "jalr", args, 3);
      return 1;
    }
    if (num_args == 1) /*1*/
    {
      args[1] = args[0];
      args[0] = "ra";
      args[2] = "0";
      /*write*/
      write_inst_string(output, "jalr", args, 3);
      return 1;
    }
    return 0;
    /* */
  } else /* other*/
  {

    write_inst_string(output, name, args, num_args);
  }
  return 1;
}

/* Writes the instruction in hexadecimal format to OUTPUT during pass #2.

   NAME is the name of the instruction, ARGS is an array of the arguments, and
   NUM_ARGS specifies the number of items in ARGS.

   The symbol table (SYMTBL) is given for any symbols that need to be resolved
   at this step.

   You must perform error checking on all instructions and make sure that their
   arguments are valid. If an instruction is invalid, you should not write
   anything to OUTPUT but simply return -1. venus may be a useful resource for
   this step.

   Note the use of helper functions. Consider writing your own! If the function
   definition comes afterwards, you must declare it first (see translate.h).

   Returns 0 on success and -1 on error.
 */
int translate_inst(FILE *output, const char *name, char **args, size_t num_args,
                   uint32_t addr, SymbolTable *symtbl) {
  if (strcmp(name, "add") == 0) /*add*/
    return write_rtype(0x33, 0x00, 0x00, output, args, num_args);
  else if (strcmp(name, "or") == 0) /*or*/
    return write_rtype(0x33, 0x06, 0x00, output, args, num_args);
  else if (strcmp(name, "sll") == 0) /*sll*/
    return write_rtype(0x33, 0x01, 0x00, output, args, num_args);
  else if (strcmp(name, "slt") == 0) /*slt*/
    return write_rtype(0x33, 0x02, 0x00, output, args, num_args);
  else if (strcmp(name, "sltu") == 0) /*sltu*/
    return write_rtype(0x33, 0x03, 0x00, output, args, num_args);
  /* YOUR CODE HERE */
  /*others*/

  /* ====I==== */

  /* lb */
  else if (strcmp(name, "lb") == 0)
    return write_itype(0x03, 0x00, output, args, num_args);
  /* lw */
  else if (strcmp(name, "lw") == 0)
    return write_itype(0x03, 0x02, output, args, num_args);
  /* lbu */
  else if (strcmp(name, "lbu") == 0)
    return write_itype(0x03, 0x04, output, args, num_args);
  /* addi */
  else if (strcmp(name, "addi") == 0)
    return write_itype(0x13, 0x00, output, args, num_args);
  /* ori */
  else if (strcmp(name, "ori") == 0)
    return write_itype(0x13, 0x06, output, args, num_args);
  /* jalr */
  else if (strcmp(name, "jalr") == 0)
    return write_itype(0x67, 0x00, output, args, num_args);
  /* ====S==== */

  /* sb */
  else if (strcmp(name, "sb") == 0)
    return write_stype(0x23, 0x00, output, args, num_args);
  /* sw */
  else if (strcmp(name, "sw") == 0)
    return write_stype(0x23, 0x02, output, args, num_args);
  /* ====SB==== */

  /* beq */
  else if (strcmp(name, "beq") == 0)
    return write_sbtype(0x63, 0x00, output, args, num_args, addr, symtbl);
  /* bne */
  else if (strcmp(name, "bne") == 0)
    return write_sbtype(0x63, 0x01, output, args, num_args, addr, symtbl);
  /* blt */
  else if (strcmp(name, "blt") == 0)
    return write_sbtype(0x63, 0x04, output, args, num_args, addr, symtbl);
  /* bge */
  else if (strcmp(name, "bge") == 0)
    return write_sbtype(0x63, 0x05, output, args, num_args, addr, symtbl);
  /* ====U==== */

  /* lui */
  else if (strcmp(name, "lui") == 0)
    return write_utype(0x37, output, args, num_args);

  /* ====UJ==== */

  /* jal */
  else if (strcmp(name, "jal") == 0)
    return write_ujtype(0x6f, output, args, num_args, addr, symtbl);
  else
    return -1;
}
/* A helper function for writing most R-type instructions. You should use
   translate_reg() to parse registers and write_inst_hex() to write to
   OUTPUT. Both are defined in translate_utils.h.

   This function is INCOMPLETE. Complete the implementation below. You will
   find bitwise operations to be the cleanest way to complete this function.
 */
int write_rtype(uint8_t opcode, uint8_t funct3, uint8_t funct7, FILE *output,
                char **args, size_t num_args) {
  /*  Perhaps perform some error checking? */
  int rd, rs, rt;
  uint32_t instruction = 0;

  /*check*/
  if (num_args != 3) {
    return -1;
  }

  /*rd 0*/
  rd = translate_reg(args[0]);
  /*rs 1*/
  rs = translate_reg(args[1]);
  /*rt 2*/
  rt = translate_reg(args[2]);
  /* REMOVE THE FOLLOWING LINE. IT'S FOR MAKING YOUR CODE TO COMPILE */

  /*check args*/
  /* YOUR CODE HERE */
  /* error checking for register ids */
  if (rd == -1 || rs == -1 || rt == -1) {
    return -1;
  }
  /* generate instruction */
  instruction = opcode + (funct3 << 12) + (funct7 << 25) + (rd << 7) +
                (rs << 15) + (rt << 20);

  write_inst_hex(output, instruction); /* output */
  return 0;
}

int write_itype(uint8_t opcode, uint8_t funct3, FILE *output, char **args,
                size_t num_args) {
  /* YOUR CODE HERE */
  int rd, rs;
  long imme;
  uint32_t instruction = 0;

  /*check args*/
  if (num_args != 3) {
    return -1;
  }

#ifdef DEBUG /* debug */
  printf("%s:%d BEGIN write_itype\n", __FILE__, __LINE__);
#endif

  /*set rd 0*/
  rd = translate_reg(args[0]);
  if (rd == -1)
    return -1;
  if (opcode == 0x03) {
    /* rs */
    rs = translate_reg(args[2]);
    /* imme */
    if (rs == -1)
      return -1;
    if (strlen(args[1]) > 2 && args[1][0] == '0' && args[1][1] == 'x') {
      if (translate_num(&imme, args[1], 0, 0xFFFFFFFF) == -1)
        return -1; /* ret */

      if (imme > 0x7FFFFFFF) /* 32 */
        imme = imme - 0xFFFFFFFF - 1;
      if (imme > 0xFFF)
        return -1;
      if (imme > 2047)                 /* not 12 b */
        imme = imme - 0xFFF - 1;       /* + -> - */
      if (imme > 2047 || imme < -2048) /* not in range */
        return -1;
#ifdef DEBUG /* debug */
      printf("%s:%d imme: %ld\n", __FILE__, __LINE__, imme);
#endif
    } else {

      if (translate_num(&imme, args[1], -2048, 2047) == -1) /* DEC */
        return -1;                                          /* call err */
    }
    instruction = /* ins */
        opcode + (rd << 7) + (funct3 << 12) + (rs << 15) + (imme << 20);
    write_inst_hex(output, instruction);
    return 0;
  }

  else {

    /* rs */
    rs = translate_reg(args[1]);
    /* imme */
    if (rs == -1)
      return -1;
    if (strlen(args[2]) > 2 && args[2][0] == '0' && args[2][1] == 'x') /* HEX */
    {
      if (translate_num(&imme, args[2], 0, 0xFFFFFFFF) == -1) /* 32 ? */
        return -1;
      if (imme > 0x7FFFFFFF) /* + / - */
        imme = imme - 0xFFFFFFFF - 1;

      if (imme > 0xFFF) /* 12 ? */
        return -1;
      if (imme > 2047)
        imme = imme - 0xFFF - 1; /* - ! */
      if (imme > 2047 || imme < -2048)
        return -1;
#ifdef DEBUG /* debug */
      printf("%s:%d imme: %ld\n", __FILE__, __LINE__, imme);
#endif
    } else {
      /* printf("imme: %s", args[2]); */
      if (translate_num(&imme, args[2], -2048, 2047) == -1) /* DEC */
        return -1;
    }
    instruction = opcode + (rd << 7) + (funct3 << 12) + (rs << 15) +
                  (imme << 20); /* green book */
    write_inst_hex(output, instruction);
    return 0;
  }

  return -1;
}

/* int write_stype(uint8_t opcode, uint8_t funct3, FILE *output, char **args,
                size_t num_args) */

int write_stype(uint8_t opcode, uint8_t funct3, FILE *output, char **args,
                size_t num_args) {
  int rs, rt;
  long imme;
  uint32_t instruction; /* uint32_t instruction; */
  if (num_args != 3)    /* check */
    return -1;
  rs = translate_reg(args[2]); /* reg */
  rt = translate_reg(args[0]);
  if (rs == -1)
    return -1; /* reg ? */
  if (rt == -1)
    return -1;
  if (strlen(args[1]) > 2 && args[1][0] == '0' && args[1][1] == 'x') /* HEX */
  {
    if (translate_num(&imme, args[1], 0, 0xFFFFFFFF) == -1) /* 32 ? */
      return -1;
    if (imme > 0x7FFFFFFF) /* 32 u -> li */
      imme = imme - 0xFFFFFFFF - 1;

    if (imme > 0xFFF) /* 12  */
      return -1;
    if (imme > 2047)
      imme = imme - 0xFFF - 1;
    if (imme > 2047 || imme < -2048) /* 12 range */
      return -1;
  } else {
    if (translate_num(&imme, args[1], -2048, 2047) == -1)
      return -1;
  }
  /* check reg */
  if (rt == -1 || rs == -1 || imme == -1) {
    return -1;
  }
  instruction = opcode + ((imme & 0x0000001F) << 7) + (funct3 << 12) +
                (rs << 15) + (rt << 20) + ((imme >> 5) << 25);
  write_inst_hex(output, instruction); /* write gex */
  return 0;
}

/* Hint: the way for branch to calculate relative address. e.g. bne
     bne rs rt label
   assume the byte_offset(addr) of label is L,
   current instruction byte_offset(addr) is A
   the relative address I for label satisfy:
     L = A + I
   so the relative addres is
     I = L - A              */
int write_sbtype(uint8_t opcode, uint8_t funct3, FILE *output, char **args,
                 size_t num_args, uint32_t addr, SymbolTable *symtbl) {
  int rs, rt, imme = 0; /* init */
  int64_t label_addr;
  uint32_t instruction;
  if (num_args != 3) /* cherck num_args */
  {
    return -1;
  }
  rs = translate_reg(args[0]);
  rt = translate_reg(args[1]); /* args[1] */
  if (rt == -1 || rs == -1 || imme == -1 || !args[2]) {
    return -1; /* check regs valid */
  }
  label_addr = get_addr_for_symbol(symtbl, args[2]); /* get smbol addr */
  if (label_addr >= 0)
    imme = label_addr - addr; /* get imme */
  else
    return -1;

  if (imme < int12_min || imme > int12_UP)
    return -1;
  instruction = opcode + ((((imme) >> 11) & 1) << 7) + /* grenbook */
                ((((imme ) >> 1) & 0xF) << 8) + (funct3 << 12) +
                (rs << 15) + (rt << 20) + (((imme & 0x000007E0) >> 5) << 25) +
                ((((imme ) >> 12) & 1 )<< 31); /* grenbook */
  write_inst_hex(output, instruction);
  return 0;
}
/*


int write_utype(uint8_t opcode, FILE *output, char **args, size_t num_args)
{
  */
int write_utype(uint8_t opcode, FILE *output, char **args, size_t num_args) {
  int rd, tmp;
  long int imme;
  uint32_t instruction; /* iknit */

  if (num_args != 2)
    return -1;

  rd = translate_reg(args[0]);
  tmp = translate_num(&imme, args[1], 0, 0xFFFFF);
  if (tmp == -1 || rd == -1) /* check reg */
    return -1;

  instruction = opcode + (rd << 7) + (imme << 12);

  write_inst_hex(output, instruction);
  return 0;
}

/* In this project there is no need to relocate labels,
   you may think about the reasons. */
int write_ujtype(uint8_t opcode, FILE *output, char **args, size_t num_args,
                 uint32_t addr, SymbolTable *symtbl) {
  int rd;/* init */
  long imme;
  uint32_t instruction;
  int64_t label_addr; /* init */
  if (num_args != 2)
    return -1;
  rd = translate_reg(args[0]);
 /* printf("rd: %d", rd);*/
  if (rd == -1)
    return -1;
  /** get label address */

  label_addr = get_addr_for_symbol(symtbl, args[1]);
  if (label_addr < 0)
    return -1;
  imme = label_addr - addr; /* get addr */

  if (imme > 0x7FFFF || imme < (long)0xFFFFFFFFFFF80000) { /* check range */
    return -1;
  }

  instruction = opcode + (rd << 7) + (imme & 0x000FF000) + /* greenbook */
                (((imme & 0x00000800) >> 11) << 20) +
                (((imme & 0x0000007FE) >> 1) << 21) +
                (((imme & 0x00100000) >> 20) << 31);/* greenbook */
  write_inst_hex(output, instruction);
  return 0;
}
