//
// Created by Knight on 2019-08-16.
//

#include <cstdio>

class A {
public:
    A(int &c) : _b(2), _c(c) {
        _a = 1;
        printf("A construct\n");
    }

protected:
    int _a;
    const int _b;
    int &_c;
};

class B {

public:
    B(int &c) : _a(c) {
        printf("B contruct\n");
        printf("c: %d\n", c);
    }

protected:
    A _a;
};

int main() {

    int xx;
    int &a = xx;
    printf("a: %d\n", a);
    new B(a);

}