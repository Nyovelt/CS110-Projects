#include "doubll2d.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void List2D_PrintList(doubll2d *list);
void List2D_PrintChain(doubll2d_elem *chain);
void List2D_Free(doubll2d *list);
void Data_shift(int shift);
void Data_free();

bool lessThan(doubll2d_elem *a, doubll2d_elem *b);

#define N 1010
doubll2d list;
void *data[N];
size_t size[N];

int main() {
  /* 初始化 data */
  int i;
  doubll2d_elem *result;
  for (i = 0; i < N; ++i)
    data[i] = NULL;
  data[0] = malloc(sizeof(int));
  size[0] = sizeof(int);
  *((int *)(data[0])) = 0;
  data[1] = malloc(sizeof(int));
  size[1] = sizeof(int);
  *((int *)(data[1])) = 1;
  data[2] = malloc(sizeof(int));
  size[2] = sizeof(int);
  *((int *)(data[2])) = 2;
  data[3] = malloc(sizeof(int));
  size[3] = sizeof(int);
  *((int *)(data[3])) = 3;
  data[4] = malloc(sizeof(int));
  size[4] = sizeof(int);
  *((int *)(data[4])) = 4;
  data[5] = malloc(sizeof(int));
  size[5] = sizeof(int);
  *((int *)(data[5])) = 5;
  /* 初始化 list */
  /* test row */
  doubll2d_init(&list);
  result = doubll2d_insert_row(&list, NULL, data, size, 2);
  Data_shift(10); // List2D_PrintList(&list);
  result = doubll2d_insert_row(&list, list.head, data, size, 2);
  Data_shift(10); // List2D_PrintList(&list);
  result = doubll2d_insert_row(&list, list.head, data, size, 2);
  Data_shift(10); // List2D_PrintList(&list);
  ///* test col */
  result = doubll2d_insert_col(&list, list.tail, data, size, 4);
  Data_shift(10); // List2D_PrintList(&list);
  result = doubll2d_insert_col(&list, list.head, data, size, 4);
  Data_shift(10); // List2D_PrintList(&list);
  result = doubll2d_insert_row(&list, list.head, data, size, 4);
  Data_shift(10); // List2D_PrintList(&list);
  result = doubll2d_insert_col(&list, list.head->right, data, size, 4);
  Data_shift(10); // List2D_PrintList(&list);
  result = doubll2d_delete_row(&list, list.head->down);
  Data_shift(10); // List2D_PrintList(&list);
  result = doubll2d_insert_row(&list, list.tail->left, data, size, 4);
  Data_shift(10); // List2D_PrintList(&list);
  result = doubll2d_insert_row(&list, list.tail->up, data, size, 4);
  Data_shift(10); // List2D_PrintList(&list);
  result = doubll2d_insert_col(&list, list.tail->left, data, size, 5);
  Data_shift(10);
  List2D_PrintList(&list);
  result = doubll2d_insert_col(&list, list.tail, data, size, 6);
  Data_shift(10);
  List2D_PrintList(&list);
  result = doubll2d_insert_row(&list, list.tail, data, size, 6);
  Data_shift(10);
  List2D_PrintList(&list);
  result = doubll2d_insert_col(&list, list.tail, data, size, 6);
  Data_shift(10);
  List2D_PrintList(&list);
  result = doubll2d_insert_row(&list, list.tail, data, size, 6);
  Data_shift(10);
  List2D_PrintList(&list);
  result = doubll2d_insert_col(&list, list.tail, data, size, 6);
  Data_shift(10);
  List2D_PrintList(&list);
  printf("max value = %d\n",
         *((int *)(doubll2d_find_max(&list, lessThan)->data))); // max = 155
  printf("min value = %d\n",
         *((int *)(doubll2d_find_min(&list, lessThan)->data))); // min = 0
  result = doubll2d_delete_row(&list, list.head->right->right->down->down);
  Data_shift(10);
  List2D_PrintList(&list);
  result = doubll2d_delete_col(&list, list.head);
  Data_shift(10);
  List2D_PrintList(&list);
  result = doubll2d_delete_row(&list, list.tail);
  Data_shift(10);
  List2D_PrintList(&list);
  result = doubll2d_delete_col(&list, list.tail);
  Data_shift(10);
  List2D_PrintList(&list);
  result = doubll2d_delete_row(&list, list.head);
  Data_shift(10);
  List2D_PrintList(&list);
  result = doubll2d_delete_col(&list, list.tail->left);
  Data_shift(10);
  List2D_PrintList(&list);
  result = doubll2d_delete_row(&list, list.head->right);
  Data_shift(10);
  List2D_PrintList(&list);
  result = doubll2d_delete_col(&list, list.tail);
  Data_shift(10);
  List2D_PrintList(&list);
  result = doubll2d_delete_row(&list, list.head);
  Data_shift(10);
  List2D_PrintList(&list);
  result = doubll2d_delete_row(&list, list.tail);
  Data_shift(10);
  List2D_PrintList(&list);
  result = doubll2d_delete_row(&list, list.tail);
  Data_shift(10);
  List2D_PrintList(&list);
  printf("cursor address = %p\n", (void *)result); // result = NULL
  doubll2d_purge(&list);
  List2D_Free(&list);
  Data_free();
  return 0;
}

