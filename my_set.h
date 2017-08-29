#include <initializer_list>
#include <memory>
#include "treap.h"
#include <set>

#pragma once

template<typename T, class Compare = std::less<T>>
class my_set {
 private:
    treap<T> treap;
    size_t _size = 0;

 public:
    // member types
    using key_type = T;
    using value_type = T;
    using iterator = std::iterator<std::bidirectional_iterator_tag, T>;
    using const_iterator = std::iterator<std::bidirectional_iterator_tag, const T>;

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

    my_set &operator=(std::initializer_list<value_type> ilist) {
        clear();
        insert(ilist.begin(), ilist.end());
        return *this;
    }

    // iterators
    iterator begin() noexcept {
        return treap.begin();
    }

    const_iterator begin() const noexcept;

    const_iterator cbegin() const noexcept;

    iterator end() noexcept {
        return treap.end();
    }

    const_iterator end() const noexcept;

    const_iterator cend() const noexcept;

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
        return treap.insert(value);
    }

    std::pair<iterator, bool> insert(value_type &&value) {
        ++_size;
        return treap.insert(std::move(value));
    };

    iterator insert(const_iterator hint, const value_type &value) {}

    iterator insert(const_iterator hint, value_type &&value);

    template<class InputIt>
    void insert(InputIt first, InputIt last) {
        while (first++ != last)
            treap.insert(*first);
    }

    void insert(std::initializer_list<value_type> ilist) {
        treap.insert(ilist.begin(), ilist.end());
    }

    iterator erase(const_iterator pos) {
        treap.erase(pos);
    }

    iterator erase(const_iterator first, const_iterator last) {
        while (first++ != last) {
            treap.erase(first);
        }
    }

    size_t erase(const key_type &key);

    void swap(my_set &other) {
        std::swap(treap.root, other.treap.root);
    }

    // lookup
    size_t count(const T &key) const {
        return 1 ? treap.search(key) != nullptr : 0;
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
