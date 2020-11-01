#include <functional>
#include <iostream>

int add(int a, int b) {
    return a + b;
}

int minus(int a, int b) {
    return a - b;
}

int exec(std::function<int (int, int)> func, int a, int b) {
    if (func) {
        return func(a, b);
    }
    /* Error code */
    return -1;
}

int main()
{
    int add1_2 = exec(add, 1, 2);
    int minus3_1 = exec(minus, 3, 1);
    std::cout << "add 1, 2 " << add1_2
        << (add1_2 == 3 ? " pass !" : " fail !") << std::endl;
    std::cout << "minus 3, 1 " << minus3_1
        << (minus3_1 == 2 ? " pass !" : " fail !") << std::endl;
    return 0;
}