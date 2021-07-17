#include "doubll2d.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void doubll2d_init(doubll2d *list) {
  /* Init head and tail */
  list->head = NULL;
  list->tail = NULL;

  /* Init value */
  list->dim_col = 0;
  list->dim_row = 0;
}

doubll2d_elem *doubll2d_get_head(doubll2d *list) {
  /* chech whet·her the return object is NULL or not */
  if (list != NULL)
    return list->head;
  return NULL;
}

doubll2d_elem *doubll2d_get_tail(doubll2d *list) {
  /* chech whether the return object is NULL or not */
  if (list != NULL)
    return list->tail;
  return NULL;
}

size_t doubll2d_dim_row(doubll2d *list) {
  /* chech whether the return object is NULL or not */
  if (list != NULL)
    return list->dim_row;
  return -1;
}

size_t doubll2d_dim_col(doubll2d *list) {
  /* chech whether the return object is NULL or not */
  if (list != NULL)
    return list->dim_col;
  return -1;
}
/*check */
int check(doubll2d *list, doubll2d_elem *cursor) {

  doubll2d_elem *begin_row, *begin_col;
  size_t i;
  size_t j; /*init */
  int cursor_exist;
  cursor_exist = 1; /* int cursor_exist = 1; */
  if (list == NULL)
    cursor_exist = 0;
  if (cursor == NULL) /* check mem 8 */
    cursor_exist = 0;
  /* init iter pointer */

  begin_row = list->head;
  begin_col = begin_row;

  /* iter from col and row
    TODO: use pointer iter
   */

  for (i = 0; i < list->dim_row; ++i) {
    for (j = 0; j < list->dim_col; ++j) {
      /* judge */
      if (begin_col == cursor) {
        /* aimed */
        cursor_exist = 0;
        break;
      }
      /* move */
      begin_col = begin_col->right;
    }
    /* continue */
    begin_row = begin_row->down;
    begin_col = begin_row;
  }

  /* final */
  return cursor_exist;
}

