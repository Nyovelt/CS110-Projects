/* This project is based on the MIPS Assembler of CS61C in UC Berkeley.
   The framework of this project is been modified to be suitable for RISC-V
   in CS110 course in ShanghaiTech University by Zhijie Yang in March 2019.
   Updated by Chibin Zhang and Zhe Ye in March 2021.
*/

#ifndef TRANSLATE_UTILS_H
#define TRANSLATE_UTILS_H

#define int32_up (long int)0x000000007FFFFFFF
/*upper*/
#define int32_down (long int)0xFFFFFFFF80000000
/*lower*/
#define unint32_up (unsigned long)0x00000000FFFFFFFF
/*uint upper*/

#define int20_up (long)0x000000000007FFFF
/*upper*/
#define int20_down (long)0xFFFFFFFFFFF80000
/*loweer*/
#define uint20_up (unsigned long)0x00000000000FFFFF
/*uint upper*/

#define int12_UP (long int)0x00000000000007FF
/*upper*/
#define int12_min (long int)0xFFFFFFFFFFFFF800
/*lower*/
#define uint12_up (unsigned long)0x0000000000000FFF
/*uint upper*/

#include <stdint.h>

/* Writes the instruction as a string to OUTPUT. NAME is the name of the
   instruction, and its arguments are in ARGS. NUM_ARGS is the length of
   the array.
 */
void write_inst_string(FILE *output, const char *name, char **args,
                       int num_args);

/* Writes the instruction to OUTPUT in hexadecimal format. */
void write_inst_hex(FILE *output, uint32_t instruction);

/* Returns 1 if the label is valid and 0 if it is invalid. A valid label is one
   where the first character is a character or underscore and the remaining
   characters are either characters, digits, or underscores.
 */
int is_valid_label(const char *str);

/* IMPLEMENT ME - see documentation in translate_utils.c */
int translate_num(long int *output, const char *str, long int lower_bound,
                  long int upper_bound);

/* IMPLEMENT ME - see documentation in translate_utils.c */
int translate_reg(const char *str);

#endif
