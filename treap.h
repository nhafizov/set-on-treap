#pragma once

#include <cstddef>
#include <random>
#include <iostream>
#include <stack>

const size_t mod = 32416187567;

template<typename T>
struct Node {
    T data = NULL;
    size_t prior = 0;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;

    Node() {}

    Node(T _data, size_t _prior = ((rand() << 15) + rand()) % mod) : data(_data), prior(_prior) {}

    Node(Node *other) : data(other->data), prior(other->prior), left(other->left), right(other->right) {}

    Node &operator=(const Node<T> *&other) {
        left = other->left;
        right = other->right;
        parent = other->parent;
        data = other->data;
        prior = other->prior;
        return *this;
    }
};

template<typename T, typename Compare = std::less<T>>
class treap {
 public:
    Node<T> *last = new Node<T>(42);
    Node<T> *root = nullptr;
    Compare comp;

    treap() {}

    explicit treap(const treap &other) {
        other.preUpdateLast();
        copy(other);
        updateLast();
    }

    treap &operator=(const treap &other) {
        clear();
        other.preUpdateLast();
        copy(other);
        updateLast();
        return *this;
    }

    ~treap() {
        clear();
    }

    Node<T> *search(Node<T> *_root, const T &data) {
        if (!_root || _root->data == data)
            return _root;
        if (_root->data < data)
            return search(_root->right, data);
        return search(_root->left, data);
    }

    Node<T> *search(Node<T> *_root, const T &data) const {
        if (!_root || _root->data == data)
            return _root;
        if (_root->data < data)
            return search(_root->right, data);
        return search(_root->left, data);
    }

    void update(Node<T> *node) {
        if (node) {
            node->parent = nullptr;
            if (node->left)
                node->left->parent = node;
            if (node->right)
                node->right->parent = node;
        }
    }

    void split(Node<T> *_root, T &data, Node<T> *&left, Node<T> *&right) {
        if (!_root) {
            left = nullptr;
            right = nullptr;
        } else if (data < _root->data) {
            split(_root->left, data, left, _root->left);
            right = _root;
        } else {
            split(_root->right, data, _root->right, right);
            left = _root;
        }
        update(left);
        update(right);
    }

    void erase(Node<T> *&_root, const T &data) {
        if (_root->data == data)
            merge(_root, _root->left, _root->right);
        else
            erase(data < _root->data ? _root->left : _root->right, data);
    }

    void merge(Node<T> *&_root, Node<T> *&left, Node<T> *&right) {
        if (!left || !right) {
            _root = left ? left : right;
        } else if (left->prior > right->prior) {
            merge(left->right, left->right, right);
            _root = left;
        } else {
            merge(right->left, left, right->left);
            _root = right;
        }
        update(_root);
    }

    // useful functions implementation
    Node<T> *insert(const T &data) {
        preUpdateLast();
        Node<T> *tmp1 = nullptr;
        Node<T> *tmp2 = nullptr;
        Node<T> *elem = new Node<T>(data);
        split(root, elem->data, tmp1, tmp2);
        merge(tmp1, tmp1, elem);
        merge(root, tmp1, tmp2);
        updateLast();
        return elem;
    }

    template<typename inputIt>
    void insert(inputIt begin, inputIt end) {
        while (begin != end) {
            insert(*begin);
            ++begin;
        }
    }

    Node<T> *search(const T &data) {
        return search(root, data);
    }

    Node<T> *search(const T &data) const {
        return search(root, data);
    }

    void erase(const T &data) {
        preUpdateLast();
        erase(root, data);
        inOrderParentProblem(root, nullptr);
        updateLast();
    }

    void clear() {
        preUpdateLast();
        destroyNode(root);
        root = nullptr;
        updateLast();
    }

    void inOrder(Node<T> *_root) {
        if (_root && _root != last) {
            inOrder(_root->left);
            std::cout << "key: " << _root->data << " | priority: %d "
                      << _root->prior;
            if (_root->parent && _root->parent != last)
                std::cout << " | parent: " << _root->parent->data;
            if (_root->left && _root->left != last)
                std::cout << " | left child: " << _root->left->data;
            if (_root->right && _root->right != last)
                std::cout << " | right child: " << _root->right->data;
            std::cout << "\n";
            inOrder(_root->right);
        }
    }