void List2D_Free(doubll2d *list) {
  doubll2d_elem *itBegin, *it;
  if (list == NULL)
    return;
  itBegin = list->head, it = itBegin;
  while (itBegin != NULL) {
    itBegin = itBegin->down;
    while (it != NULL) {
      doubll2d_elem *freed = it;
      it = it->right;
      free(freed->data);
      free(freed);
    }
    it = itBegin;
  }
}

void List2D_PrintList(doubll2d *list) {
  doubll2d_elem **rowBuffer;
  doubll2d_elem *itBegin, *it;
  if (list == NULL || list->head == NULL || list->tail == NULL) {
    printf("Empty\n\n");
    return;
  }
  printf("---------------------------------------------------------------\n");
  printf("ROW = %ld    COL = %ld\n", (long unsigned int)list->dim_row,
         (long unsigned int)list->dim_col);
  rowBuffer = malloc(sizeof(doubll2d_elem *) * list->dim_col);
  itBegin = list->head;
  it = itBegin;
  while (true) {
    size_t i = 0;
    itBegin = itBegin->down;
    while (it != NULL) {
      rowBuffer[i++] = it;
      it = it->right;
    }
    for (i = 0; i < list->dim_col; ++i) {
      printf("p=%p   ", (void *)rowBuffer[i]);
    }
    putchar('\n');
    for (i = 0; i < list->dim_col; ++i) {
      printf("v=%d          ", *((int *)(rowBuffer[i]->data)));
    }
    putchar('\n');
    for (i = 0; i < list->dim_col; ++i) {
      printf("s=%ld          ", (unsigned long int)rowBuffer[i]->size);
    }
    putchar('\n');
    for (i = 0; i < list->dim_col; ++i) {
      printf("u=%p   ", (void *)rowBuffer[i]->up);
    }
    putchar('\n');
    for (i = 0; i < list->dim_col; ++i) {
      printf("d=%p   ", (void *)rowBuffer[i]->down);
    }
    putchar('\n');
    for (i = 0; i < list->dim_col; ++i) {
      printf("l=%p   ", (void *)rowBuffer[i]->left);
    }
    putchar('\n');
    for (i = 0; i < list->dim_col; ++i) {
      printf("r=%p   ", (void *)rowBuffer[i]->right);
    }
    putchar('\n');
    if (itBegin == NULL)
      break;
    else {
      it = itBegin;
      putchar('\n');
    }
  }
  free(rowBuffer);
  printf("---------------------------------------------------------------\n");
  putchar('\n');
  putchar('\n');
}

void List2D_PrintChain(doubll2d_elem *chain) {
  doubll2d_elem *it;
  for (it = chain; it != NULL; it = it->right) {
    printf("p=%p   ", (void *)it);
  }
  putchar('\n');
  for (it = chain; it != NULL; it = it->right) {
    printf("v=%d          ", *((int *)(it->data)));
  }
  putchar('\n');
  for (it = chain; it != NULL; it = it->right) {
    printf("s=%ld          ", (long unsigned int)it->size);
  }
  putchar('\n');
  for (it = chain; it != NULL; it = it->right) {
    printf("l=%p   ", (void *)it->left);
  }
  putchar('\n');
  for (it = chain; it != NULL; it = it->right) {
    printf("r=%p   ", (void *)it->right);
  }
  putchar('\n');
  putchar('\n');
}

bool lessThan(doubll2d_elem *a, doubll2d_elem *b) {
  return *((int *)(a->data)) < *((int *)(b->data));
}

void Data_shift(int shift) {
  for (int i = 0; i < 6; ++i) {
    *((int *)(data[i])) += shift;
  }
}

void Data_free() {
  int i;
  for (i = 0; i < N; ++i) {
    if (data[i] != NULL)
      free(data[i]);
  }
}
