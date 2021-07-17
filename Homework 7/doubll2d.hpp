//  ShanghaiTech University
//
//  Computer Architecture I - 2021 Spring
//
//  HW 7 C++ 2D Doubly Linked List

#ifndef _HW7_DOUBLL2D_HPP_
#define _HW7_DOUBLL2D_HPP_

#include <cstddef>
#include <functional>
#include <iterator>

template <typename T> class doubll2d;

// Detailed implementation of doubll2d.
// Namespaces are used to prevent users from directly using them.
namespace __detail {
// Helper class for creating iterable from two iterators.
// You do not need to implement or use this.
template <typename T> class iterable {
private:
    T begin_;
    T end_;

public:
    iterable(T begin, T end) : begin_{begin}, end_{end} {}

    T begin() const {
        return begin_;
    }

    T end() const {
        return end_;
    }
};

template <typename T> iterable<T> make_iterable(T begin, T end) {
    return iterable<T>{begin, end};
}

// Helper class to create reverse iterator from normal iterator.
// You do not need to implement or use this.
template <class I>
class reverse_iter : public std::iterator<typename std::iterator_traits<I>::iterator_category, typename std::iterator_traits<I>::value_type,
                                          typename std::iterator_traits<I>::difference_type, typename std::iterator_traits<I>::pointer,
                                          typename std::iterator_traits<I>::reference> {
public:
    explicit reverse_iter(I iter) : inner{iter} {}

    // reference operator (implemented)
    typename reverse_iter::reference operator*() {
        return *inner;
    }

    // pointer operator (implemented)
    typename reverse_iter::pointer operator->() {
        return &*inner;
    }

    // self increment operator (implemented)
    reverse_iter &operator++() {
        --inner;
        return *this;
    }

    reverse_iter operator++(int) {
        return reverse_iter{inner--};
    }

    // self decrement operator (implemented)
    reverse_iter &operator--() {
        ++inner;
        return *this;
    }

    reverse_iter operator--(int) {
        return reverse_iter{inner++};
    }

    // comparison operator (implemented)
    bool operator==(const reverse_iter &other) {
        return inner == other.inner;
    }

    bool operator!=(const reverse_iter &other) {
        return inner != other.inner;
    }

private:
    I inner;
};

// List node, you do not need to implement this
template <typename T> class list_node {
public:
    // Initialize the node with a value (implemented)
    explicit list_node(const T &value) : left{nullptr}, right{nullptr}, up{nullptr}, down{nullptr}, data{value} {}

    // Copy constructor (compiler generated)
    list_node(const list_node &other) = default;

    // Destructor (compiler generated)
    ~list_node() = default;

    // Copy assignment operator (compiler generated)
    list_node &operator=(const list_node &rhs) = default;

    // adjacent nodes
    list_node *left;
    list_node *right;
    list_node *up;
    list_node *down;

    // Data of the node
    T data;
};

// Iterator of the list element in some row.
template <typename T> class list_row_elem_iter : public std::iterator<std::bidirectional_iterator_tag, T> {
public:
    explicit list_row_elem_iter(list_node<T> *inner) : inner{inner} {}

    // reference operator (implement this)
    typename list_row_elem_iter::reference operator*();

    // pointer operator (implement this)
    typename list_row_elem_iter::pointer operator->();

    // self increment operator (implement this)
    // move to the right element
    list_row_elem_iter &operator++();

    list_row_elem_iter operator++(int);

    // self decrement operator (implement this)
    // move to the left element
    list_row_elem_iter &operator--();

    list_row_elem_iter operator--(int);

    // comparison operator (implement this)
    bool operator==(const list_row_elem_iter &other);

    bool operator!=(const list_row_elem_iter &other);

private:
    list_node<T> *inner;

    // this allows you get the inner node inside this iter
    friend class doubll2d<T>;
};

// Iterator of the row in the list
template <typename T> class list_row_iter : public std::iterator<std::bidirectional_iterator_tag, list_row_iter<T>> {
public:
    // Type renaming
    using iterator = list_row_elem_iter<T>;
    using reverse_iterator = __detail::reverse_iter<iterator>;

    list_row_iter(list_node<T> *left, list_node<T> *right) : left{left}, right{right} {}

    // the leftmost iterator of this row (implement this)
    iterator begin();

    // the iterator next to the rightmost element in this row (implement this)
    iterator end();

    // the `reverse_iterator` of the rightmost element in this row (implement this)
    reverse_iterator rbegin();

    // the `reverse_iterator` before the leftmost element in this row (implement this)
    reverse_iterator rend();

    iterable<reverse_iterator> riterable() {
        return make_iterable(rbegin(), rend());
    }

    // reference operator (implement this)
    typename list_row_iter::reference operator*();

    // pointer operator (implement this)
    typename list_row_iter::pointer operator->();

    // self increment operator (implement this)
    // move to the row below
    list_row_iter &operator++();

    list_row_iter operator++(int);

    // self decrement operator (implement this)
    // move to the row above
    list_row_iter &operator--();

    list_row_iter operator--(int);

    // comparison operator (implement this)
    bool operator==(const list_row_iter &other);

    bool operator!=(const list_row_iter &other);

private:
    list_node<T> *left;  // leftmost element in the row
    list_node<T> *right; // rightmost element in the row
};

// Iterator of the list element in some column.
template <typename T> class list_col_elem_iter : public std::iterator<std::bidirectional_iterator_tag, T> {
public:
    // Type renaming
    explicit list_col_elem_iter(list_node<T> *inner) : inner{inner} {}

    // reference operator (implement this)
    typename list_col_elem_iter::reference operator*();

    // pointer operator (implement this)
    typename list_col_elem_iter::pointer operator->();

    // self increment operator (implement this)
    // move to the element below
    list_col_elem_iter &operator++();

    list_col_elem_iter operator++(int);

    // self decrement operator (implement this)
    // move to the element above
    list_col_elem_iter &operator--();

    list_col_elem_iter operator--(int);

    // comparison operator (implement this)
    bool operator==(const list_col_elem_iter &other);

    bool operator!=(const list_col_elem_iter &other);

private:
    list_node<T> *inner;

    // this allows you get the inner node inside this iter
    friend class doubll2d<T>;
};

// Iterator of the column in the list
template <typename T> class list_col_iter : public std::iterator<std::bidirectional_iterator_tag, list_col_iter<T>> {
public:
    // Type renaming
    using iterator = list_col_elem_iter<T>;
    using reverse_iterator = __detail::reverse_iter<iterator>;

    list_col_iter(list_node<T> *up, list_node<T> *down) : up{up}, down{down} {}

    // the top iterator of this column (implement this)
    iterator begin();

    // the iterator below the bottom element in this column (implement this)
    iterator end();

    // the `reverse_iterator` of the bottom element in this column (implement this)
    reverse_iterator rbegin();

    // the `reverse_iterator` above the top element in this column (implement this)
    reverse_iterator rend();

    iterable<reverse_iterator> riterable() {
        return make_iterable(rbegin(), rend());
    }

    // reference operator (implement this)
    typename list_col_iter::reference operator*();

    // pointer operator (implement this)
    typename list_col_iter::pointer operator->();

    // self increment operator (implement this)
    // move to the next column
    list_col_iter &operator++();

    list_col_iter operator++(int);

    // self decrement operator (implement this)
    // move to the previous column
    list_col_iter &operator--();

    list_col_iter operator--(int);

    // comparison operator (implement this)
    bool operator==(const list_col_iter &other);

    bool operator!=(const list_col_iter &other);

private:
    list_node<T> *up;   // top element in the column
    list_node<T> *down; // bottom element in the column
};
} // namespace __detail

