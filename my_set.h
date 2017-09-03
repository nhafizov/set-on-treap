#pragma once

#include <initializer_list>
#include <memory>
#include "treap.h"
#include <set>
#include <algorithm>

template<typename T, typename Compare = std::less<T>>
class my_set {
 private:
    treap<T, Compare> _treap;

 protected:
    size_t _size = 0;
    Compare comp;

 public:
    /* member types */
    using key_type = T;
    using value_type = T;
    using key_compare = Compare;
    using value_compare = Compare;
    typedef typename treap<T, Compare>::iterator iterator;
    typedef typename treap<T, Compare>::const_iterator const_iterator;

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
        clear();
        std::swap(_treap.root, other._treap.root);
        delete _treap.last;
        std::swap(_treap.last, other._treap.last);
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
        for (auto it = ilist.begin(); it != ilist.end(); ++it) _treap.insert(*it);
    }

    template<class... Args>
    std::pair<iterator, bool> emplace(Args &&... args) {
        auto tmp = (new T(std::forward<Args>(args)...));
        auto cnt = _treap.search(*tmp);
        if (cnt) {
            return std::make_pair(iterator(cnt), false);
        } else {
            ++_size;
            return std::make_pair(iterator(_treap.insert(std::move(*tmp))), true);
        }
    };

    template<class... Args>
    iterator emplace_hint(const_iterator hint, Args &&... args) {
        return iterator(_treap.insert(*(new T(std::forward<Args>(args)...))));
    }

    iterator erase(const_iterator pos) {
        if (pos != cend()) {
            Node<T> *cnt = pos.current;
            iterator smth = iterator(cnt);
            ++smth;
            _treap.erase(pos.current->data);
            return smth;
        } else {
            return end();
        }
    }

    iterator erase(const_iterator first, const_iterator last) {
        if (first == cbegin() && last == cend()) {
            clear();
            return iterator(last.current, _treap.last);
        } else {
            while (first != last) erase(first++);
            return iterator(first.current);
        }
    }

    size_t erase(const key_type &key) {
        auto flag = _treap.search(key);
        if (flag) {
            return 0;
        } else {
            _treap.erase(key);
            return 1;
        }
    }

    void swap(my_set &other) {
        std::swap(_treap.root, other._treap.root);
        std::swap(_treap.last, other._treap.last);
    }

    /* lookup */
    size_t count(const T &key) const {
        auto flag = _treap.search(key);
        if (flag) {
            return 0;
        } else {
            return 1;
        }
    }

    iterator find(const T &key) {
        return iterator(_treap.search(key));
    }

    const_iterator find(const T &key) const {
        return const_iterator(_treap.search(key));
    }

    std::pair<iterator, iterator> equal_range(const T &key) {
        return std::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
    };

    std::pair<const_iterator, const_iterator> equal_range(const T &key) const {
        return std::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
    };

    iterator lower_bound(const T &key) {
        return _treap.lower_bound(key);
    }

    const_iterator lower_bound(const T &key) const {
        return _treap.lower_bound(key);
    }

    iterator upper_bound(const T &key) {
        return _treap.upper_bound(key);
    }

    const_iterator upper_bound(const T &key) const {
        return _treap.upper_bound(key);
    }

    // observers
    key_compare key_comp() const {
        return comp;
    }

    value_compare value_comp() const {
        return comp;
    }
};

/* non-member functions */
template<class Key, class Compare>
bool operator==(const my_set<Key, Compare> &lhs,
                const my_set<Key, Compare> &rhs) {
    return lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin());
};

template<class Key, class Compare, class Alloc>
bool operator!=(const my_set<Key, Compare> &lhs,
                const my_set<Key, Compare> &rhs) {
    return !(lhs == rhs);
};

template<class Key, class Compare>
bool operator<(const my_set<Key, Compare> &lhs,
               const my_set<Key, Compare> &rhs) {
    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
};

template<class Key, class Compare, class Alloc>
bool operator>(const my_set<Key, Compare> &lhs,
               const my_set<Key, Compare> &rhs) {
    return rhs < lhs;
};

template<class Key, class Compare>
bool operator<=(const my_set<Key, Compare> &lhs,
                const my_set<Key, Compare> &rhs) {
    return !(rhs < lhs);
};

template<class Key, class Compare, class Alloc>
bool operator>=(const my_set<Key, Compare> &lhs,
                const my_set<Key, Compare> &rhs) {
    return !(lhs < rhs);
};

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
