#include <iostream>
#include "treap.h"
#include <cstddef>

int main() {
    treap<int> treap2;
    treap2.insert(50);
    treap2.insert(30);
    treap2.insert(20);
    treap2.insert(40);
    treap2.insert(70);
    treap2.insert(60);
    treap2.insert(80);

    treap<int> treap1(treap2);

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

    return 0;
}