#include <iostream>
#include "treap.h"
#include "test.h"

void test_treap() {
    treap<int> treap2;
    treap2.insert(50);
    treap2.insert(30);
    treap2.insert(20);
    treap2.insert(40);
    treap2.insert(70);
    treap2.insert(60);
    treap2.insert(80);

    treap<int> treap1;
    treap1 = treap2;

    std::cout << "Inorder traversal of the given tree \n";
    treap2.inOrder();

    std::cout << "\nDelete 20\n";
    treap2.erase(20);
    std::cout << "Inorder traversal of the modified tree \n";
    treap2.inOrder();

    std::cout << "\nDelete 30\n";
    treap2.erase(30);
    std::cout << "Inorder traversal of the modified tree \n";
    treap2.inOrder();

    std::cout << "\nDelete 50\n";
    treap2.erase(50);
    std::cout << "Inorder traversal of the modified tree \n";
    treap2.inOrder();

    Node<int> *res = treap2.search(50);
    (res == nullptr) ? std::cout << "\n50 Not Found " :
    std::cout << "\n50 found";

    std::cout << "\n\n\n";

    std::cout << "Inorder traversal of the given tree \n";
    treap1.inOrder();

    std::cout << "\nDelete 20\n";
    treap1.erase(20);
    std::cout << "Inorder traversal of the modified tree \n";
    treap1.inOrder();

    std::cout << "\nDelete 30\n";
    treap1.erase(30);
    std::cout << "Inorder traversal of the modified tree \n";
    treap1.inOrder();

    std::cout << "\nDelete 50\n";
    treap1.erase(50);
    std::cout << "Inorder traversal of the modified tree \n";
    treap1.inOrder();

    Node<int> *res1 = treap1.search(50);
    (res1 == nullptr) ? std::cout << "\n50 Not Found " :
    std::cout << "\n50 found";
}

void test_iterators() {
    treap<int> treap2;
    treap2.insert(50);
    treap2.insert(30);
    treap2.insert(20);
    treap2.insert(40);
    treap2.insert(70);
    treap2.insert(60);
    treap2.insert(80);
    std::cout << "++iterator\n";
    auto it = treap2.begin();
    while (it != treap2.end()) {
        std::cout << *it;
        ++it;
    }
    std::cout << "\n--iterator\n";
    while (it != treap2.begin()) {
        std::cout << *it;
        --it;
    }
    std::cout << "\nin-order\n";
    treap2.inOrder();
}