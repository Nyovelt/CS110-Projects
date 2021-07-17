/* This project is based on the MIPS Assembler of CS61C in UC Berkeley.
   The framework of this project is been modified to be suitable for RISC-V
   in CS110 course in ShanghaiTech University by Zhijie Yang in March 2019.
   Updated by Chibin Zhang and Zhe Ye in March 2021.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/tables.h"
#include "src/translate.h"
#include "src/translate_utils.h"
#include "src/utils.h"

#include "assembler.h"

#define MAX_ARGS 3
#define BUF_SIZE 1024
const char *IGNORE_CHARS = " \f\n\r\t\v,()";
const int SYMBOLTBL_NON_UNIQUE = 0;
const int SYMBOLTBL_UNIQUE_NAME = 1; /* init */
/*******************************
 * Helper Functions
 *******************************/

/* you should not be calling this function yourself. */
static void raise_label_error(uint32_t input_line, const char *label) {
  write_to_log("Error - invalid label at line %d: %s\n", input_line, label);
}

/* call this function if more than MAX_ARGS arguments are found while parsing
   arguments.

   INPUT_LINE is which line of the input file that the error occurred in. Note
   that the first line is line 1 and that empty lines are included in the count.

   EXTRA_ARG should contain the first extra argument encountered.
 */
static void raise_extra_argument_error(uint32_t input_line,
                                       const char *extra_arg) {
  write_to_log("Error - extra argument at line %d: %s\n", input_line,
               extra_arg);
}

/* You should call this function if write_pass_one() or translate_inst()
   returns -1.

   INPUT_LINE is which line of the input file that the error occurred in. Note
   that the first line is line 1 and that empty lines are included in the count.
 */
static void raise_instruction_error(uint32_t input_line, const char *name,
                                    char **args, int num_args) {

  write_to_log("Error - invalid instruction at line %d: ", input_line);
  log_inst(name, args, num_args);
}

/* Truncates the string at the first occurrence of the '#' character. */
static void skip_comments(char *str) {
  char *comment_start = strchr(str, '#');
  if (comment_start) {
    *comment_start = '\0';
  }
}

/* Reads STR and determines whether it is a label (ends in ':'), and if so,
   whether it is a valid label, and then tries to add it to the symbol table.

   INPUT_LINE is which line of the input file we are currently processing. Note
   that the first line is line 1 and that empty lines are included in this
   count.

   BYTE_OFFSET is the offset of the NEXT instruction (should it exist).

   Four scenarios can happen:
    1. STR is not a label (does not end in ':'). Returns 0.
    2. STR ends in ':', but is not a valid label. Returns -1.
    3a. STR ends in ':' and is a valid label. Addition to symbol table fails.
        Returns -1.
    3b. STR ends in ':' and is a valid label. Addition to symbol table succeeds.
        Returns 1.
 */
static int add_if_label(uint32_t input_line, char *str, uint32_t byte_offset,
                        SymbolTable *symtbl) {

  size_t len = strlen(str); /* add_if_label */
  if (str[len - 1] == ':') {
    str[len - 1] = '\0';
    if (is_valid_label(str)) {
      if (add_to_table(symtbl, str, byte_offset) == 0) { /* add_if_label */
        return 1;
      } else {
        return -1;
      } /* add_if_label */
    } else {
      raise_label_error(input_line, str);
      return -1; /* add_if_label */
    }
  } else {
    return 0;
  }
}

/*******************************
 * Implement the Following
 *******************************/

