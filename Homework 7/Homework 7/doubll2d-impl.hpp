
using namespace __detail;

template <typename T>
typename list_row_elem_iter<T>::reference list_row_elem_iter<T>::operator*() {
  return inner->data; // return the data TOO: or reference
}

// pointer operator (implement this)
template <typename T>
typename list_row_elem_iter<T>::pointer list_row_elem_iter<T>::operator->() {
  return &(inner->data); // return itself
}

// self increment operator (implement this)
// move to the right element
template <typename T>
list_row_elem_iter<T> &list_row_elem_iter<T>::operator++() {
  inner = inner->right; // next element in the row
  return *this;         // return node ++
}

template <typename T>
list_row_elem_iter<T> list_row_elem_iter<T>::operator++(int) { // increment
  list_row_elem_iter<T> temp(*this);
  operator++();
  return temp;
  // TODO: check the correctness
}

// self decrement operator (implement this)
// move to the left element
//  operator-- represents the last left element in this row
// TODO: check the mean of the `last left element`
template <typename T>
list_row_elem_iter<T> &list_row_elem_iter<T>::operator--() {
  inner = inner->left;
  return *this;
}

template <typename T>
list_row_elem_iter<T> list_row_elem_iter<T>::operator--(int) {
  list_row_elem_iter<T> temp(*this);
  operator--();
  return temp;
}

// comparison operator (implement this)
// ==
template <typename T>
bool list_row_elem_iter<T>::operator==(const list_row_elem_iter &other) {
  return inner == other.inner; // ==
}

// !=
template <typename T>
bool list_row_elem_iter<T>::operator!=(const list_row_elem_iter &other) {
  return inner != other.inner; //!=
}

// reference operator (implement this)
template <typename T>
typename list_col_elem_iter<T>::reference list_col_elem_iter<T>::operator*() {
  return (inner->data);
}

// pointer operator (implement this)
template <typename T>
typename list_col_elem_iter<T>::pointer list_col_elem_iter<T>::operator->() {
  return &(inner->data);
}

// self increment operator (implement this)
// move to the element below
template <typename T>
list_col_elem_iter<T> &list_col_elem_iter<T>::operator++() {
  inner = inner->down; // operator++ represents the element below
  return *this;        // return node ++
}

template <typename T>
list_col_elem_iter<T> list_col_elem_iter<T>::operator++(int) {
  list_col_elem_iter<T> temp(*this);
  operator++();
  return temp;
  // TODO: check the correctness
}

// self decrement operator (implement this)
// move to the element above
template <typename T>
list_col_elem_iter<T> &list_col_elem_iter<T>::operator--() {
  // up
  inner = inner->up;
  return *this;
}

template <typename T>
list_col_elem_iter<T> list_col_elem_iter<T>::operator--(int) {
  list_col_elem_iter<T> temp(*this);
  operator--();
  return temp;
  // TODO: check the correctness
}

// comparison operator (implement this)
template <typename T>
bool list_col_elem_iter<T>::operator==(const list_col_elem_iter &other) {
  return inner == other.inner; // ==
}

template <typename T>
bool list_col_elem_iter<T>::operator!=(const list_col_elem_iter &other) {
  return inner != other.inner; // !=
}

// the leftmost iterator of this row (implement this)
template <typename T> list_row_elem_iter<T> list_row_iter<T>::begin() {
  return list_row_elem_iter<T>(left);
}

// the iterator next to the rightmost element in this row (implement this)
template <typename T> list_row_elem_iter<T> list_row_iter<T>::end() {

  return list_row_elem_iter<T>(nullptr);

  // TOD: if right is nullptr (No need to worry about )
}

// the `reverse_iterator` of the rightmost element in this row (implement
// this)
template <typename T>
reverse_iter<list_row_elem_iter<T>> list_row_iter<T>::rbegin() {
  return reverse_iter<list_row_elem_iter<T>>(list_row_elem_iter<T>(right));
}

// the `reverse_iterator` before the leftmost element in this row (implement
// this)
template <typename T>
reverse_iter<list_row_elem_iter<T>> list_row_iter<T>::rend() {
  // TOD: if left is null

  return reverse_iter<list_row_elem_iter<T>>(list_row_elem_iter<T>(nullptr));
}

