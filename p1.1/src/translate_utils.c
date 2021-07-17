/* This project is based on the MIPS Assembler of CS61C in UC Berkeley.
   The framework of this project is been modified to be suitable for RISC-V
   in CS110 course in ShanghaiTech University by Zhijie Yang in March 2019.
   Updated by Chibin Zhang and Zhe Ye in March 2021.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "translate_utils.h"

void write_inst_string(FILE *output, const char *name, char **args,
                       int num_args) {
  int i;

  fprintf(output, "%s", name);
  for (i = 0; i < num_args; i++) { /* framework */
    fprintf(output, " %s", args[i]);
  }
  fprintf(output, "\n");/* framework */
}

void write_inst_hex(FILE *output, uint32_t instruction) {/* framework */
  fprintf(output, "%08x\n", instruction);
}
/* framework */
int is_valid_label(const char *str) {
  int first = 1;
  if (!str) {/* framework */
    return 0;
  }

  while (*str) {
    if (first) {/* framework */
      if (!isalpha((int)*str) && *str != '_') {
        return 0; /* does not start with letter or underscore */
      } else {
        first = 0;
      }
    } else if (!isalnum((int)*str) && *str != '_') {
      return 0; /* subsequent characters not alphanumeric */
    }
    str++;/* framework */
  }
  return first ? 0 : 1; /* empty string is invalid  */
}

/* Translate the input string into a signed number. The number is then
   checked to be within the correct range (note bounds are INCLUSIVE)
   ie. NUM is valid if LOWER_BOUND <= NUM <= UPPER_BOUND.

   The input may be in either positive or negative, and be in either
   decimal or hexadecimal format. It is also possible that the input is not
   a valid number. Fortunately, the library function strtol() can take
   care of all that (with a little bit of work from your side of course).
   Please read the documentation for strtol() carefully. Do not use strtoul()
   or any other variants.

   You should store the result into the location that OUTPUT points to. The
   function returns 0 if the conversion proceeded without errors, or -1 if an
   error occurred.
 */
int translate_num(long int *output, const char *str, long int lower_bound,
                  long int upper_bound) {
  char *ptr;/* framework */
  long int ret;

  if (!str || !output) {
    return -1;
  }/* framework */

  ret = strtol(str, &ptr, 0);
  #ifdef DEBUG
  printf("translate_num: %ld\n", ret);/* framework */
  printf("upper bound: %ld\n", upper_bound);
  #endif/* framework */
  if (*ptr == '\0'  && lower_bound <= ret && ret <= upper_bound) {
    *output = ret;/* framework */
    return 0;
  }/* framework */
  #ifdef DEBUG
  printf("translate_num: ERR\n");/* framework */
  #endif
  return -1;/* framework */
}
/* Translates the register name to the corresponding register number. Please
   see the RISC-V Green Sheet for information about register numbers.

   Returns the register number of STR or -1 if the register name is invalid.
 */
int translate_reg(const char *str) {
  if (strcmp(str, "zero") == 0 || strcmp(str, "x0") == 0) /* return */
    return 0;
  else if (strcmp(str, "ra") == 0 || strcmp(str, "x1") == 0)/* return */
    return 1;
  else if (strcmp(str, "sp") == 0 || strcmp(str, "x2") == 0)/* return */
    return 2;
  else if (strcmp(str, "gp") == 0 || strcmp(str, "x3") == 0)/* return */
    return 3;
  else if (strcmp(str, "tp") == 0 || strcmp(str, "x4") == 0)/* return */
    return 4;
  else if (strcmp(str, "t0") == 0 || strcmp(str, "x5") == 0)/* return */
    return 5;
  else if (strcmp(str, "t1") == 0 || strcmp(str, "x6") == 0)/* return */
    return 6;
  else if (strcmp(str, "t2") == 0 || strcmp(str, "x7") == 0)/* return */
    return 7;
  else if (strcmp(str, "s0") == 0 || strcmp(str, "fp") ==0 ||/* return */
           strcmp(str, "x8") == 0)
   {return 8;}
  else if (strcmp(str, "s1") == 0 || strcmp(str, "x9") == 0)/* return */
    return 9;
  else if (strcmp(str, "a0") == 0 || strcmp(str, "x10") == 0)/* return */
    return 10;
  else if (strcmp(str, "a1") == 0 || strcmp(str, "x11") == 0)/* return */
    return 11;
  else if (strcmp(str, "a2") == 0 || strcmp(str, "x12") == 0)/* return */
    { return 12;}
  else if (strcmp(str, "a3") == 0 || strcmp(str, "x13") == 0)
    return 13;/* return */
  else if (strcmp(str, "a4") == 0 || strcmp(str, "x14") == 0)
    return 14;
  else if (strcmp(str, "a5") == 0 || strcmp(str, "x15") == 0)/* return */
    return 15;
  else if (strcmp(str, "a6") == 0 || strcmp(str, "x16") == 0)/* return */
    return 16;
  else if (strcmp(str, "a7") == 0 || strcmp(str, "x17") == 0)
    return 17;
  else if (strcmp(str, "s2") == 0 || strcmp(str, "x18") == 0)/* return */
    return 18;
  else if (strcmp(str, "s3") == 0 || strcmp(str, "x19") == 0)
    return 19;
  else if (strcmp(str, "s4") == 0 || strcmp(str, "x20") == 0)/* return */
    return 20;
  else if (strcmp(str, "s5") == 0 || strcmp(str, "x21") == 0)
    return 21;/* return */
  else if (strcmp(str, "s6") == 0 || strcmp(str, "x22") == 0)
    return 22;
  else if (strcmp(str, "s7") == 0 || strcmp(str, "x23") == 0)/* return */
    return 23;
  else if (strcmp(str, "s8") == 0 || strcmp(str, "x24") == 0)
    return 24;/* return */
  else if (strcmp(str, "s9") == 0 || strcmp(str, "x25") == 0)
    return 25;/* return */
  else if (strcmp(str, "s10") == 0 || strcmp(str, "x26") == 0)
    return 26;/* return */
  else if (strcmp(str, "s11") == 0 || strcmp(str, "x27") == 0)
    return 27;
  else if (strcmp(str, "t3") == 0 || strcmp(str, "x28") == 0)
    return 28;/* return */
  else if (strcmp(str, "t4") == 0 || strcmp(str, "x29") == 0)/* return */
    return 29;
  else if (strcmp(str, "t5") == 0 || strcmp(str, "x30") == 0)
    return 30;/* return */
  else if (strcmp(str, "t6") == 0 || strcmp(str, "x31") == 0)
    return 31;
  else
    return -1;
}/* return */