/* First pass of the assembler. You should implement pass_two() first.

   This function should read each line, strip all comments, scan for labels,
   and pass instructions to write_pass_one(). The symbol table should also
   been built and written to specified file. The input file may or may not
   be valid. Here are some guidelines:

    1. Only one label may be present per line. It must be the first token
   present. Once you see a label, regardless of whether it is a valid label or
   invalid label, treat the NEXT token as the beginning of an instruction.
    2. If the first token is not a label, treat it as the name of an
   instruction. DO NOT try to check it is a valid instruction in this pass.
    3. Everything after the instruction name should be treated as arguments to
        that instruction. If there are more than MAX_ARGS arguments, call
        raise_extra_argument_error() and pass in the first extra argument. Do
   not write that instruction to the output file (eg. don't call
   write_pass_one())
    4. Only one instruction should be present per line. You do not need to do
        anything extra to detect this - it should be handled by guideline 3.
    5. A line containing only a label is valid. The address of the label should
        be the byte offset of the next instruction, regardless of whether there
        is a next instruction or not.
    6. If an instruction contains an immediate, you should output it AS IS.
    7. Comments should always be skipped before any further process.

   Just like in pass_two(), if the function encounters an error it should NOT
   exit, but process the entire file and return -1. If no errors were
   encountered, it should return 0.
 */
int pass_one(FILE *input, FILE *inter, FILE *symtbl) {
  int a,flag=0;
  /* YOUR CODE HERE */
  int curr_lineno = 0, err = 0, BYTE_OFFSET = 0;
  SymbolTable *smt;
  /* A buffer for line parsing. */
  char buf[BUF_SIZE] __attribute__((unused));

  /* Variables for argument parsing. */
  char *args[MAX_ARGS] __attribute__((unused));
  int num_args __attribute__((unused));

  /* smt = create_table_from_file(SYMBOLTBL_UNIQUE_NAME, */
  /*                              symtbl); create symbol table from FILE */
  smt = create_table(SYMBOLTBL_UNIQUE_NAME);

  /* For each line, there are some hints of what you should do:
      1. Skip all comments
      2. Use `strtok()` to read next token
      3. Deal with labels
      4. Parse the instruction
   */
  while (fgets(buf, BUF_SIZE, input)) {
    char *token, *name; /* name = token */
    int i;    /*int j;*/
    ++curr_lineno;      /* line nym */
    skip_comments(buf); /*  1. Skip all comments */
    flag=0;
    if (strlen(buf) == 0)
      continue; /* skip empty line */

    token = strtok(buf, IGNORE_CHARS); /* depart */
    if (!token)
      continue;
    a = add_if_label(curr_lineno, token, BYTE_OFFSET, smt); /* add if label */
#ifdef DEBUG
    printf("%s:%d a=%d\n", __FILE__, __LINE__, a);
#endif
    /* Deal with labels */
    if (a == 1) /* valid label */
    {
      /* add_to_table(smt, token, BYTE_OFFSET); */
      token = strtok(NULL, IGNORE_CHARS);
      /* printf("token: %s\n", token); */

    } else if (a == -1) /* invalid label */
    {
      err = -1;
      continue; /* read next line */
    }
    if (!token) continue; 
    name = token;
    num_args = 0;
    while ((token = strtok(NULL, IGNORE_CHARS)) !=
           NULL) { /* Use `strtok()` to read next token */
      printf("token: %s\n", token);
      args[num_args] = token;

      if (num_args >= MAX_ARGS) { /* check */
        raise_extra_argument_error(curr_lineno, args[num_args]);
        err = -1;
        flag = 1;
        break; /* read next line */
      }
      ++num_args;
    }
  if(flag)
    continue;

#ifdef DEBUG /* debug */

    printf("%s:%d name:%s %d BEGIN write_pass_one\n", __FILE__, __LINE__, name, 
           num_args);
    for (j = 0; j < num_args; j++)
      printf("%s:%d name: %s, %s\n", __FILE__, __LINE__, name, args[j]);
#endif/* debug */

    if (!(i = write_pass_one(inter, name, args, num_args))) {
      raise_instruction_error(curr_lineno, name, args, num_args);
     /* DEBUG    */
      #ifdef DEBUG
     printf("%s:%d raise_instruction_error\n", __FILE__, __LINE__);
    #endif

      err = -1;
      continue; /* next line */
    }
    BYTE_OFFSET += i * 4;
  }
  write_table(smt, symtbl);
  free_table(smt);
  return err;
}

