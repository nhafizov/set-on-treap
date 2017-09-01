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
};

template<typename T>
class treap {
 public:
    Node<T> *last = new Node<T>(42);
    Node<T> *root = nullptr;

    treap() {}

    explicit treap(const treap &other) {
        copy(other);
        inOrderParentProblem(root, nullptr);
    }

    treap &operator=(const treap &other) {
        clear();
        copy(other);
        inOrderParentProblem(root, nullptr);
        return *this;
    }

    ~treap() {
        clear();
    }

    Node<T> *search(Node<T> *_root, const T &data) {
        if (!_root || root->data == data)
            return _root;
        if (_root->data < data)
            return search(_root->right, data);
        return search(_root->left, data);
    }

    Node<T> *search(Node<T> *_root, const T &data) const {
        if (!_root || root->data == data)
            return _root;
        if (_root->data < data)
            return search(_root->right, data);
        return search(_root->left, data);
    }

    Node<T> *insert(Node<T> *&_root, Node<T> *elem) {
        if (!_root) {
            _root = elem;
            return _root;
        } else if (elem->prior > _root->prior) {
            split(_root, elem->data, elem->left, elem->right);
            _root = elem;
            return _root;
        } else {
            insert(elem->data < _root->data ? _root->left : _root->right, elem);
        }
    }

    void split(Node<T> *_root, T &data, Node<T> *&left, Node<T> *&right) {
        if (!_root) {
            left = nullptr;
            right = nullptr;
        } else if (data < _root->data) {
            split(_root->left, data, left, _root->left, _root);
            right = _root;
        } else {
            split(_root->right, data, _root->right, right, _root);
            left = _root;
        }
    }

    void split(Node<T> *_root, T &data, Node<T> *&left, Node<T> *&right, Node<T> *__root) {
        if (!_root) {
            left = nullptr;
            right = nullptr;
        } else if (data < _root->data) {
            if (left && left->parent)
                left->parent = __root;
            split(_root->left, data, left, _root->left, __root);
            right = _root;
        } else {
            if (right && right->parent)
                right->parent = __root;
            split(_root->right, data, _root->right, right, __root);
            left = _root;
        }
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
    }

    // useful functions implementation
    Node<T> *insert(const T &data) {
        Node<T> *_elem = new Node<T>(data);
        preUpdateLast();
        auto cnt = insert(root, _elem);
        inOrderParentProblem(root, nullptr);
        updateLast();
        return cnt;
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
        destroyNode(root);
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
        std::vector<Node<T> const *> remaining;
        Node<T> const *cur = other.root;
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
        preUpdateLast();
        updateLast();
        if (root) return iterator(cnt, last);
        else return iterator(cnt, root);
    }

    iterator end() noexcept {
        auto cnt = root;
        while (cnt && cnt->right) {
            cnt = cnt->right;
        }
        preUpdateLast();
        updateLast();
        if (cnt && cnt->right) cnt->right = last;
        if (root) return iterator(last, last);
        else return iterator(root, root);
    }


    const_iterator begin() const noexcept {
        auto cnt = root;
        while (cnt && cnt->left) {
            cnt = cnt->left;
        }
        preUpdateLast();
        updateLast();
        if (root) return const_iterator(cnt, last);
        else return const_iterator(cnt, root);
    }

    const_iterator end() const noexcept {
        auto cnt = root;
        while (cnt && cnt->right) {
            cnt = cnt->right;
        }
        preUpdateLast();
        updateLast();
        if (cnt && cnt->right) cnt->right = last;
        if (root) return const_iterator(last, last);
        else return const_iterator(cnt, root);
    }

 private:
    static void destroyNode(Node<T> *node) {
        if (node) {
            destroyNode(node->left);
            destroyNode(node->right);
            delete node;
        }
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

    void inOrderParentProblem(Node<T> *_root, Node<T> *__root) {
        if (_root && _root != last) {
            inOrderParentProblem(_root->left, _root);
            _root->parent = __root;
            inOrderParentProblem(_root->right, _root);
        }
    }
};