// reference operator (implement this)
template <typename T>
typename list_row_iter<T>::reference list_row_iter<T>::operator*() {
  return *this;

  // TOD: what about right
}

// pointer operator (implement this)
template <typename T>
typename list_row_iter<T>::pointer list_row_iter<T>::operator->() {
  return this;
  // TOD: ->
}

// self increment operator (implement this)
// move to the row below
template <typename T> list_row_iter<T> &list_row_iter<T>::operator++() {
  // TOD: nullptr?
  left = left->down; // below
  right = right->down;
  return *this;
}

template <typename T> list_row_iter<T> list_row_iter<T>::operator++(int) {
  list_row_iter<T> temp(left, right);
  ++(*this);
  return temp;
}

// self decrement operator (implement this)
// move to the row above
template <typename T> list_row_iter<T> &list_row_iter<T>::operator--() {
  left = left->up;
  right = right->up;
  return *this;
}

template <typename T> list_row_iter<T> list_row_iter<T>::operator--(int) {
  list_row_iter<T> temp(left, right);
  --(*this);
  return temp;
}

// comparison operator (implement this)
template <typename T>
bool list_row_iter<T>::operator==(const list_row_iter &other) {
  return (left == other.left) && (right == other.right);
}
template <typename T>
bool list_row_iter<T>::operator!=(const list_row_iter &other) {
  return (left != other.left) || (right != other.right);
}

// the top iterator of this column (implement this)
// the top iterator of this column (implement this)
template <typename T> list_col_elem_iter<T> list_col_iter<T>::begin() {
  return list_col_elem_iter<T>(up);
}

// the iterator below the bottom element in this column (implement this)
template <typename T> list_col_elem_iter<T> list_col_iter<T>::end() {

  return list_col_elem_iter<T>(nullptr);

  // TOD: what if nullptr
}

// the `reverse_iterator` of the bottom element in this column (implement
// this)
template <typename T>
reverse_iter<list_col_elem_iter<T>> list_col_iter<T>::rbegin() {
  return reverse_iter<list_col_elem_iter<T>>(list_col_elem_iter<T>(down));
}

// the `reverse_iterator` above the top element in this column (implement
// this)
template <typename T>
reverse_iter<list_col_elem_iter<T>> list_col_iter<T>::rend() {

  return reverse_iter<list_col_elem_iter<T>>(list_col_elem_iter<T>(nullptr));

  // TOOD: what if nullptr
}

// reference operator (implement this)
template <typename T>
typename list_col_iter<T>::reference list_col_iter<T>::operator*() {
  return *this;
  // TOD: what about down
}

// pointer operator (implement this)
template <typename T>
typename list_col_iter<T>::pointer list_col_iter<T>::operator->() {
  return this;
  // TOD: what about down
}

// self increment operator (implement this)
// move to the next column
template <typename T> list_col_iter<T> &list_col_iter<T>::operator++() {
  up = up->right;
  down = down->right; // right
  return *this;
}

template <typename T> list_col_iter<T> list_col_iter<T>::operator++(int) {
  list_col_iter<T> temp(up, down);
  ++(*this);
  return temp;
}

// self decrement operator (implement this)
// move to the previous column
template <typename T> list_col_iter<T> &list_col_iter<T>::operator--() {
  up = up->left;
  down = down->left; // left
  return *this;
}

template <typename T> list_col_iter<T> list_col_iter<T>::operator--(int) {
  list_col_iter<T> temp(up, down);
  --(*this);
  return temp;
}

// comparison operator (implement this)
template <typename T>
bool list_col_iter<T>::operator==(const list_col_iter &other) {
  return (up == other.up) && (down == other.down);
}

template <typename T>
bool list_col_iter<T>::operator!=(const list_col_iter &other) {
  return (up != other.up) || (down != other.down);
}

// Iterator to the first (top) row (implement this)
template <typename T> list_row_iter<T> doubll2d<T>::row_begin() {
  return list_row_iter<T>(up_left, up_right);
}

