#include <iostream>
#include "treap.h"
#include "test.h"

int main() {
    treap<int> treap2;
    treap2.insert(50);
    treap2.insert(30);
    treap2.insert(20);
    treap2.insert(40);
    treap2.insert(70);
    treap2.insert(60);
    treap2.insert(80);
    std::cout << *treap2.begin();
    std::cout << (treap2.begin().parent());
    return 0;
}