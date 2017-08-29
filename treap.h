#include <cstddef>
#include <random>
#include <iostream>
#include <stack>
// Добавить insert(begin, end);
#pragma once

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

    Node(Node *other) : data(other->data), prior(other->prior), left(other->left), right(other->right),
                        parent(other->parent) {}
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
        inOrderParentProblem(_root, nullptr);
    }

    void inOrderParentProblem(Node<T> *_root, Node<T> *__root) {
        if (_root) {
            inOrderParentProblem(_root->left, _root);
            _root->parent = __root;
            inOrderParentProblem(_root->right, _root);
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
            if (_root->parent)
                std::cout << " | parent: " << _root->parent->data;
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

        iterator(Node<T> *node) : current(node) {
        }

        iterator &operator=(const iterator &other) {
            std::move(current);
            current = new Node<T>(other.current);
            return *this;
        }

        bool operator==(iterator const &other) const { return current == other.current; }

        bool operator!=(iterator const &other) const { return current != other.current; }

        T &operator*() const { return static_cast<Node<T> *>(current)->data; }

        T *operator->() const { return &(static_cast<Node<T> *>(current)->data); }

        const iterator &operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }

        const iterator &operator--(int) {
            iterator result(*this);
            --(*this);
            return result;
        }

        iterator &operator++() {
            if (current == nullptr) {
                return *this;
            }
            Node<T> *n;
            if (current->left != nullptr) {
                /* '-> has left child node -> visit always */
                current = current->left;
            } else if (current->right != nullptr) {
                /* '-> only right child node -> visit always */
                current = current->right;
            } else {
                n = current;
                while (true) {
                    /* '-> traverse back until node with unvisited right neighbor or root */
                    if (n->parent == nullptr) {
                        current = nullptr;
                        break;
                    } else if (n == n->parent->left && n->parent->right != nullptr) {
                        current = n->parent->right;
                        break;
                    } else {
                        n = n->parent;
                    }
                }
            }
            return *this;
        }

        iterator &operator--() {
        }

        void Increment() {
            if (current == nullptr) {
                return;
            }
            // now we have a valid navigator
            if (current.HasRightChild())
                // slide down the left subtree of right child
            {
                current++;
                while (current.HasLeftChild())
                    +current;
            } else
                // back up to first ancestor not already visited
                // as long as we are parent's right child, then parent has been visited
            {
                bool navWasRightChild;
                do {
                    navWasRightChild = current.IsRightChild();
                    --current;
                } while (navWasRightChild);
            }
        }

        void Decrement() {
            if (current) {
                // note: -- on first element is undefined => we may safely move up if not left
                if (current == current->parent->arg_first()) {
                    // current is first child => move up
                    current = current->parent;
                } else {
                    // current is not first child => move up one step, then traverse down
                    // find pointer from parent
                    auto prev = --current->parent->arg_end();
                    for (; *prev != current; --prev);
                    --prev; // previous from current (prev can't be argv.front())
                    current = *prev;
                    // Now traverse down right most
                    while (!current->is_leaf()) current = current->arg_last();
                }
            } else {
                // current at end, so we need to use root to get to last element
                for (current = root; !current->is_leaf();) {
                    current = current->arg_last();
                }
            }
            return *this;
        }

        bool HasRightChild() const {
            if (current && current->right != 0)
                return 1;
            return 0;
        }

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
}