// Iterator below the last (bottom) row (implement this)
template <typename T> list_row_iter<T> doubll2d<T>::row_end() {

  return list_row_iter<T>(nullptr, nullptr);
}

// `reverse_iterator` to the last (bottom) row (implement this)
template <typename T> reverse_iter<list_row_iter<T>> doubll2d<T>::row_rbegin() {
  return reverse_iter<list_row_iter<T>>(
      list_row_iter<T>(down_left, down_right));
}

// `reverse_iterator` above the first (top) row (implement this)
template <typename T> reverse_iter<list_row_iter<T>> doubll2d<T>::row_rend() {

  return reverse_iter<list_row_iter<T>>(list_row_iter<T>(nullptr, nullptr));
}

// Iterator to the first (leftmost) column (implement this)
template <typename T> list_col_iter<T> doubll2d<T>::col_begin() {
  return list_col_iter<T>(up_left, down_left);
}

// Iterator after the last (rightmost) column (implement this)
template <typename T> list_col_iter<T> doubll2d<T>::col_end() {

  return list_col_iter<T>(nullptr, nullptr);
}

// `reverse_iterator` to the last (rightmost) column (implement this)
template <typename T> reverse_iter<list_col_iter<T>> doubll2d<T>::col_rbegin() {
  return reverse_iter<list_col_iter<T>>(list_col_iter<T>(up_right, down_right));
}

// `reverse_iterator` before the first (leftmost) column (implement this)
template <typename T> reverse_iter<list_col_iter<T>> doubll2d<T>::col_rend() {

  return reverse_iter<list_col_iter<T>>(list_col_iter<T>(nullptr, nullptr));
}

// Insert a new row in the list below the row referenced by `cursor`.
// The data stores from `input_iter` `begin` to `end`. (implement this)
//
// Remember, our 2D doubly linked list should always be a rectangular. When
// the length of data is shorter than it should be, you should fill the rest
// part by default value of T. Additionally, it is okay that the length of
// data is longer than needed, in this case you should make use of the
// `dim_col` items from `begin` and ignore the extra elements.
//
// If the list is empty, you should insert the whole data from `begin` to
// `end`. If the list is empty and `begin` equals to `end`, do nothing and
// return `row_end()`.
//
// If the cursor equals to `row_end()` operator, insert the data above the
// origin first row.
//
// Return the iter of the row inserted.
template <typename T>
template <typename input_iter>
list_row_iter<T> doubll2d<T>::insert_row(list_row_iter<T> cursor,
                                         input_iter begin, input_iter end) {
  // If the list is empty and begin equals to end, do nothing and return
  // col_end().
  if ((begin == end) && ((!get_dim_row()) || (!get_dim_col())))
    // if ((begin == end))
    return row_end();
  list_node<T> *start_node = nullptr;
  list_node<T> *end_node = nullptr;
  list_node<T> *front_ptr = nullptr;
  list_node<T> *_iter = nullptr;
  size_t count = 0; // the count of row elements
  // If the list is empty, you should insert the whole data from begin to end.
  int flag = 0;
  list_row_elem_iter<T> _cursor(nullptr);

  if (cursor == row_end()) {
    list_row_elem_iter<T> __cursor(up_left);
    _cursor = __cursor;
    flag = 1;
  } else if (cursor.begin().inner == down_left) {
    list_row_elem_iter<T> __cursor(cursor.begin().inner);
    _cursor = __cursor;
    flag = 2;
  } else {
    list_row_elem_iter<T> __cursor(cursor.begin().inner);

    _cursor = __cursor;
    flag = 3;
  }

  if ((!get_dim_row()) || (!get_dim_col())) {

    for (auto iter = begin; iter != end; ++iter) {
      list_node<T> *i = new list_node<T>(*iter);
      if (!count) { // The first element
        up_left = down_left = i;
      } else { // Not the first element
        front_ptr->right = i;
        i->left = front_ptr;
      }

      front_ptr = i;
      count++;
    }

    up_right = down_right = front_ptr; // iter = end

    dim_row = 1;
    dim_col = count;
    return list_row_iter<T>(up_left, up_right);
  } else {

    dim_row++;
    auto insert_iter = begin;
    int is_insert_end = 0;
    for (size_t i = 1; i <= dim_col; i++, count++) {

      if ((!is_insert_end) && insert_iter == end)
        is_insert_end = 1;
      if (is_insert_end) {
        _iter = new list_node<T>(T());
      } else {
        _iter = new list_node<T>(*insert_iter);
        insert_iter++;
      } // init nodes

      if (flag == 1) {

        // list_row_elem_iter<T> _cursor(up_left);
        auto node = _cursor.inner;
        if (!count) {
          up_left = _iter;
          start_node = _iter;
        } else {
          _iter->left = front_ptr;
          front_ptr->right = _iter;
        }
        front_ptr = _iter;
        node->up = _iter;

        _iter->down = node;
        if (i == dim_col)
          up_right = _iter;
        end_node = _iter;
        _cursor++;

      } else if (flag == 2) {

        // list_row_elem_iter<T> _cursor(cursor.begin().inner);
        auto node = _cursor.inner;

        if (!count) {
          down_left = _iter;
          start_node = _iter;
        } else {
          _iter->left = front_ptr;
          front_ptr->right = _iter;
        }
        front_ptr = _iter;
        node->down = _iter;
        _iter->up = node;
        if (i == dim_col) {
          down_right = _iter;
          end_node = _iter;
        }

        _cursor++;

        // std::cout << "Remove me: " << i << std::endl;
      } else if (flag == 3) {
        // std::cout << "Remove me: " << i << std::endl;
        // list_row_elem_iter<T> _cursor(cursor.begin().inner);
        auto node = _cursor.inner;
        if (count) {
          _iter->left = front_ptr;
          front_ptr->right = _iter;
        } else {
          start_node = _iter;
        }
        front_ptr = _iter;
        _iter->up = node;
        _iter->down = node->down;
        node->down->up = _iter;
        node->down = _iter;

        if (i == dim_col) {
          end_node = _iter;
        }
        _cursor++;
      }
    }
    return list_row_iter<T>(start_node, end_node);
  }
}