/* Second pass of the assembler.

   This function should read an intermediate file and the corresponding symbol
   table file, translates it into machine code. You may assume:
    1. The input file contains no comments
    2. The input file contains no labels
    3. The input file contains at maximum one instruction per line
    4. All instructions have at maximum MAX_ARGS arguments
    5. The symbol table file is well formatted
    6. The symbol table file contains all the symbol required for translation
   If an error is reached, DO NOT EXIT the function. Keep translating the rest
   of the document, and at the end, return -1. Return 0 if no errors were
   encountered. */
int pass_two(FILE *inter, FILE *symtbl, FILE *output) {
  /* YOUR CODE HERE */
  char *name, *token;
  int BYTE_OFFSET = 0, err = 0;
  SymbolTable *smt ;
  int curr_lineno = 0;                /* line number */

  /* A buffer for line parsing. */
  char buf[BUF_SIZE] __attribute__((unused));

  /* Variables for argument parsing. */
  char *args[MAX_ARGS] __attribute__((unused));
  int num_args __attribute__((unused));

  /* Write text segment. */
  fprintf(output, ".text\n");
    #ifdef DEBUG /* dubeg */
    printf("%s:%d .text\n", __FILE__, __LINE__);
    #endif
  smt = create_table_from_file(SYMBOLTBL_UNIQUE_NAME,
                               symtbl); /* create symbol table from FILE */
  /* Create symbol table here by reading the symbol table file. */

  /* For each line, there are some hints of what you should do:
      1. Get instruction name.
      2. Parse instruction arguments; Extra arguments should be filtered out in
       `pass_one()`, so you don't need to worry about that here.
      3. Use `translate_inst()` to translate the instruction and write to the
       output file;
      4. Or if an error occurs, call `raise_instruction_error()` instead of
     write the instruction.
   */
  while (fgets(buf, BUF_SIZE, inter) != NULL) {

    ++curr_lineno;
    name = token = strtok(buf, IGNORE_CHARS);
    num_args = 0;
    /* wrong => next line */
    if (!token)
      continue;

    while ((token = strtok(NULL, IGNORE_CHARS))) { /* depart */
      args[num_args] = token;
      ++num_args; 
    } 
#ifdef DEBUG /* debug */
    printf("%s:%d name:%s %d BEGIN translate_inst\n", __FILE__, __LINE__, name,
           num_args);
    for (j = 0; j < num_args; j++)
      printf("%s:%d name: %s, %s\n", __FILE__, __LINE__, name, *(args+j));
#endif/* debug */
    if (translate_inst(output, name, args, num_args, BYTE_OFFSET, smt) == -1) { /*err */
    #ifdef DEBUG/* debug */
     printf("%s:%d raise_instruction_error\n", __FILE__, __LINE__);
    #endif
      raise_instruction_error(curr_lineno, name, args, num_args);
      err = -1;
    }

    BYTE_OFFSET += 4; /* byteoffset */
  }

  /* Write symbol segment. */
  fprintf(output, "\n.symbol\n");
  /* Write symbols here by calling `write_table()` */
  write_table(smt, output);
  free_table(smt);
  return err;
}

/*******************************
 * Do Not Modify Code Below
 *******************************/

static int open_files_pass_one(FILE **input, FILE **inter, FILE **symtbl,
                               const char *input_name, const char *inter_name,
                               const char *symtbl_name) {

  *input = fopen(input_name, "r"); /* framework */
  if (!*input) {/* framework */
    write_to_log("Error: unable to open input file: %s\n", input_name);
    return -1;/* framework */
  }
  *inter = fopen(inter_name, "w");
  if (!*inter) {/* framework */
    write_to_log("Error: unable to open intermediate file: %s\n", inter_name);
    fclose(*input);
    return -1;/* framework */
  }
  *symtbl = fopen(symtbl_name, "w");/* framework */
  if (!*symtbl) {
    write_to_log("Error: unable to open symbol table file: %s\n", symtbl_name);/* framework */
    fclose(*input);
    fclose(*inter);/* framework */
    return -1;
  }/* framework */
  return 0;
}/* framework */

