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
        copy(other.root, other.root);
    }

    treap operator=(const treap &other) {
        clear();
        copy(other.root, other.root);
        return *this;
    }

    void insert(Node<T> *&_root, Node<T> *elem) {
        if (!_root)
            _root = elem;
        else if (elem->prior > _root->prior)
            split(_root, elem->data, elem->left, elem->right), _root = elem;
        else
            insert(elem->data < _root->data ? _root->left : _root->right, elem);
    }

    Node<T> *search(Node<T> *_root, const T &data) {
        if (!_root || root->data == data)
            return _root;

        if (_root->data < data)
            return search(_root->right, data);

        return search(_root->left, data);
    }

    void erase(Node<T> *&_root, const T &data) {
        if (_root->data == data)
            merge(_root, _root->left, _root->right);
        else
            erase(data < _root->data ? _root->left : _root->right, data);
    }

    void merge(Node<T> *&_root, Node<T> *&left, Node<T> *&right) {
        if (!left || !right)
            _root = left ? left : right;
        else if (left->prior > right->prior)
            merge(left->right, left->right, right), _root = left;
        else
            merge(right->left, left, right->left), _root = right;
    }

    void split(Node<T> *_root, T &data, Node<T> *&left, Node<T> *&right) {
        if (!_root) {
            left = nullptr;
            right = nullptr;
        } else if (data < _root->data)
            split(_root->left, data, left, _root->left), right = _root;
        else
            split(_root->right, data, _root->right, right), left = _root;
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

    void copy(Node<T> *_root, Node<T> *_cur) {
        if (_cur) {
            copy(_root, _cur->left);
            insert(_root, _cur);
            copy(_root, _cur->right);
        }
    }
};