    void inOrder() {
        inOrder(root);
    }

    void copy(const treap &other) {
        std::vector<Node<T> *> remaining;
        Node<T> *cur = other.root;
        while (cur) {
            insert(cur->data);
            if (cur->right) {
                remaining.push_back(cur->right);
            }
            if (cur->left) {
                cur = cur->left;
            } else if (remaining.empty()) {
                break;
            } else {
                cur = remaining.back();
                remaining.pop_back();
            }
        }
    }

    // Iterators
 public:
    class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
     public:
        Node<T> *current = nullptr;
        Node<T> *_end = nullptr;
        Node<T> *nil = nullptr;

     public:
        iterator() {}

        iterator(Node<T> *node) : current(node) {}

        iterator(Node<T> *node, Node<T> *&__end) : current(node), _end(__end) {}

        iterator &operator=(const iterator &other) {
            std::move(current);
            current = new Node<T>(other.current);
            _end = other._end;
            return *this;
        }

        bool operator==(iterator const &other) const { return current == other.current; }

        bool operator!=(iterator const &other) const { return current != other.current; }

        T &operator*() { return current != _end ? (static_cast<Node<T> *>(current))->data : nil->data; }

        T *operator->() { return current != _end ? (&(static_cast<Node<T> *>(current))->data) : nil->data; }

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

        iterator &operator++() {
            Increment();
            return *this;
        }

        iterator &operator--() {
            Decrement();
            return *this;
        }

        void Increment() {
            if (current->right != 0) {
                current = current->right;
                while (current->left != 0)
                    current = current->left;
            } else {
                Node<T> *ptr = current->parent;
                if (!ptr) return;
                while (current == ptr->right) {
                    current = ptr;
                    ptr = ptr->parent;
                }
                if (current->right != ptr)
                    current = ptr;
            }
        }

