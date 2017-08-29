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
    auto it = treap2.begin();
    while (++it != treap2.end()) {
        std::cout << *it << "\n";
    }
    treap2.inOrder();
    return 0;
}
//        80
//      20
//        30
//           50
//         40  60
//               70