doubll2d_elem *doubll2d_insert_row(doubll2d *list, doubll2d_elem *cursor,
                                   void **data, size_t *size, size_t length) {
  size_t i; /* init */
  doubll2d_elem *front_ptr;
  doubll2d_elem *start_node;

  int pos_x;

  /* special */
  if (list->dim_row == 0 || cursor == NULL) {
    list->dim_col = list->dim_row = 1;
    if (length >= 1) {
      /* init elem*/
      doubll2d_elem *elem;
      elem = calloc(1, sizeof(doubll2d_elem));
      /* point */
      elem->left = elem->right = elem->up = elem->down = NULL;
      /* mem cpy */
      elem->data = calloc(1, *size);
      memcpy(elem->data, *data, *size);
      elem->size = *size;
      list->head = list->tail = elem;
      /* return */
      return elem;
    }
    /* exception */
    return NULL;
  }

/* check list */
#ifdef CHECK_LIST
  if (check(list, cursor))
    return NULL;
#endif

  /* init */

  pos_x = 1;

  start_node = cursor;
  /*  start node */
  while (start_node->left != NULL) {
    start_node = start_node->left;
    pos_x += 1;
  }

  /* length is more than required */
  if (list->dim_col <= length) {
    length = list->dim_col;
  }
  /* length is less than required */
  else {
    return NULL;
  }

  /* begin main process */

  front_ptr = NULL;

  for (i = 0; i < length; i++) {
    /* copy */
    doubll2d_elem *ptr = (doubll2d_elem *)calloc(1, sizeof(doubll2d_elem));
    ptr->size = *(size + i);
    ptr->data = calloc(1, ptr->size);
    memcpy(ptr->data, *(data + i), ptr->size);

    /* set up pointer to NULL */
    ptr->up = start_node;
    ptr->down = start_node->down;
    ptr->left = NULL;
    ptr->right = NULL;

    /* precess list */
    if (i + 1 == length) {
      if (start_node->down == NULL)
        list->tail = ptr;
      list->dim_row += 1;
    }

    /* point */
    start_node->down = ptr;

    /* process left */
    if (i) {
      ptr->left = front_ptr;
      front_ptr->right = ptr;
    }

    /* recursor */
    start_node = start_node->right;
    front_ptr = ptr;
  }

  return cursor->down;
}
/* doubll2d_insert_col */
doubll2d_elem *doubll2d_insert_col(doubll2d *list, doubll2d_elem *cursor,
                                   void **data, size_t *size, size_t length) {
  size_t i; /* init */
  doubll2d_elem *front_ptr;
  doubll2d_elem *start_node;
  int pos_y;

  /* special */
  if (list->dim_row == 0 || cursor == NULL) {
    list->dim_col = list->dim_row = 1;
    if (length >= 1) {
      /* init elem*/
      doubll2d_elem *elem;
      elem = calloc(1, sizeof(doubll2d_elem));
      /* point */
      elem->left = elem->right = elem->up = elem->down = NULL;
      /* mem cpy */
      elem->data = calloc(1, *size);
      memcpy(elem->data, *data, *size);
      elem->size = *size;
      list->head = list->tail = elem;
      return elem; /* return */
    }
    /* exception */
    return NULL;
  }

/* check list */
#ifdef CHECK_LIST
  if (check(list, cursor))
    return NULL;
#endif

  /* Calculate the position of cursor to the left.
      pos_x = (pos_x, y)
  */

  pos_y = 1;

  start_node = cursor; /* init */
  while (start_node->up != NULL) {
    start_node = start_node->up;
    pos_y += 1; /* += 1 */
  }

  /* length is more than required */
  if (list->dim_row <= length) {
    length = list->dim_row;
  }
  /* length is less than required */
  else {
    return NULL;
  }

  /* begin main process */

  front_ptr = NULL;

  for (i = 0; i < length; i++) {
    /* copy */
    doubll2d_elem *ptr = (doubll2d_elem *)calloc(1, sizeof(doubll2d_elem));
    ptr->size = *(size + i);
    ptr->data = calloc(1, ptr->size);
    memcpy(ptr->data, *(data + i), ptr->size); /* memcpy */

    /* set up pointer to NULL */
    ptr->up = NULL;
    ptr->down = NULL;
    ptr->left = start_node;
    ptr->right = start_node->right;

    /* precess list */
    if (i + 1 == length) {
      if (start_node->right == NULL)
        list->tail = ptr;
      list->dim_col += 1;
    }
    /* point */
    start_node->right = ptr;

    /* process left */
    if (i) {
      ptr->up = front_ptr;
      front_ptr->down = ptr;
    }

    /* recursor */
    start_node = start_node->down;
    front_ptr = ptr;
  }
  return cursor->right; /*  return cursor->right; */
}

/* doubll2d_delete_row_helper */
void doubll2d_delete_row_helper(doubll2d_elem *node) {
  if (node == NULL)
    return;
  if (node->up != NULL) /* check */
    node->up->down = node->down;
  if (node->down != NULL)
    node->down->up = node->up;
  if (node->right != NULL) /* check */
    node->right->left = NULL;
  if (node->left != NULL)
    node->left->right = NULL;

  if (node->left != NULL) /* check */
    doubll2d_delete_row_helper(node->left);
  if (node->right != NULL)
    doubll2d_delete_row_helper(node->right);
  free(node->data);
  free(node); /* free */
}
doubll2d_elem *doubll2d_delete_row(doubll2d *list, doubll2d_elem *cursor) {
  doubll2d_elem *ret; /* ret */
  ret = NULL;
  if (cursor == NULL)
    return NULL;
    /* check list */
#ifdef CHECK_LIST
  if (check(list, cursor))
    return NULL;
#endif
  if (cursor->up != NULL) { /* check */
    ret = cursor->up;
  } else if (cursor->down != NULL) {
    ret = cursor->down;
  }

  if (cursor->down == NULL) /* change */
    list->tail = list->tail->up;
  if (cursor->up == NULL)
    list->head = list->head->down;

  if ((list->dim_col >= 1 && list->dim_row >= 1)) { /* recursor */
    doubll2d_delete_row_helper(cursor);
    --(list->dim_row);
    return ret;
  }
  return NULL; /* return */
}

/* void doubll2d_delete_col_helper(doubll2d_elem *node) {
 */