// Insert a new column in the list after the column referenced by `cursor`.
// The data stores from `input_iter` `begin` to `end`. (implement this)
//
// Remember, our 2D doubly linked list should always be a rectangular. When
// the length of data is shorter than it should be, you should fill the rest
// part by default value of T. Additionally, it is okay that the length of
// data is longer than needed, in this case you should make use of the first
// `dim_row` items from `begin` and ignore the extra elements.
//
// If the list is empty, you should insert the whole data from `begin` to
// `end`. If the list is empty and `begin` equals to `end`, do nothing and
// return `col_end()`.
//
// If the cursor is `col_end()` operator, insert the data before the origin
// first column.
//
// Return the iter of the column inserted.
template <typename T>
template <typename input_iter>
list_col_iter<T> doubll2d<T>::insert_col(col_iter cursor, input_iter begin,
                                         input_iter end) {
  if ((begin == end) && ((!get_dim_row()) || (!get_dim_col())))
    return col_end();
  list_node<T> *start_node = nullptr;
  list_node<T> *end_node = nullptr;
  list_node<T> *front_ptr = nullptr;
  list_node<T> *_iter = nullptr;
  size_t count = 0; // the count of row elements
  // If the list is empty, you should insert the whole data from begin to
  // end.

  int flag = 0;
  list_col_elem_iter<T> _cursor(nullptr);

  if (cursor == col_end()) {
    list_col_elem_iter<T> __cursor(up_left);
    _cursor = __cursor;
    flag = 1;
  } else if (cursor.begin().inner == up_right) {
    list_col_elem_iter<T> __cursor(cursor.begin().inner);
    _cursor = __cursor;
    flag = 2;
  } else {
    list_col_elem_iter<T> __cursor(cursor.begin().inner);

    _cursor = __cursor;
    flag = 3;
  }

  if ((!get_dim_row()) || (!get_dim_col())) {

    for (auto iter = begin; iter != end; ++iter) {
      list_node<T> *i = new list_node<T>(*iter);
      if (!count) { // The first element
        up_left = up_right = i;
        // start_node = i;
      } else { // Not the first element
        front_ptr->down = i;
        i->up = front_ptr;
      }

      front_ptr = i;
      count++;
    }

    down_left = down_right = front_ptr; // iter = end

    dim_row = count;
    dim_col = 1;
    return list_col_iter<T>(up_left, down_left);
  } else {
    dim_col++;
    auto insert_iter = begin;
    int is_insert_end = 0;
    for (size_t i = 1; i <= dim_row; i++, count++) {
      if ((!is_insert_end) && insert_iter == end)
        is_insert_end = 1;
      if (is_insert_end) {
        _iter = new list_node<T>(T());
      } else {
        _iter = new list_node<T>(*insert_iter);
        insert_iter++;
      } // init nodes
      if (flag == 1) {
        // list_row_elem_iter<T> _cursor(up_left);
        auto node = _cursor.inner;
        if (!count) {
          up_left = _iter;
          start_node = _iter;
        } else {
          _iter->up = front_ptr;
          front_ptr->down = _iter;
        }
        front_ptr = _iter;
        node->left = _iter;
        _iter->right = node;

        if (i == dim_row)
          down_left = _iter;
        end_node = _iter;
        _cursor++;

      } else if (flag == 2) {
        // list_row_elem_iter<T> _cursor(cursor.begin().inner);
        auto node = _cursor.inner;
        if (!count) {
          up_right = _iter;
          start_node = _iter;
        } else {
          _iter->up = front_ptr;
          front_ptr->down = _iter;
        }
        front_ptr = _iter;
        node->right = _iter;
        _iter->left = node;
        if (i == dim_row) {
          down_right = _iter;
          end_node = _iter;
        }
        _cursor++;

      } else if (flag == 3) {
        // list_row_elem_iter<T> _cursor(cursor.begin().inner);
        auto node = _cursor.inner;
        if (count) {
          _iter->up = front_ptr;
          front_ptr->down = _iter;
        } else {
          start_node = _iter;
        }

        front_ptr = _iter;
        _iter->left = node;
        _iter->right = node->right;
        node->right->left = _iter;
        node->right = _iter;

        if (i == dim_row) {
          end_node = _iter;
        }
        _cursor++;
      }
    }
    return list_col_iter<T>(start_node, end_node);
  }
}

