#include "doubll2d.hpp"
#include <assert.h>
#include <iostream>
#include <vector>
using namespace std;
// using namespace __detail;

void test_elem_row_iter() {
  /*
      class list_row_elem_iter 通过赋值一个迭代器构造，迭代器的值类型为链表类型
      typename list_row_elem_iter::reference operator*();
      typename list_row_elem_iter::pointer operator->();
      list_row_elem_iter &operator++();
      list_row_elem_iter operator++(int);
      list_row_elem_iter &operator--();
      list_row_elem_iter operator--(int);
      bool operator==(const list_row_elem_iter &other);
      bool operator!=(const list_row_elem_iter &other);
  */
  list_node<int> *a = nullptr, *b = nullptr, *c = nullptr, *d = nullptr;
  a = new list_node<int>(1);
  b = new list_node<int>(3);
  c = new list_node<int>(2);
  a->right = b, b->right = c;
  c->left = b, b->left = a;
  auto i = list_row_elem_iter<int>(a);
  auto j = list_row_elem_iter<int>(b);
  auto k = list_row_elem_iter<int>(c);
  assert(++i == j);
  k--;
  assert(j == k);
  assert(--i != k++);
  assert(*i == 1);
  delete a;
  delete b;
  delete c;
  delete d;
  cout << "pass elem_row_iter test!\n";
}

void test_elem_col_iter() {
  list_node<int> *a = nullptr, *b = nullptr, *c = nullptr, *d = nullptr;
  a = new list_node<int>(1);
  b = new list_node<int>(3);
  c = new list_node<int>(2);
  a->down = b, b->down = c;
  c->up = b, b->up = a;
  auto i = list_col_elem_iter<int>(a);
  auto j = list_col_elem_iter<int>(b);
  auto k = list_col_elem_iter<int>(c);
  assert(++i == j);
  k--;
  assert(j == k);
  assert(--i != k++);
  assert(*i == 1);
  delete a;
  delete b;
  delete c;
  delete d;
  cout << "pass elem_col_iter test!\n";
}

void test_row_iter() {
  /*
      class list_row_iter 通过赋值某行头尾节点构造，迭代器的值类型与类类型相同
          using iterator = list_row_elem_iter<T>;
          using reverse_iterator = __detail::reverse_iter<iterator>;
      iterator begin();
      iterator end();
      reverse_iterator rbegin();
      reverse_iterator rend();
          riterable() 返回行迭代器的反向迭代器
      typename list_row_iter::reference operator*();
      typename list_row_iter::pointer operator->();
      list_row_iter &operator++();
      list_row_iter operator++(int);
      list_row_iter &operator--();
      list_row_iter operator--(int);
      bool operator==(const list_row_iter &other);
      bool operator!=(const list_row_iter &other);
  */
  list_node<int> *a[3][3];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      a[i][j] = new list_node<int>(i * 3 + j + 1);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (j != 2)
        a[i][j]->right = a[i][j + 1];
      if (j != 0)
        a[i][j]->left = a[i][j - 1];
      if (i != 2)
        a[i][j]->down = a[i + 1][j];
      if (i != 0)
        a[i][j]->up = a[i - 1][j];
    }
  }
  auto x = list_row_iter<int>(a[0][0], a[0][2]);
  auto y = list_row_iter<int>(a[1][0], a[1][2]);
  auto z = list_row_iter<int>(a[2][0], a[2][2]);
  int j = 0;
  for (auto i = x.begin(); i != x.end(); i++)
    assert(++j == *i);
  for (auto i = x.rbegin(); i != x.rend(); i++)
    assert(j-- == *i);
  assert(++x == y);
  z--;
  assert(y == z);
  assert(x-- != ++z);
  assert(*++x == list_row_iter<int>(a[1][0], a[1][2]));
  assert(x->begin() == list_row_elem_iter<int>(a[1][0]));
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      delete a[i][j];
  cout << "pass row_iter test!\n";
}