void doubll2d_delete_col_helper(doubll2d_elem *node) {
  if (node == NULL)
    return;

  if (node->up != NULL) /* check */
    node->up->down = NULL;
  if (node->down != NULL)
    node->down->up = NULL;
  if (node->right != NULL) /* check */
    node->right->left = node->left;
  if (node->left != NULL)
    node->left->right = node->right;

  if (node->up != NULL) /* check */
    doubll2d_delete_col_helper(node->up);
  if (node->down != NULL)
    doubll2d_delete_col_helper(node->down);
  if (node != NULL) {
    free(node->data); /* free */
    free(node);
  }
}

doubll2d_elem *doubll2d_delete_col(doubll2d *list, doubll2d_elem *cursor) {
  doubll2d_elem *ret; /* ret */
  ret = NULL;
  if (cursor == NULL)
    return NULL;
    /* check list */
#ifdef CHECK_LIST
  if (check(list, cursor))
    return NULL;
#endif
  else if (cursor->left != NULL) /* check */
    ret = cursor->left;
  else if (cursor->right != NULL)
    ret = cursor->right;

  if (cursor->left == NULL) /* change */
    list->head = list->head->right;
  else if (cursor->right == NULL)
    list->tail = list->tail->left;

  if (list->dim_col >= 1 && list->dim_row >= 1) { /* recursor */
    doubll2d_delete_col_helper(cursor);
    --(list->dim_col);
    return ret;
  }
  return NULL; /* return */
}

void doubll2d_purge(doubll2d *list) { /* doubll2d_purge */
  if (list == NULL)
    return;
  while (list->head != NULL) {
    doubll2d_delete_row(list, list->head); /* recursor */
  }
  doubll2d_delete_row_helper(list->head);
  list->head = list->tail = NULL;
  list->dim_row = list->dim_col = 0; /* finish */
}
/* doubll2d_find_max_helper */
doubll2d_elem *doubll2d_find_max_helper(doubll2d_elem *node,
                                        list_less_func *less) {
  if (node->right != NULL && node->down != NULL) {
    doubll2d_elem *t = doubll2d_find_max_helper(node->right, less); /* t */
    doubll2d_elem *t1 = doubll2d_find_max_helper(node->down, less); /* t1 */
    doubll2d_elem *t2 = less(t, t1) ? t1 : t;                       /* t2 */
    return less(node, t2) ? t2 : node;
  } else if (node->right != NULL) {
    return less(node, doubll2d_find_max_helper(
                          node->right, less)) /* doubll2d_find_max_helper */
               ? doubll2d_find_max_helper(node->right, less)
               : node;
  } else if (node->down != NULL) { /* node->down  */
    return less(node, doubll2d_find_max_helper(node->down, less))
               ? doubll2d_find_max_helper(node->down, less)
               : node;
  } else
    return node; /* return node; */
}

doubll2d_elem *doubll2d_find_max(doubll2d *list, list_less_func *less) {
  /* When the 2D linked list is empty, return NULL. */
  if (list->dim_col == 0 || list->dim_col == 0)
    return NULL;
  return doubll2d_find_max_helper(list->head, less);
}

/* doubll2d_find_min_helper */
doubll2d_elem *
doubll2d_find_min_helper(doubll2d_elem *node, /* *doubll2d_find_min_helper */
                         list_less_func *less) {
  if (node->right != NULL && node->down != NULL) {
    doubll2d_elem *t = doubll2d_find_min_helper(node->right, less); /* t */
    doubll2d_elem *t1 = doubll2d_find_min_helper(node->down, less); /* t1 */
    doubll2d_elem *t2 = less(t, t1) ? t : t1;                       /* t2 */
    return less(node, t2) ? node : t2;
  } else if (node->right != NULL) {
    return less(node, doubll2d_find_min_helper(node->right, less)) /* return */
               ? node
               : doubll2d_find_max_helper(node->right, less);
  } else if (node->down != NULL) { /* else */
    return less(node, doubll2d_find_min_helper(node->down, less))
               ? node
               : doubll2d_find_max_helper(node->down, less);
  } else
    return node; /* return */
}
doubll2d_elem *doubll2d_find_min(
    doubll2d *list,
    list_less_func *less) { /* When the 2D linked list is empty, return NULL. */
  if (list->dim_col == 0 || list->dim_col == 0)
    return NULL;
  return doubll2d_find_min_helper(list->head, less); /* return */
}