// Delete the row where the given `cursor` reference to and returns the
// `row_iter` above the given `cursor`. If the first row is deleted, then
// return the `row_iter` below the given `cursor`. If the deleted row is the
// only row in the list, return `row_end()`. (implement this)
//
// If the cursor is `row_end()` operator, do nothing and return `row_end()`
// operator. If the last row in list is deleted, the size of the list should
// be set to 0*0.
template <typename T>
list_row_iter<T> doubll2d<T>::delete_row(row_iter cursor) {
  // If the cursor is row_end() operator, do nothing and return row_end()
  // operator.
  int count = 0;
  if (cursor == row_end())
    return row_end(); // do nothing
  // list_node<T> *_iter = nullptr;
  list_node<T> *start_node = nullptr;
  list_node<T> *end_node = nullptr;

  int flag = 0;
  if (dim_row == 1) {
    flag = 1;
  } else if (cursor == row_begin()) {
    flag = 2;
  } else if (cursor.begin().inner == down_left) {

    flag = 3;
  } else {
    flag = 4;
  }

  auto _cursor = cursor.begin();
  for (size_t i = 1; i <= dim_col; i++, count++) {
    // std::cout << "Remove me: " << i << std::endl;

    auto node = _cursor.inner;
    if (i != dim_col)
      _cursor++;
    if (flag == 1) {

      // std::cout << "Remove me: " << i << std::endl;
      // for(auto iter: cursor)
      //   delete
      delete node;

      up_left = up_right = down_left = down_right = nullptr;
      if (i == dim_col) {
        dim_col = dim_row = 0;
        return row_end();
      }
    }

    if (flag == 2) {
      // std::cout << "Remove me: " << i << std::endl;

      if (!count) {
        // std::cout << "Remove me: " << i << std::endl;
        start_node = up_left = node->down;
      }
      // std::cout << "Remove me: " << dim_row << std::endl;
      if (i == dim_col) {
        // std::cout << "Remove me: " << i << std::endl;
        end_node = up_right = node->down;
      }
      node->down->up = nullptr;
      delete node;
    }

    if (flag == 3) {
      // std::cout << "Remove me: " << node->data << std::endl;

      if (!count) {
        start_node = down_left = node->up;
      }

      if (i == dim_col) {
        end_node = down_right = node->up;
      }
      node->up->down = nullptr;

      delete node;
      // return list_row_iter<T>(start_node, end_node);
    }

    if (flag == 4) {
      // std::cout << "Remove me: " << i << std::endl;
      if (!count) {
        start_node = node->up;
      }

      if (i == dim_col) {
        // std::cout << "Remove me: " << i << std::endl;
        end_node = node->up;
      }
      node->up->down = node->down;
      node->down->up = node->up;
      delete node;
    }
    // return list_row_iter<T>(start_node, end_node);}
    // std::cout << "Remove me: " << i << std::endl;
  }
  dim_row--;
  return list_row_iter<T>(start_node, end_node);
}

