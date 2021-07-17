template <typename T> class list_row_elem_iter : public std::iterator<std::bidirectional_iterator_tag, T> {
public:
    explicit list_row_elem_iter(list_node<T> *inner) : inner{inner} {}

    // reference operator (implement this)
    typename list_row_elem_iter::reference operator*() {
        return *inner; // return the data TODO: or reference
    }

    // pointer operator (implement this)
    typename list_row_elem_iter::pointer operator->() {
        return inner; // return itself
    }

    // self increment operator (implement this)
    // move to the right element
    list_row_elem_iter &operator++() {
        inner = inner->right; // next element in the row
        return *this;         // return node ++
    }

    list_row_elem_iter operator++(int) { // increment
        list_node<T> *temp = *this;
        ++*this;
        return *temp;
        // TODO: check the correctness
    }

    // self decrement operator (implement this)
    // move to the left element
    //  operator-- represents the last left element in this row
    // TODO: check the mean of the `last left element`
    list_row_elem_iter &operator--() {
        // keep left until NULL
        while (inner->left != NULL)
            inner = inner->left;
        return *this;
    }

    list_row_elem_iter operator--(int) {
        list_node<T> *temp = *this;
        --*this;
        return *temp;
        //TODO:  The same as above
    }

    // comparison operator (implement this)
    // ==
    bool operator==(const list_row_elem_iter &other) {
        return this->inner == other->inner;
    }

    // !=
    bool operator!=(const list_row_elem_iter &other) {
        return this->inner != other->inner;
    }

private:
    list_node<T> *inner;

    // this allows you get the inner node inside this iter
    friend class doubll2d<T>;
};

// Iterator of the list element in some column.
template <typename T> class list_col_elem_iter : public std::iterator<std::bidirectional_iterator_tag, T> {
public:
    // Type renaming
    explicit list_col_elem_iter(list_node<T> *inner) : inner{inner} {}

    // reference operator (implement this)
    typename list_col_elem_iter::reference operator*() {
        return *inner;
    }

    // pointer operator (implement this)
    typename list_col_elem_iter::pointer operator->() {
        return inner;
    }

    // self increment operator (implement this)
    // move to the element below
    list_col_elem_iter &operator++() {
        inner = inner->down; // operator++ represents the element below
        return *this;        // return node ++
    }

    list_col_elem_iter operator++(int) {
        list_node<T> *temp = *this;
        ++*this;
        return *temp;
        // TODO: check the correctness
    }

    // self decrement operator (implement this)
    // move to the element above
    list_col_elem_iter &operator--() {
        // keep above until NULL
        while (inner->up != NULL)
            inner = inner->up;
        return *this;
    }

    list_col_elem_iter operator--(int) {
        list_node<T> *temp = *this;
        -- *this;
        return *temp;
        // TODO: check the correctness
    }

    // comparison operator (implement this)
    bool operator==(const list_col_elem_iter &other) {
        return this->inner == other->inner;
    }

    bool operator!=(const list_col_elem_iter &other){
        return this->inner != other->inner;
    }

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
    iterator begin(){
        
    }

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