#include <iostream>
#include "treap.h"
#include "test.h"
#include "my_set.h"
#include "timer.h"
#include <algorithm>

constexpr int test_size = 10000000;

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

    treap2.clear();
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

/*
key: 20 | priority: %d 266688984 | parent: 30
key: 30 | priority: %d 1316969908 | parent: 60 | left child: 20 | right child: 50
key: 40 | priority: %d 272062119 | parent: 50
key: 50 | priority: %d 1109799209 | parent: 30 | left child: 40
key: 60 | priority: %d 14167992570 | left child: 30 | right child: 80
key: 70 | priority: %d 276255807 | parent: 80
key: 80 | priority: %d 12832447970 | parent: 60 | left child: 70
*/

void test_set() {
    // set1 initialization
    std::cout << "default constructor test:";
    my_set<int> defSet;
    std::cout << defSet << "\n\n";

    std::cout << "range constructor test:\n";
    std::vector<int> vector = {10, 30, 20, 40, 50, 70, 60, 80, 90};
    std::cout << "vector elements: ";
    for (const auto &it : vector) std::cout << it << " ";
    std::cout << "\n";
    my_set<int> ranSet(vector.begin(), vector.end());
    std::cout << "set elements after initialization: " << ranSet << "\n\n";

    std::cout << "copy constructor test:\n";
    my_set<int> copySet1;
    for (size_t i = 10; i != 100; i += 10) copySet1.insert(i);
    std::cout << "set to copy elements: " << copySet1 << "\n";
    my_set<int> copySet2(copySet1);
    std::cout << "set elements after initialization: " << copySet2 << "\n\n";

    std::cout << "move constructor test:\n";
    my_set<int> moveSet1;
    for (size_t i = 10; i != 100; i += 10) moveSet1.insert(i);
    std::cout << "set to move elements: " << moveSet1 << "\n";
    my_set<int> moveSet2(std::move(moveSet1));
    std::cout << "set elements after initialization: " << moveSet2 << "\n\n";

    std::cout << "Initializer-list constructor test:\n";
    my_set<int> initSet({10, 20, 30, 40, 50, 60, 70, 80, 90});
    std::cout << "set elements after initialization: " << initSet << "\n\n";

    std::cout << "copy assignment operator test:\n";
    my_set<int> caoSet1({10, 20, 30, 40, 50, 60, 70, 80, 90});
    std::cout << "set to copy elements: " << caoSet1 << "\n";
    my_set<int> caoSet2 = {1, 2, 3};
    caoSet2 = caoSet1;
    std::cout << "set elements after operator=: " << caoSet2 << "\n\n";

    std::cout << "Move assignment operator:\n";
    my_set<int> opMoveSet1 = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    std::cout << "set to copy elements: " << opMoveSet1 << "\n";
    my_set<int> opMoveSet2;
    opMoveSet2 = std::move(opMoveSet1);
    std::cout << "set elements after operator= " << opMoveSet2 << "\n\n";

    std::cout << "operator= with initializer list: ";
    my_set<int> opInitSet1 = {1, 2, 3, 4};
    std::cout << opInitSet1 << "\n\n";

    std::cout << "capacity test: \n";
    my_set<int> capEmpty;
    my_set<int> cap = {1, 2, 3};
    std::cout << "empty set: " << capEmpty.empty() << "\n";
    std::cout << "non-empty set: " << cap.empty() << "\n\n";

    std::cout << "size test: \n";
    std::cout << "empty set: " << capEmpty.size() << "\n";
    std::cout << "non-empty set: " << caoSet1.size() << "\n\n";

    std::cout << "modifiers: \n";
    std::cout << "clear function test: \n";
    my_set<int> clearSet({1, 2, 3, 4, 5, 6});
    std::cout << "before clear(): " << clearSet << "empty(): " << clearSet.empty() << "\n";
    clearSet.clear();
    std::cout << "after clear(): " << clearSet << "empty(): " << clearSet.empty() << "\n\n";

    my_set<int> insertSet1;
    std::cout << "std::pair insert test: \n";
    std::cout << "elements I'm going to insert: 10, 10, 10, 20, 30, 40, 50, 60\n";
    for (const auto elem : {10, 10, 10, 20, 30, 40, 50, 60}) {
        auto cnt = insertSet1.insert(elem);
        std::cout << "first: " << *cnt.first << " second: " << cnt.second << " | ";
    }
    std::cout << "\n\n";

    my_set<int> insertSet2;
    std::cout << "std::pair insert test: \n";
    std::cout << "move() elements I'm going to insert: 10, 10, 10, 20, 30, 40, 50, 60\n";
    for (auto elem : {10, 10, 10, 20, 30, 40, 50, 60}) {
        auto cnt = insertSet2.insert(std::move(elem));
        std::cout << "first: " << *cnt.first << " second: " << cnt.second << " | ";
    }
    std::cout << "\n\n";

    my_set<int> insertSet3;
    std::cout << "inputIt insert test: ";
    std::vector<int> vector1 = {10, 10, 20, 30, 40};
    std::cout << "elements I'm going to insert using vector iterators: 10, 10, 20, 30, 40\n";
    insertSet3.insert(vector1.begin(), vector1.end());
    std::cout << "set after insert(): " << insertSet3 << "\n\n";

    my_set<int> insertSet4;
    std::cout << "ilist insert test: \n";
    std::cout << "elements I'm going to insert using vector ilist: 10, 10, 20, 30, 40\n";
    insertSet4.insert({10, 10, 20, 30, 40});
    std::cout << "set after insert(): " << insertSet4 << "\n\n";

    my_set<int> emplaceSet;
    std::cout << "emplace test: ";
    emplaceSet.emplace(10);
    std::cout << emplaceSet << "\n\n";

    my_set<int> eraseSet1({10, 20, 30, 40});
    std::cout << "single iterator erase test: \n";
    auto cnt1 = eraseSet1.erase(eraseSet1.cbegin());
    std::cout << "iterator which was returned: " << *cnt1 << "\n";
    std::cout << "set after erase(): " << eraseSet1 << "\n\n";

    my_set<int> eraseSet2({10, 20, 30, 40});
    std::cout << "several iterators erase test: \n";
    auto cnt2 = eraseSet2.erase(eraseSet2.cbegin(), --eraseSet2.cend());
    std::cout << "iterator which was returned: " << *cnt2 << "\n";
    std::cout << "set after erase(): " << eraseSet2 << "\n\n";

    my_set<int> eraseSet3({10, 20, 30, 40});
    std::cout << "erase 10 \n";
    std::cout << "bool = " << eraseSet3.erase(10) << " set after erase(): " << eraseSet3 << "\n\n";

    std::cout << "swap test:\n";
    my_set<int> swapSet1({1, 2, 3, 4});
    my_set<int> swapSet2({10, 20, 30, 40});
    std::cout << "before swap():\n" << "set1: " << swapSet1 << "\n" << "set2: " << swapSet2 << "\n\n";
    swapSet1.swap(swapSet2);
    std::cout << "after swap():\n" << "set1: " << swapSet1 << "\n" << "set2: " << swapSet2 << "\n\n";

    std::cout << "lookup functions:\n";
    my_set<int> lookupSet = {1, 2, 3, 5, 6};
    std::cout << "count() test: if elem in set " << lookupSet.count(2) << " | else: " << lookupSet.count(10) << "\n\n";

    std::cout << "iterator find() test: if elem in set " << *lookupSet.find(2) << " | else: "
              << (lookupSet.find(10) == nullptr) << "\n\n";

    std::cout << "lower_bound() test:\nelem = 0" << (lookupSet.lower_bound(0) == lookupSet.end()) << "\n";
    std::cout << "elem = 10: " << *lookupSet.lower_bound(10) << "\n";
    std::cout << "elem = 4: " << *lookupSet.lower_bound(4) << "\n\n";

    std::cout << "upper_bound() test:\n elem = 0: " << *lookupSet.upper_bound(0) << "\n";
    std::cout << "elem = 10: " << (lookupSet.upper_bound(10) == lookupSet.end()) << "\n";
    std::cout << "elem = 4: " << *lookupSet.upper_bound(4) << "\n\n";

    std::cout << "equal_range() test: ";
    std::cout << "elem = 4: first: " << *lookupSet.equal_range(4).first << " | second: "
              << *lookupSet.equal_range(4).second << "\n";

    std::cout << "non-member functions:\n";
    my_set<int> equalSet1 = {1, 2, 3};
    my_set<int> equalSet2 = {1, 2, 3};
    std::cout << "2 equal sets:\n";
    std::cout << "operator==: " << (equalSet1 == equalSet2) << "\n";
    std::cout << "operator<: " << (equalSet1 < equalSet2) << "\n";

    my_set<int> nonEqualSet1 = {1, 2};
    my_set<int> nonEqualSet2 = {1, 2, 3};
    std::cout << "2 nonEqual sets:\n";
    std::cout << "operator==: " << (nonEqualSet1 == nonEqualSet2) << "\n";
    std::cout << "operator<: " << (nonEqualSet1 < nonEqualSet2) << "\n";
}

