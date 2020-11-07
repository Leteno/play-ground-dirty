#include <iostream>
#include <memory>

void process(std::shared_ptr<int> p) {
    std::cout << "process: " << *p << std::endl;
}

int main() {
    auto p = new int;
    auto sp = std::make_shared<int>();
    process(sp);
    // no suitable constructor exists to convert from "int *" to "std::shared_ptr<int>"
    // process(new int());
    // process(p);
    process(std::shared_ptr<int>(p));
    return 0;
}