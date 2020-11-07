#include <iostream>
#include <memory>

int main() {
    auto sp = std::make_shared<int>(456);
    auto p = sp.get();
    delete p;
    std::cout << "After delete, sp: " << *sp << std::endl;
    *sp = 123;

    std::cout << "Now sp is: " << *sp << std::endl;
    return 0;
}

/**

After delete, sp: 456
Now sp is: 123

 */