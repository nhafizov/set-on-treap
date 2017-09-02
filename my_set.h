#pragma once

#include <initializer_list>
#include <memory>
#include "treap.h"
#include <set>
#include <algorithm>

// Проблема в clear()
template<typename T>
class treap;

template<typename T, class Compare = std::less<T>>
class my_set {
 private:
    treap<T> _treap;

 protected:
    size_t _size = 0;
    Compare comp;

 public:
    /* member types */
    using key_type = T;
    using value_type = T;
    using key_compare = Compare;
    using value_compare = Compare;
    typedef typename treap<T>::iterator iterator;
    typedef typename treap<T>::const_iterator const_iterator;

    /* member functions */
    explicit my_set(const Compare &comp = Compare()) {}

    template<typename InputIt>
    my_set(InputIt first, InputIt last, const Compare &comp = Compare()) : comp(comp) {
        while (first != last) {
            _treap.insert(*first);
            ++first;
            ++_size;
        }
    }

    explicit my_set(const my_set &other) : _treap(other._treap), comp(other.comp), _size(other._size) {}

    explicit my_set(my_set &&other) : comp(other.comp) {
        std::swap(_treap.root, other._treap.root);
        std::swap(_size, other._size);
        std::swap(_treap.last, other._treap.last);
    }

    my_set(std::initializer_list<value_type> init, const Compare &comp = Compare()) {
        for (auto it = init.begin(); it != init.end(); ++it) {
            _treap.insert(*it);
            ++_size;
        }
    }

    ~my_set() {}

    my_set &operator=(const my_set &other) {
        _treap = other._treap;
        _size = other._size;
        comp = other.comp;
        return *this;
    }

    my_set &operator=(my_set &&other) {
        _treap.root = other._treap.root;
        _treap.last = other._treap.last;
        other._treap.root = nullptr;
        _size = other._size;
        return *this;
    }

    my_set &operator=(std::initializer_list<value_type> ilist) {
        clear();
        for (auto it = ilist.begin(); it != ilist.end(); ++it) {
            _treap.insert(*it);
            ++_size;
        }
        return *this;
    }

    /* iterators */
    iterator begin() noexcept {
        return _treap.begin();
    }

    const_iterator begin() const noexcept {
        return _treap.begin();
    }

    const_iterator cbegin() const noexcept {
        return _treap.begin();
    }

    iterator end() noexcept {
        return _treap.end();
    }

    const_iterator end() const noexcept {
        return _treap.end();
    }

    const_iterator cend() const noexcept {
        return _treap.end();
    }

    /* capacity */
    bool empty() const noexcept {
        return _treap.begin() == _treap.end();
    }

    size_t size() const noexcept {
        return _size;
    }

    /* modifiers */
    void clear() noexcept {
        _size = 0;
        _treap.clear();
    };

    std::pair<iterator, bool> insert(const value_type &value) {
        auto cnt = _treap.search(value);
        if (cnt) {
            return std::make_pair(iterator(cnt), false);
        } else {
            ++_size;
            return std::make_pair(iterator(_treap.insert(value)), true);
        }
    }

    std::pair<iterator, bool> insert(value_type &&value) {
        auto cnt = _treap.search(value);
        if (cnt) {
            return std::make_pair(iterator(cnt), false);
        } else {
            ++_size;
            return std::make_pair(iterator(_treap.insert(value)), true);
        }
    };

    // fix
    iterator insert(const_iterator hint, const value_type &value) {
        return iterator(_treap.insert(value));
    }

    // fix
    iterator insert(const_iterator hint, value_type &&value) {
        return iterator(_treap.insert(value));
    }

    template<class InputIt>
    void insert(InputIt first, InputIt last) {
        while (first != last) {
            _treap.insert(*first);
            ++first;
        }
    }

    void insert(std::initializer_list<value_type> ilist) {
        _treap.insert(ilist.begin(), ilist.end());
    }

    iterator erase(const_iterator pos) {
        Node<T> *cnt = pos.current;
        iterator smth = iterator(cnt);
        ++smth;
        _treap.erase(pos.current->data);
        return smth;
    }

    iterator erase(const_iterator first, const_iterator last) {
        while (first != last) {
            _treap.erase(first);
            ++first;
        }
        return iterator(last.current);
    }

    //fix
    size_t erase(const key_type &key) {
        auto flag = _treap.search(key);
        if (!flag) {
            return 0;
        } else {
            _treap.erase(key);
            return 1;
        }
        _treap.erase(key);
    }

    void swap(my_set &other) {
        auto cmp = _treap.root;
        _treap.root = other._treap.root;
        other._treap.root = cmp;
    }

    // lookup
    int count(const T &key) {
        auto smth = _treap.search(key);
        return 1 ? !smth || !smth->data != nullptr : 0;
    }

    iterator find(const T &key) {
        return iterator(_treap.search(key));
    }

    const_iterator find(const T &key) const {
        return const_iterator(_treap.search(key));
    }

    std::pair<iterator, iterator> equal_range(const T &key) {
        return std::equal_range(begin(), end(), key);
    };

    std::pair<const_iterator, const_iterator> equal_range(const T &key) const {
        return std::equal_range(cbegin(), cend(), key);
    };

    iterator lower_bound(const T &key) {
        return std::lower_bound(begin(), end(), key);
    }

    const_iterator lower_bound(const T &key) const {
        return std::lower_bound(cbegin(), cend(), key);
    }

    iterator upper_bound(const T &key) {
        return std::lower_bound(begin(), end(), key);
    }

    const_iterator upper_bound(const T &key) const {
        return std::lower_bound(cbegin(), cend(), key);
    }

    // observers
    key_compare key_comp() const {
        return comp;
    }

    value_compare value_comp() const {
        return comp;
    }
};

// non-member functions
template<class Key, class Compare>
bool operator==(const my_set<Key, Compare> &lhs,
                const my_set<Key, Compare> &rhs) {
};

template<class Key, class Compare, class Alloc>
bool operator!=(const my_set<Key, Compare> &lhs,
                const my_set<Key, Compare> &rhs) {
    return lhs._treap.root != rhs._treap.root;
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

template<typename T>
std::ostream &operator<<(std::ostream &out, const my_set<T> &other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
        out << *it << " ";
    }
    return out;
}