void test_speed() {
    my_set<int> treap_set;
    Timer time;
    time.start();
    for (int i = 0; i < test_size; ++i)
        treap_set.insert(i);
    std::cout << "treap set sequential insert: " << time.getTime() << "\n\n";
    std::set<int> std_set;
    time.restart();
    for (int i = 0; i < test_size; ++i)
        std_set.insert(i);
    std::cout << "std set sequential insert: " << time.getTime() << "\n\n";

    time.restart();
    for (auto &elem : treap_set) (void) elem;
    std::cout << "treap set iteration: " << time.getTime() << "\n\n";

    time.restart();
    for (auto &elem : std_set) (void) elem;
    std::cout << "std set iteration: " << time.getTime() << "\n\n";

    time.restart();
    treap_set.clear();
    std::cout << "treap set clear: " << time.getTime() << "\n\n";

    time.restart();
    std_set.clear();
    std::cout << "std set clear: " << time.getTime() << "\n\n";

    time.restart();
    for (int i = test_size - 1; i >= 0; --i)
        treap_set.insert(i);
    std::cout << "treap set reverse order insert: " << time.getTime() << "\n\n";

    time.restart();
    for (int i = test_size - 1; i >= 0; --i)
        std_set.insert(i);
    std::cout << "std set reverse order insert: " << time.getTime() << "\n\n";

    time.restart();
    int find_start = rand() % (test_size);
    for (int i = 0; i < test_size; ++i)
        treap_set.find((find_start + i) % test_size);
    std::cout << "treap set find: " << time.getTime() << "\n\n";

    time.restart();
    int find_start1 = rand() % (test_size);
    for (int i = 0; i < test_size; ++i)
        std_set.find((find_start1 + i) % test_size);
    std::cout << "std set find: " << time.getTime() << "\n\n";

    time.restart();
    for (int i = 0; i < test_size; i += 5) {
        for (int j = 0; j < 5; ++j) treap_set.find((find_start + i) % test_size);
    }
    std::cout << "treap set find nearby: " << time.getTime() << "\n\n";

    time.restart();
    for (int i = 0; i < test_size; i += 5) {
        for (int j = 0; j < 5; ++j) std_set.find((find_start + i) % test_size);
    }
    std::cout << "std set find nearby: " << time.getTime() << "\n\n";

    time.restart();
    for (int i = 0; i < test_size; ++i)
        treap_set.erase(i);
    std::cout << "treap set erase: " << time.getTime() << "\n\n";

    time.restart();
    for (int i = 0; i < test_size; ++i)
        std_set.erase(i);
    std::cout << "std set erase: " << time.getTime() << "\n\n";
}

/* На 1000000
treap set sequential insert: 1.265

std set sequential insert: 1.546

treap set iteration: 0.047

std set iteration: 0.047

treap set clear: 0.125

std set clear: 0.156

treap set reverse order insert: 1.063

std set reverse order insert: 1.578

treap set find: 0.25

std set find: 0.781

treap set find nearby: 0.234

std set find nearby: 0.641

treap set erase: 0.203

std set erase: 0.985
*/

/* На 10000000
treap set sequential insert: 7.765

std set sequential insert: 11.031

treap set iteration: 0.438

std set iteration: 0.328

treap set clear: 1

std set clear: 1.203

treap set reverse order insert: 8.344

std set reverse order insert: 10.937

treap set find: 2.219

std set find: 5.813

treap set find nearby: 2.062

std set find nearby: 5.797

treap set erase: 2.172

std set erase: 9.906 */
