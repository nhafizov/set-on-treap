#include <iostream>
#include "treap.h"
#include "test.h"
#include "my_set.h"

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
        --it;
        std::cout << *it;
    }
    std::cout << "\nin-order\n";
    treap2.inOrder();
}

void test_set() {
    // set1 initialization
    std::cout << "default constructor test:\n";
    my_set<int> defSet;
    std::cout << defSet;

    std::cout << "range constructor test:\n";
    std::vector<int> vector = {10, 30, 20, 40, 50, 70, 60, 80, 90};
    std::cout << "vector elements:\n";
    for (const auto &it : vector) std::cout << it << " ";
    std::cout << "\n";
    my_set<int> ranSet(vector.begin(), vector.end());
    std::cout << "set elements after initialization:\n";
    std::cout << ranSet;

    std::cout << "copy constructor test:\n";
    my_set<int> copySet1;
    for (size_t i = 10; i != 100; i += 10) copySet1.insert(i);
    std::cout << "set to copy:\n";
    std::cout << copySet1;
    std::cout << "set elements after initialization:\n";
    my_set<int> copySet2(copySet1);
    std::cout << copySet2;

    std::cout << "move constructor test:\n";
    my_set<int> moveSet1;
    for (size_t i = 10; i != 100; i += 10) moveSet1.insert(i);
    std::cout << "set to copy:\n";
    std::cout << moveSet1;
    std::cout << "set elements after initialization:\n";
    my_set<int> moveSet2(std::move(moveSet1));
    std::cout << moveSet2;

    std::cout << "Initializer-list constructor test:\n";
    my_set<int> initSet = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    std::cout << initSet;

    std::cout << "copy assignment operator test:\n";
    my_set<int> caoSet = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    std::cout << "set to operator:\n";


//    my_set<int> set1;
//    set1.insert(30);
//    set1.insert(20);
//    set1.insert(40);
//    set1.insert(50);
//    set1.insert(70);
//    set1.insert(60);
//    set1.insert(80);
//
//    my_set<int> set2(std::move(set1));
//
//    std::cout << "set1 print\n";
//    std::cout << set1;
//
//    std::cout << "\nDelete 20\n";
//    set1.erase(20);
//    std::cout << "set1 print\n";
//    std::cout << set1;
//
//    std::cout << "\nDelete 30\n";
//    set1.erase(30);
//    std::cout << "\nset1 print\n";
//    std::cout << set1;
//
//    std::cout << "\nDelete 50\n";
//    set1.erase(50);
//    std::cout << "\nset1 print\n";
//    std::cout << set1;
//
//    my_set<int>::iterator res = set1.find(50);
//    (res == nullptr) ? std::cout << "\n50 Not Found " :
//    std::cout << "\n50 found";
//
//    std::cout << "\n\n\n copy constructor\\operator\n";
//
//    std::cout << "set2 print\n";
//    std::cout << set2;
//
//    std::cout << "\nDelete 20\n";
//    set2.erase(20);
//    std::cout << "\nset2 print\n";
//    std::cout << set2;
//
//    std::cout << "\nDelete 30\n";
//    set2.erase(30);
//    std::cout << "\nset2 print\n";
//    std::cout << set1;
//
//    std::cout << "\nDelete 50\n";
//    set2.erase(50);
//    std::cout << "\nset2 print\n";
//    std::cout << set2;
//
//    my_set<int>::iterator res2 = set2.find(50);
//    (res2 == nullptr) ? std::cout << "\n50 Not Found " :
//    std::cout << "\n50 found";
}