#include <iostream>
#include <memory>

void process(std::shared_ptr<int> p) {
    std::cout << "process: " << *p << std::endl;
    *p = 12;
}

int main() {
    std::shared_ptr<int> p(new int(42));
    process(std::shared_ptr<int>(p.get()));
    std::cout << "after processing: " << *p << std::endl; 
    return 0;
}

/*
process: 42
after processing: 6822848

p is freed.

*/