#include <initializer_list>
#include <memory>
#include "treap.h"

#pragma once

template<typename T, class Compare = std::less<T>>
class my_set {
 private:
    treap<T> treap;
    size_t _size = 0;

    // Iterators
 public:
    class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
     public:
        Node *current;

     public:
        iterator(Node *node) : current(node) {}

        bool operator==(iterator const &other) const { return current == other.current; }

        bool operator!=(iterator const &other) const { return !(*this == other); }

        iterator &operator++() {
            current = current->right;
            return *this;
        }

        iterator &operator--() {
            current = current->left;
            return *this;
        }

        iterator operator++(int) {
            iterator result(*this);
            ++(*this);
            return result;
        }

        iterator operator--(int) {
            iterator result(*this);
            --(*this);
            return result;
        }

        T &operator*() const { return static_cast<Node *>(current)->data; }

        T *operator->() const { return &(static_cast<Node *>(current)->data); }
    };

 public:
    // member types
    using key_type = T;
    using value_type = T;
    using iterator = std::iterator<std::bidirectional_iterator_tag, T>;
    using const_iterator = std::iterator<std::bidirectional_iterator_tag, const T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // member functions
    my_set() {}

    explicit my_set(const my_set &other) : treap(other.treap) {}

    explicit my_set(my_set &&other) {
        treap.root = other.treap.root;
        _size = other._size;
        other._size = 0;
        other.treap.root = nullptr;
    }

    ~my_set() {
        clear();
    }

    my_set &operator=(const my_set &other) {
        treap = other.treap;
        return *this;
    }

    my_set &operator=(my_set &&other) {
        treap.root = other.treap.root;
        other.treap.root = nullptr;
        return *this;
    }

    my_set &operator=(std::initializer_list<value_type> ilist);

    // iterators
    iterator begin() noexcept {
        auto cnt = treap.root;
        while (cnt && cnt->left) {
            cnt = cnt->left;
        }
        return iterator(cnt);
    }

    const_iterator begin() const noexcept;

    const_iterator cbegin() const noexcept;

    iterator end() noexcept {
        auto cnt = treap.root;
        while (cnt && cnt->right) {
            cnt = cnt->right;
        }
        return cnt;
    }

    const_iterator end() const noexcept;

    const_iterator cend() const noexcept;

    reverse_iterator rbegin() noexcept;

    const_reverse_iterator rbegin() const noexcept;

    const_reverse_iterator crbegin() const noexcept;

    reverse_iterator rend() noexcept;

    const_reverse_iterator rend() const noexcept;

    const_reverse_iterator crend() const;

    // capacity
    bool empty() const noexcept {
        return treap.root;
    }

    size_t size() const noexcept {
        return _size;
    }

    // modifiers
    void clear() noexcept {
        _size = 0;
        treap.clear();
    };

    std::pair<iterator, bool> insert(const value_type &value) {
        ++_size;
        treap.insert(value);
    }

    std::pair<iterator, bool> insert(value_type &&value);

    iterator insert(const_iterator hint, const value_type &value);

    iterator insert(const_iterator hint, value_type &&value);

    template<class InputIt>
    void insert(InputIt first, InputIt last) {
        while (first++ != last)
            treap.insert(*first);
    }

    void insert(std::initializer_list<value_type> ilist);

    template<class... Args>
    std::pair<iterator, bool> emplace(Args &&... args);

    template<class... Args>
    iterator emplace_hint(const_iterator hint, Args &&... args);

    iterator erase(const_iterator pos) {
        treap.erase(pos);
    }

    iterator erase(const_iterator first, const_iterator last);

    size_t erase(const key_type &key);

    void swap(my_set &other) {
        std::swap(treap.root, other.treap.root);
    }

    // lookup
    size_t count(const T &key) const {
        return 1 ? treap.search(key) != nullptr ? 0;
    }

    iterator find(const T &key) {}

    const_iterator find(const T &key) const;

    std::pair<iterator, iterator> equal_range(const T &key);

    std::pair<const_iterator, const_iterator> equal_range(const T &key) const;

    iterator lower_bound(const T &key);

    const_iterator lower_bound(const T &key) const;

    iterator upper_bound(const T &key);

    const_iterator upper_bound(const T &key) const;

    // observers
    /*
    key_compare key_comp() const;

    std::set::value_compare value_comp() const;
    */
};

// non-member functions
template<class Key, class Compare>
bool operator==(const my_set<Key, Compare> &lhs,
                const my_set<Key, Compare> &rhs) {
    return lhs.treap.root == rhs.treap.root;
};

template<class Key, class Compare, class Alloc>
bool operator!=(const my_set<Key, Compare> &lhs,
                const my_set<Key, Compare> &rhs) {
    return lhs.treap.root != rhs.treap.root;
};

template<class Key, class Compare>
bool operator<(const my_set<Key, Compare> &lhs,
               const my_set<Key, Compare> &rhs) {

};

template<class Key, class Compare>
bool operator<=(const my_set<Key, Compare> &lhs,
                const my_set<Key, Compare> &rhs);

template<class Key, class Compare, class Alloc>
bool operator>(const my_set<Key, Compare> &lhs,
               const my_set<Key, Compare> &rhs);

template<class Key, class Compare, class Alloc>
bool operator>=(const my_set<Key, Compare> &lhs,
                const my_set<Key, Compare> &rhs);

template<class Key, class Compare, class Alloc>
void swap(my_set<Key, Compare> &lhs,
          my_set<Key, Compare> &rhs) {
    lhs.swap(rhs);
};
