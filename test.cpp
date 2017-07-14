#include "test.h"
#include "treap.cpp"

void test_treap() {
    treap<int> treap;
    treap.insert(50);
    treap.insert(30);
    treap.insert(20);
    treap.insert(40);
    treap.insert(70);
    treap.insert(60);
    treap.insert(80);

    std::cout << "Inorder traversal of the given tree \n";
    treap.inOrder();

    std::cout << "\nDelete 20\n";
    treap.erase(20);
    std::cout << "Inorder traversal of the modified tree \n";
    treap.inOrder();

    std::cout << "\nDelete 30\n";
    treap.erase(30);
    std::cout << "Inorder traversal of the modified tree \n";
    treap.inOrder();

    std::cout << "\nDelete 50\n";
    treap.erase(50);
    std::cout << "Inorder traversal of the modified tree \n";
    treap.inOrder();

    Node<int> *res = treap.search(50);
    (res == nullptr) ? std::cout << "\n50 Not Found " :
    std::cout << "\n50 found";
}

void test_set() {}