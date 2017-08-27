#include <cstddef>
#include <random>
#include <iostream>

#pragma once

const size_t mod = 32416187567;

template<typename T>
struct Node {
    T data;
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
 private:
    Node<T> *root = nullptr;

    static void destroyNode(Node<T> *node) {
        if (node) {
            destroyNode(node->left);
            destroyNode(node->right);
            delete node;
        }
    }

 public:
    treap() {}

    explicit treap(const treap &other) {
        copy(other);
    }

    treap &operator=(const treap &other) {
        clear();
        copy(other);
        return *this;
    }

    Node<T> *search(Node<T> *_root, const T &data) {
        if (!_root || root->data == data)
            return _root;

        if (_root->data < data)
            return search(_root->right, data);

        return search(_root->left, data);
    }

    void insert(Node<T> *&_root, Node<T> *elem) {
        if (!_root) {
            _root = elem;
        } else if (elem->prior > _root->prior) {
            split(_root, elem->data, elem->left, elem->right);
            _root = elem;
        } else {
            insert(elem->data < _root->data ? _root->left : _root->right, elem);
        }
    }

    void split(Node<T> *_root, T &data, Node<T> *&left, Node<T> *&right) {
        if (!_root) {
            left = nullptr;
            right = nullptr;
        } else if (data < _root->data) {
            split(_root->left, data, left, _root->left);
            if (left->parent)
                left->parent = _root;
            right = _root;
        } else {
            split(_root->right, data, _root->right, right);
            if (right->parent)
                left->parent = _root;
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
        auto __root = _root;
        if (!left || !right) {
            _root = left ? left : right;
        } else if (left->prior > right->prior) {
            merge(left->right, left->right, right);
            _root = left;
        } else {
            merge(right->left, left, right->left);
            _root = right;
        }
        if (_root && _root->left)
            _root->left->parent = __root;
        if (_root && _root->right)
            _root->right->parent = __root;
    }

    ~treap() {
        clear();
    }

    // useful functions implementation
    void insert(const T &data) {
        Node<T> *_elem = new Node<T>(data);
        insert(root, _elem);
    }

    Node<T> *search(const T &data) {
        return search(root, data);
    }

    void erase(const T &data) {
        erase(root, data);
    }

    void clear() {
        destroyNode(root);
    }

    void merge(Node<T> *&left, Node<T> *&right) {
        merge(root, left, right);
    }

    void split(T &data, Node<T> *&left, Node<T> *&right) {
        split(root, data, left, right);
    }

    void inOrder(Node<T> *_root) {
        if (_root) {
            inOrder(_root->left);
            std::cout << "key: " << _root->data << " | priority: %d "
                      << _root->prior;
            if (_root->left)
                std::cout << " | left child: " << _root->left->data;
            if (_root->right)
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
        Node<T> *current;

     public:
        iterator() {}

        iterator(Node<T> *node) : current(node) {}

        iterator &operator=(const iterator &other) {
            std::move(current);
            current = new Node<T>(other.current);
            return *this;
        }

        bool operator==(iterator const &other) const { return current == other.current; }

        bool operator!=(iterator const &other) const { return current != other.current; }

        iterator &operator++() {
            if (current->right != nullptr) {
                current = current->right;
                while (current->left != nullptr) {
                    current = current->left;
                }
            } else {
                while (current->parent != nullptr && current->parent->right == current) {
                    current = current->parent;
                }
                if (current->parent != nullptr)
                    current = current->parent;
            }
            return *this;
        }

        Node<T> *parent() {
            if (current && current->parent)
                return current->parent;
        }

        iterator &operator--() {
//            Node<T> *parent;
//
//            if (this->current == nullptr) {
//                /* '-> begin iterator does not decrement */
//                return *this;
//            }
//            parent = this->current->parent;
//            /*
//             * reaches root -> next is end()
//             */
//            if (parent == nullptr) {
//                this->current = nullptr;
//                return *this;
//            }
//
//            /*
//             * left child -> go to right child
//             * right child -> go to parent
//             */
//            if ((this->current == parent->left) && (parent->right != nullptr)) {
//                this->current = parent->right;
//            } else {
//                this->current = this->current->parent;
//                return *this;
//            }
//            while (true) {
//                if (this->current->left != nullptr) {
//                    /* '-> has left child node */
//                    this->current = this->current->left;
//                } else if (this->current->right != nullptr) {
//                    /* '-> only right child node */
//                    this->current = this->current->right;
//                } else {
//                    /* '-> has no children -> stop here */
//                    return *this;
//                }
//            }
        }

        const iterator &operator++(int) {
            iterator result(*this);
            ++(*this);
            return result;
        }

        const iterator &operator--(int) {
            iterator result(*this);
            --(*this);
            return result;
        }

        T &operator*() const { return static_cast<Node<T> *>(current)->data; }

        T *operator->() const { return &(static_cast<Node<T> *>(current)->data); }
    };

    iterator begin() noexcept {
        auto cnt = root;
        while (cnt && cnt->left) {
            cnt = cnt->left;
        }
        return iterator(cnt);
    }

    iterator end() noexcept {
        return iterator(nullptr);
    }
};