// Delete the column where the given `cursor` reference to and returns the
// `col_iter` left to the given `cursor`. If the first column is deleted,
// then return the `col_iter` right to the given `cursor`. If the deleted
// column is the only column in the list, return `col_end()`. (implement
// this)
//
// If the cursor is `col_end()` operator, do nothing and return `col_end()`
// operator. If the last column in list is deleted, the size of the list
// should be set to 0*0.
template <typename T>
list_col_iter<T> doubll2d<T>::delete_col(
    col_iter cursor) { // If the cursor is row_end() operator, do nothing
                       // and return row_end()
  // operator.
  int count = 0;
  if (cursor == col_end())
    return col_end(); // do nothing
  // list_node<T> *_iter = nullptr;
  list_node<T> *start_node = nullptr;
  list_node<T> *end_node = nullptr;

  int flag = 0;
  if (dim_col == 1) {
    flag = 1;
  } else if (cursor == col_begin()) {
    flag = 2;
  } else if (cursor.begin().inner == up_right) {
    flag = 3;
  } else {
    flag = 4;
  }
  auto _cursor = cursor.begin();
  for (size_t i = 1; i <= dim_row; i++, count++) {

    auto node = _cursor.inner;
    if (i != dim_row)
      _cursor++;
    if (flag == 1) {
      // for(auto iter: cursor)
      //   delete
      delete node;

      up_left = up_right = down_left = down_right = nullptr;

      if (i == dim_row) {
        dim_col = dim_row = 0;
        return col_end();
      }
    }

    if (flag == 2) {
      if (!count) {
        start_node = up_left = node->right;
      }

      if (i == dim_row) {
        end_node = down_left = node->right;
      }
      node->right->left = nullptr;
      delete node;
      // return list_col_iter<T>(start_node, end_node);
    }

    if (flag == 3) {
      if (!count) {
        start_node = up_right = node->left;
      }

      if (i == dim_row) {
        end_node = down_right = node->left;
      }
      node->left->right = nullptr;
      delete node;
      // return list_col_iter<T>(start_node, end_node);
    }
    if (flag == 4) {
      if (!count) {
        start_node = node->left;
      }

      if (i == dim_row) {
        end_node = node->left;
      }
      node->left->right = node->right;
      node->right->left = node->left;
      delete node;
    }
  }
  dim_col--;

  return list_col_iter<T>(start_node, end_node);
}

// Clear all the nodes in the list (implement this)
template <typename T> void doubll2d<T>::clear() {
  if (dim_col == 0 || dim_row == 0)
    return;
  while (dim_row > 0)
    delete_row(row_begin());
}

// This reduce() implementation takes a reducer function and an initial
// value for the accumulator. For each iterable item, the reducer is called,
// passing it the accumulator and the current list element.
//
// The return value is assigned to the accumulator. When it's finished
// applying the reducer to all of the values in the list, the accumulated
// value is returned.
template <typename T>
template <class R>
R doubll2d<T>::reduce(std::function<R(R, const T &)> fn, R init) {
  for (auto iter : row_iterable()) {
    for (auto iter2 : iter) {
      init = fn(init, *iter2);
    }
  }
  return init;
}
