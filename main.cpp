#include "Container.h"
#include "iostream"

void test1() {
    Container<int> test1;
    test1.addFirst(1);
    test1.addLast(2);
    int b = test1.getFirst();
    b++;
    int &c = test1.getFirst();
    c--;
    int result = test1.getFirst();
    std::cout << b << c << test1.getFirst() << std::endl;
    test1.clearContainer();
    std::cout << test1.getFirst() << std::endl;
}

void test2() {
    Container<int> test2;
    for (int i = 0; i < 10; i++) {
        test2.addLast(i);
    }

    int count = 50;

    for (Container<int>::iterator k = test2.begin(); k != test2.end(); ++k) {
        std::cout << *k << std::endl;
//        std::cout << "iteration " <<  count << std::endl;
        k = count;
        count++;
    }

    std::cout << std::endl;

    for (Container<int>::iterator k = test2.begin(); k != test2.end(); ++k) {
        std::cout << *k << std::endl;
    }
}

int main() {

//    test1();
    test2();

}