void test_col_iter() {
  list_node<int> *a[3][3];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      a[i][j] = new list_node<int>(i + j * 3 + 1);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (j != 2)
        a[i][j]->right = a[i][j + 1];
      if (j != 0)
        a[i][j]->left = a[i][j - 1];
      if (i != 2)
        a[i][j]->down = a[i + 1][j];
      if (i != 0)
        a[i][j]->up = a[i - 1][j];
    }
  }
  auto x = list_col_iter<int>(a[0][0], a[2][0]);
  auto y = list_col_iter<int>(a[0][1], a[2][1]);
  auto z = list_col_iter<int>(a[0][2], a[2][2]);
  int j = 0;
  for (auto i = x.begin(); i != x.end(); i++)
    assert(++j == *i);
  for (auto i = x.rbegin(); i != x.rend(); i++)
    assert(j-- == *i);
  assert(++x == y);
  z--;
  assert(y == z);
  assert(x-- != ++z);
  assert(*++x == list_col_iter<int>(a[0][1], a[2][1]));
  assert(x->begin() == list_col_elem_iter<int>(a[0][1]));
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      delete a[i][j];
  cout << "pass col_iter test!\n";
}

void test_list_row() {
  vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto st = v.begin();
  doubll2d<int> l;
  auto x1 = l.insert_row(list_row_iter<int>(nullptr, nullptr), st, st + 2);

  // auto x2 = l.insert_row(list_row_iter<int>(nullptr, nullptr), st, st);

  // assert(x2 == l.row_end());
  auto x3 = l.insert_row(x1, st + 2, st + 5);

  auto x4 = l.insert_row(x1, st + 5, st + 7);

  auto x5 = l.insert_row(l.row_end(), st + 6, st + 9);
  // cout << l.get_dim_row() << endl;
  // cout << l.get_dim_col() << endl;
  assert(l.get_dim_row() == 4 && l.get_dim_col() == 2);

  int check1[10] = {7, 8, 1, 2, 6, 7, 3, 4}, k = 0;
  for (auto i = l.row_begin(); i != l.row_end(); ++i)
    for (auto &j : i)
      assert(j == check1[k++]);
  assert(k == 8);
  cout << "pass list_row_insert test!" << endl;
  /*
      final list:
      line1(x5):7 8
      line2(x1):1 2
      line3(x4):6 7
      line4(x3):3 4
  */
  function<double(double, int)> f = [](double x, const int &y) -> double {
    x += (double)y + 0.01;
    return x;
  };
  // double res = l.reduce<double>(f, 0.01);
  // assert(abs(res - 31.09) <= 1e-5);
  // cout <<"pass list_reduce & list_iter test!\n";

  auto y1 = l.delete_row(x5);

  assert(y1 == x1);

  auto y2 = l.delete_row(x4);

  assert(y2 == x1);
  auto y3 = l.delete_row(x3);
  assert(y3 == x1);
  assert(l.get_dim_row() == 1 && l.get_dim_col() == 2);
  auto y4 = l.delete_row(y2);
  assert(l.get_dim_row() == 0 && l.get_dim_col() == 0);
  assert(y4 == l.row_end());
  cout << "pass list_row_delete test!" << endl;
  l.clear();
}

void test_list_col() {
  vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto st = v.begin();
  doubll2d<int> l;
  auto x1 = l.insert_col(list_col_iter<int>(nullptr, nullptr), st, st + 2);

  auto x3 = l.insert_col(x1, st + 2, st + 5);

  auto x4 = l.insert_col(x1, st + 5, st + 7);
  auto x5 = l.insert_col(l.col_end(), st + 6, st + 9);

  assert(l.get_dim_row() == 2 && l.get_dim_col() == 4);
  /*
  //     final list:
  //     7 1 6 3
  //     8 2 7 4
  // */
  int check1[10] = {7, 8, 1, 2, 6, 7, 3, 4}, k = 0;
  for (auto i = l.col_begin(); i != l.col_end(); ++i)
    for (auto &j : i) { // s std::cout<<j<<std::endl;
      assert(j == check1[k++]);
    }
  assert(k == 8);
  cout << "pass list_col_insert test!" << endl;

  auto y1 = l.delete_col(x5);
  cout << "Print list:" << endl;
  for (auto &i : l.row_iterable()) {
    for (auto &j : i) {
      if (j) {
        cout << j << " ";
      }
    }
    cout << endl;
  }
  assert(y1 == x1);
  auto y2 = l.delete_col(x4);
  assert(y2 == x1);
  auto y3 = l.delete_col(x3);
  assert(l.get_dim_row() == 2 && l.get_dim_col() == 1);
  assert(y3 == x1);
  auto y4 = l.delete_col(x1);
  assert(l.get_dim_row() == 0 && l.get_dim_col() == 0);
  assert(y4 == l.col_end());
  cout << "pass list_col_delete test!" << endl;
  l.clear();
}

int main() {
  test_elem_row_iter();
  test_elem_col_iter();
  test_row_iter();
  test_col_iter();
  test_list_row();
  test_list_col();
  return 0;
}