static int open_files_pass_two(FILE **inter, FILE **symtbl, FILE **output,
                               const char *inter_name, const char *symtbl_name,/* framework */
                               const char *output_name) {

  *inter = fopen(inter_name, "r");/* framework */
  if (!*inter) {
    write_to_log("Error: unable to open intermediate file: %s\n", inter_name);
    return -1;/* framework */
  }
  *symtbl = fopen(symtbl_name, "r");/* framework */
  if (!*symtbl) {
    write_to_log("Error: unable to open symbol table file: %s\n", inter_name);/* framework */
    fclose(*inter);
    return -1;
  }/* framework */
  *output = fopen(output_name, "w");/* framework */
  if (!*output) {
    write_to_log("Error: unable to open output file: %s\n", output_name);/* framework */
    fclose(*inter);
    fclose(*symtbl);
    return -1;/* framework */
  }
  return 0;
}/* framework */

static void close_files(FILE *file1, FILE *file2, FILE *file3) {/* framework */
  fclose(file1);
  fclose(file2);/* framework */
  fclose(file3);
}

/* Runs the two-pass assembler. Most of the actual work is done in pass_one()
   and pass_two().
 */
/* framework */
int assemble(const char *in, const char *out, const char *int_,
             const char *sym) {
  FILE *input, *inter, *symtbl, *output;/* framework */
  int err = 0;
/* framework */
  if (in) {/* framework */
    printf("Running pass one: %s -> %s, %s\n", in, int_, sym);/* framework */
    if (open_files_pass_one(&input, &inter, /* framework */&symtbl, in, int_, sym) != 0) {
      exit(1);
    }

    if (pass_one(input, inter, symtbl) != 0) {
      err = 1;/* framework */
    }/* framework */
    close_files(input, inter, symtbl);
  }/* framework */

  if (out) {
    printf("Running pass two: %s, %s -> %s\n", int_, sym, out);
    if (open_files_pass_two(&inter, &symtbl, &output, int_, sym, out) != 0) {
      exit(1);/* framework */
    }

    if (pass_two(inter, symtbl, output) /* framework */!= 0) {
      err = 1;
    }
/* framework */
    close_files(inter, symtbl, output);
  }

  return err;/* framework */
}

static void print_usage_and_exit() {
  printf("Usage:\n");
  printf("  Runs both passes: assembler <input file> <intermediate file> "/* framework */
         "<symbol table file> <output file>\n");
  printf("  Run pass #1:      assembler -p1 <input file> <intermediate file> "/* framework */
         "<symbol table file>\n");/* framework */
  printf("  Run pass #2:      assembler -p2 <intermediate file> <symbol table> "
         "<output file>\n");/* framework */
  printf("Append -log <file name> after any option to save log files to a text "/* framework */
         "file.\n");/* framework */
  exit(0);
}/* framework */
/* framework */
int main(int argc, char **argv) {
  int mode = 0;/* framework */
  char *input, *inter, *output, *symtbl;
  int err;/* framework */

  if (argc != 5 && argc != 7) {/* framework */
    print_usage_and_exit();
  }/* framework */

  if (strcmp(argv[1], "-p1") == 0) {
    mode = 1;/* framework */
  } else if (strcmp(argv[1], "-p2") == 0) {/* framework */
    mode = 2;
  }

  if (mode == 1) {/* framework */
    input = argv[2];/* framework */
    inter = argv[3];
    symtbl = argv[4];
    output = NULL;/* framework */
  } else if (mode == 2) {/* framework */
    input = NULL;
    inter = argv[2];/* framework */
    symtbl = argv[3];
    output = argv[4];
  } else {/* framework */
    input = argv[1];
    inter = argv[2];
    symtbl = argv[3];/* framework */
    output = argv[4];/* framework */
  }

  if (argc == 7) {/* framework *//* framework */
    if (strcmp(argv[5], "-log") == 0) {
      set_log_file(argv[6]);
    } else {
      print_usage_and_exit();/* framework */
    }
  }

  err = assemble(input, output, inter, symtbl);/* framework */

  if (err) {
    write_to_log("One or more errors encountered during assembly operation.\n");
  } else {
    write_to_log("Assembly operation completed successfully!\n");/* framework */
  }

  if (is_log_file_set()) {/* framework */
    printf("Results saved to %s\n", argv[5]);
  }

  return err;
}/* framework */
