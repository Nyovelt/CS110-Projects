/* This project is based on the MIPS Assembler of CS61C in UC Berkeley.
   The framework of this project is been modified to be suitable for RISC-V
   in CS110 course in ShanghaiTech University by Zhijie Yang in March 2019.
   Updated by Chibin Zhang and Zhe Ye in March 2021.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tables.h"
#include "utils.h"
/*
const int SYMBOLTBL_NON_UNIQUE = 0;
const int SYMBOLTBL_UNIQUE_NAME = 1;
*/
#define MAX_LINE 1024
/*******************************
 * Helper Functions
 *******************************/

void allocation_failed() { /*( allocation_failed() */
  write_to_log("Error: allocation failed\n");
  exit(1);
}

void addr_alignment_incorrect() { /* addr_alignment_incorrect()  */
  write_to_log("Error: address is not a multiple of 4.\n");
}

void name_already_exists(const char *name) { /* name_already_exists(const char *name)  */
  write_to_log("Error: name '%s' already exists in table.\n", name);
}

void write_sym(FILE *output, uint32_t addr, const char *name) { /* void write_sym(FILE *output, uint32_t addr, const char *name)  */
  fprintf(output, "%u\t%s\n", addr, name);
}

/*******************************
 * Symbol Table Functions
 *******************************/

/* Creates a new SymbolTable containg 0 elements and returns a pointer to that
   table. Multiple SymbolTables may exist at the same time.
   If memory allocation fails, you should call allocation_failed().
   Mode will be either SYMBOLTBL_NON_UNIQUE or SYMBOLTBL_UNIQUE_NAME. You will
   need to store this value for use during add_to_table().
 */
SymbolTable *create_table(int mode) {
  /* Create SymbolTable */
  SymbolTable *smt =
      (SymbolTable *)calloc(1, sizeof(SymbolTable)); /* clloc mem */
  if (!smt)                                          /* nptr check */
    allocation_failed();                             /* error handle */
  /* init begin */
  smt->len = 0;                                          /* no elm */
  smt->cap = INCREMENT_OF_CAP;                           /* 1 cap */
  smt->sym = (Symbol *)calloc(smt->cap, sizeof(Symbol)); /* dym mem */
  if (!(smt->sym))                                       /* check mem */
    allocation_failed();                                 /* error handle */
  smt->mode = mode;                                      /* inherit mode */
  return smt; /* ret ptr (CAN BE NULL) */
}

/* Frees the given SymbolTable and all associated memory. */
void free_table(SymbolTable *table) {
  Symbol *sym = table->sym;
  uint32_t i = 0;
  /* YOUR CODE HERE */
  if (!table) /* mem check */
    return;

  /* for to free dym -> *sym ( MAY CONTAINS BUGS: USE for i in len instead.) */
  for (i = 0; i < table->len; ++i) { /* sym is *( Symbol+i ) in SymbolTable */

    free(sym->name);
    ++sym;
  }

  free(table->sym);
  free(table); /* free itself */
}

/* Adds a new symbol and its address to the SymbolTable pointed to by TABLE.
   1. ADDR is given as the byte offset from the first instruction.
*/
/*
   2. The SymbolTable must be able to resize itself as more elements are added.

   3. Note that NAME may point to a temporary array, so it is not safe to simply
   store the NAME pointer. You must store a copy of the given string.
*/
/*
   4. If ADDR is not word-aligned, you should call addr_alignment_incorrect()
   and return -1.
*/
/*
   5. If the table's mode is SYMTBL_UNIQUE_NAME and NAME already exists
   in the table, you should call name_already_exists() and return -1.
*/
/*
   6.If memory allocation fails, you should call allocation_failed().

   Otherwise, you should store the symbol name and address and return 0.
 */
int add_to_table(SymbolTable *table, const char *name,
                 uint32_t addr) { /* init ptr to Symbol ready to add */
  Symbol *add = (table->sym + table->len);
  Symbol *sym = table->sym;
  uint32_t i = 0;
  /* YOUR CODE HERE */
  if (!table) /* mem check */
    return -1;
  if (!table) /* mem check */
    return -1;
  /* 4. If ADDR is not word-aligned, you should call addr_alignment_incorrect()
   */
  /*     and return -1. */
  if (addr % 4) {
    addr_alignment_incorrect();
    return -1;
  }

  /* 5. If the table's mode is SYMTBL_UNIQUE_NAME and NAME already exists */
  /*    in the table, you should call name_already_exists() and return -1. */
  if (table->mode == SYMBOLTBL_UNIQUE_NAME) {
    for (i = 0; i < table->len; ++i) {
      if (strcmp(name, sym->name) == 0) {
        /* test */
        #ifdef DEBUG
          printf("%s:%d name already exists\n", __FILE__, __LINE__);
        #endif
        /* test */
        name_already_exists(name);
        return -1;
      }
      ++sym;
    }
  }

  add->addr = addr; /* cpy */
  add->name = (char *)calloc(5, sizeof(name));
  /* memcpy(add->name, name, sizeof(name));*/ /* memcpy */
  strcpy(add->name, name);
  /* 6. If memory allocation fails, you should call allocation_failed(). */
  if (!(add->name))
    allocation_failed();
    /* failed */
  ++(table->len);

  /* 2. The SymbolTable must be able to resize itself as more elements are
   added. */
  if ((table->len) == (table->cap)) {
    table->cap += INCREMENT_OF_CAP;
    /* */
    table->sym = (Symbol *)realloc(table, table->cap * sizeof(Symbol));
  }

  if (!(table->sym))
    allocation_failed();

  /*  Otherwise, you should store the symbol name and address and return 0. */
  return 0;
}

/* Returns the address (byte offset) of the given symbol. If a symbol with name
   NAME is not present in TABLE, return -1.
 */
int64_t get_addr_for_symbol(SymbolTable *table, const char *name) {
  uint32_t i = 0;
  Symbol *sym = table->sym;
  /* YOUR CODE HERE */
  if (!table)
    return -1;
  /* */
  for (i = 0; i < table->len;++i ) {
    if (strcmp(name, sym->name) == 0)
    /* */
      return sym
          ->addr; /* Returns the address (byte offset) of the given symbol. */
  ++sym;
  }
  
  return -1; /*  If a symbol with name NAME is not present in TABLE, return -1.
              */
}

/* Writes the SymbolTable TABLE to OUTPUT. You should use write_sym() to
   perform the write. Do not print any additional whitespace or characters.
 */
void write_table(SymbolTable *table, FILE *output) {
  /**/
  uint32_t i = 0;
  Symbol *sym = table->sym;
  /* YOUR CODE HERE */
  if (!table || !output)
    return;
  /*sym*/
  for (i = 0; i < table->len; ++i) {
    write_sym(output, sym->addr, sym->name);
    ++sym;
  }
}

/* Reads the symbol table file written by the `write_table` function, and
   restore the symbol table.
 */
SymbolTable *create_table_from_file(int mode, FILE *file) { /*  init return */

  SymbolTable *ret;
  char buf[1024];
  /* */
  uint32_t addr;
  char name[50];

  ret = create_table(mode);
  while (fgets(buf, 1024, file)) {
    /* */
    sscanf(buf, "%u %s", &addr, name);
    /*debug*/
#ifdef DEBUG
    printf("%s:%d name: %s , address: %u \n", __FILE__, __LINE__, name, addr);
#endif
  /* */
  add_to_table(ret, name, addr);
  }

  /* return */
  return ret;
}