        void Decrement() {
            if (current->left != 0 && (_end && current != _end)) {
                Node<T> *ptr = current->left;
                while (ptr->right != 0)
                    ptr = ptr->right;
                current = ptr;
            } else {
                Node<T> *ptr = current->parent;
                while (current == ptr->left) {
                    current = ptr;
                    ptr = ptr->parent;
                }
                current = ptr;
            }
        }
    };

 public:
    class const_iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
     public:
        Node<T> *current = nullptr;
        Node<T> *_end = nullptr;
        Node<T> *nil = nullptr;

     public:
        const_iterator() {}

        const_iterator(Node<T> *node) : current(node) {}

        const_iterator(Node<T> *node, Node<T> *__end) : current(node), _end(__end) {}

        const_iterator &operator=(const iterator &other) {
            std::move(current);
            current = new Node<T>(other.current);
            _end = other._end;
            return *this;
        }

        bool operator==(const_iterator const &other) const { return current == other.current; }

        bool operator!=(const_iterator const &other) const { return current != other.current; }

        const T &operator*() const { return current != _end ? (current)->data : nil->data; }

        const T &operator->() const { return current != _end ? &(current)->data : nil->data; }

        const const_iterator operator++(int) {
            const_iterator result = *this;
            ++(*this);
            return result;
        }

        const const_iterator operator--(int) {
            const_iterator result = *this;
            --(*this);
            return result;
        }

        const_iterator &operator++() {
            Increment();
            return *this;
        }

        const_iterator &operator--() {
            Decrement();
            return *this;
        }

        void Increment() {
            if (current->right != 0) {
                current = current->right;
                while (current->left != 0)
                    current = current->left;
            } else {
                Node<T> *ptr = current->parent;
                if (!ptr) return;
                while (current == ptr->right) {
                    current = ptr;
                    ptr = ptr->parent;
                }
                if (current->right != ptr)
                    current = ptr;
            }
        }

        void Decrement() {
            if (current->left != 0 || (_end && current != _end)) {
                Node<T> *ptr = current->left;
                while (ptr->right != 0)
                    ptr = ptr->right;
                current = ptr;
            } else {
                Node<T> *ptr = current->parent;
                while (current == ptr->left) {
                    current = ptr;
                    ptr = ptr->parent;
                }
                current = ptr;
            }
        }
    };

    iterator begin() noexcept {
        auto cnt = root;
        while (cnt && cnt->left) {
            cnt = cnt->left;
        }
        if (root) return iterator(cnt, last);
        else return iterator(cnt, root);
    }

    iterator end() noexcept {
        auto cnt = root;
        while (cnt && cnt->right) {
            cnt = cnt->right;
        }
        if (cnt && cnt->right) cnt->right = last;
        if (root) return iterator(last, last);
        else return iterator(root, root);
    }

    const_iterator begin() const noexcept {
        auto cnt = root;
        while (cnt && cnt->left) {
            cnt = cnt->left;
        }
        if (root) return const_iterator(cnt, last);
        else return const_iterator(cnt, root);
    }

    const_iterator end() const noexcept {
        auto cnt = root;
        while (cnt && cnt->right) {
            cnt = cnt->right;
        }
        if (cnt && cnt->right) cnt->right = last;
        if (root) return const_iterator(last, last);
        else return const_iterator(cnt, root);
    }

    void preUpdateLast() {
        auto cnt = root;
        while (cnt && cnt->right && cnt->right != last) cnt = cnt->right;
        if (cnt) cnt->right = nullptr;
        last->parent = nullptr;
    }

    void updateLast() {
        auto cnt = root;
        while (cnt && cnt->right && cnt->right != last) cnt = cnt->right;
        if (cnt) cnt->right = last;
        last->parent = cnt;
    }

    void preUpdateLast() const {
        auto cnt = root;
        while (cnt && cnt->right && cnt->right != last) cnt = cnt->right;
        if (cnt) cnt->right = nullptr;
        last->parent = nullptr;
    }

    void updateLast() const {
        auto cnt = root;
        while (cnt && cnt->right && cnt->right != last) cnt = cnt->right;
        if (cnt) cnt->right = last;
        last->parent = cnt;
    }

    iterator lower_bound(const T &key) {
        Node<T> *notLessThanKey = (begin()).current;
        Node<T> *current = root;
        while (current && current != last)
            if (!comp(key, current->data))
                notLessThanKey = current, current = current->right;
            else
                current = current->left;
        if (notLessThanKey && notLessThanKey->data < key) return iterator(notLessThanKey);
        else return end();
    }

    const_iterator lower_bound(const T &key) const {
        Node<T> *LessThanKey = (begin()).current;
        Node<T> *current = root;
        while (current && current != last)
            if (!comp(key, current->data))
                LessThanKey = current, current = current->right;
            else
                current = current->left;
        if (LessThanKey && LessThanKey->data < key) return const_iterator(LessThanKey);
        else return end();
    }

    iterator upper_bound(const T &key) {
        Node<T> *greaterThanKey = (begin()).current;
        Node<T> *current = root;
        while (current && current != last)
            if (!comp(current->data, key))
                greaterThanKey = current, current = current->left;
            else
                current = current->right;
        if (greaterThanKey && greaterThanKey->data > key) return iterator(greaterThanKey);
        else return end();
    }

    const_iterator upper_bound(const T &key) const {
        Node<T> *greaterThanKey = (--end()).current;
        Node<T> *current = root;
        while (current && current != last)
            if (comp(key, current->data))
                greaterThanKey = current, current = current->left;
            else
                current = current->right;
        return const_iterator(greaterThanKey);
    }

 private:
    void destroyNode(Node<T> *node) {
        if (node) {
            if (node->left) destroyNode(node->left);
            if (node->right) destroyNode(node->right);
            delete node;
        }
    }

    void inOrderParentProblem(Node<T> *_root, Node<T> *__root) {
        if (_root && _root != last) {
            inOrderParentProblem(_root->left, _root);
            _root->parent = __root;
            inOrderParentProblem(_root->right, _root);
        }
    }
};