// 2D Doubly linked list class
template <typename T> class doubll2d {
public:
    // Type renaming
    using size_type = size_t;
    using row_iter = __detail::list_row_iter<T>;
    using col_iter = __detail::list_col_iter<T>;
    using row_riter = __detail::reverse_iter<row_iter>;
    using col_riter = __detail::reverse_iter<col_iter>;

    // Default constructor
    doubll2d() : up_left{nullptr}, up_right{nullptr}, down_left{nullptr}, down_right{nullptr}, dim_row{0}, dim_col{0} {}

    // Copy and move constructor are deleted
    doubll2d(const doubll2d &other) = delete;

    doubll2d(doubll2d &&other) = delete;

    // Destructor
    ~doubll2d() {
        clear();
    }

    // Copy and move assignment operator are deleted
    doubll2d &operator=(const doubll2d &other) = delete;

    doubll2d &operator=(doubll2d &&other) = delete;

    // The number of rows in the list
    size_type get_dim_row() const {
        return dim_row;
    }

    // The number of columns in the list
    size_type get_dim_col() const {
        return dim_col;
    }

    // Iterator to the first (top) row (implement this)
    row_iter row_begin();

    // Iterator below the last (bottom) row (implement this)
    row_iter row_end();

    __detail::iterable<row_iter> row_iterable() {
        return __detail::make_iterable(row_begin(), row_end());
    }

    // `reverse_iterator` to the last (bottom) row (implement this)
    row_riter row_rbegin();

    // `reverse_iterator` above the first (top) row (implement this)
    row_riter row_rend();

    __detail::iterable<row_riter> row_riterable() {
        return __detail::make_iterable(row_rbegin(), row_rend());
    }

    // Iterator to the first (leftmost) column (implement this)
    col_iter col_begin();

    // Iterator after the last (rightmost) column (implement this)
    col_iter col_end();

    __detail::iterable<col_iter> col_iterable() {
        return __detail::make_iterable(col_begin(), col_end());
    }

    // `reverse_iterator` to the last (rightmost) column (implement this)
    col_riter col_rbegin();

    // `reverse_iterator` before the first (leftmost) column (implement this)
    col_riter col_rend();

    __detail::iterable<col_riter> col_riterable() {
        return __detail::make_iterable(col_rbegin(), col_rend());
    }

    // Insert a new row in the list below the row referenced by `cursor`.
    // The data stores from `input_iter` `begin` to `end`. (implement this)
    //
    // Remember, our 2D doubly linked list should always be a rectangular. When the length
    // of data is shorter than it should be, you should fill the rest part by default value of T.
    // Additionally, it is okay that the length of data is longer than needed, in this case
    // you should make use of the `dim_col` items from `begin` and ignore the extra elements.
    //
    // If the list is empty, you should insert the whole data from `begin` to `end`.
    // If the list is empty and `begin` equals to `end`, do nothing and return `row_end()`.
    //
    // If the cursor equals to `row_end()` operator, insert the data above the origin first row.
    //
    // Return the iter of the row inserted.
    template <typename input_iter> row_iter insert_row(row_iter cursor, input_iter begin, input_iter end);

    // Insert a new column in the list after the column referenced by `cursor`.
    // The data stores from `input_iter` `begin` to `end`. (implement this)
    //
    // Remember, our 2D doubly linked list should always be a rectangular. When the length
    // of data is shorter than it should be, you should fill the rest part by default value of T.
    // Additionally, it is okay that the length of data is longer than needed, in this case
    // you should make use of the first `dim_row` items from `begin` and ignore the extra elements.
    //
    // If the list is empty, you should insert the whole data from `begin` to `end`.
    // If the list is empty and `begin` equals to `end`, do nothing and return `col_end()`.
    //
    // If the cursor is `col_end()` operator, insert the data before the origin first column.
    //
    // Return the iter of the column inserted.
    template <typename input_iter> col_iter insert_col(col_iter cursor, input_iter begin, input_iter end);

    // Delete the row where the given `cursor` reference to and returns the `row_iter` above
    // the given `cursor`. If the first row is deleted, then return the `row_iter`
    // below the given `cursor`. If the deleted row is the only row in the list,
    // return `row_end()`. (implement this)
    //
    // If the cursor is `row_end()` operator, do nothing and return `row_end()` operator.
    // If the last row in list is deleted, the size of the list should be set to 0*0.
    row_iter delete_row(row_iter cursor);

    // Delete the column where the given `cursor` reference to and returns the `col_iter` left to
    // the given `cursor`. If the first column is deleted, then return the `col_iter`
    // right to the given `cursor`. If the deleted column is the only column in the list,
    // return `col_end()`. (implement this)
    //
    // If the cursor is `col_end()` operator, do nothing and return `col_end()` operator.
    // If the last column in list is deleted, the size of the list should be set to 0*0.
    col_iter delete_col(col_iter cursor);

    // Clear all the nodes in the list (implement this)
    void clear();

    // This reduce() implementation takes a reducer function and an initial value
    // for the accumulator. For each iterable item, the reducer is called, passing
    // it the accumulator and the current list element.
    //
    // The return value is assigned to the accumulator. When it's finished applying the
    // reducer to all of the values in the list, the accumulated value is returned.
    template <class R> R reduce(std::function<R(R, const T &)> fn, R init);

private:
    __detail::list_node<T> *up_left;    // top-left element
    __detail::list_node<T> *up_right;   // top-right element
    __detail::list_node<T> *down_left;  // bottom-left element
    __detail::list_node<T> *down_right; // bottom-right element

    size_t dim_row;
    size_t dim_col;
};

#include "doubll2d-impl.hpp"

#endif // _HW7_DOUBLL2D_HPP_