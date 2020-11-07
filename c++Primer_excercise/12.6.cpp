#include <iostream>
#include <vector>

std::vector<int>* getVector() {
    return new std::vector<int>{1, 2, 3};
}

void print(std::vector<int>* nums) {
    for (auto it = nums->begin(); it != nums->end(); it++) {
        std::cout << *it << std::endl;
    }
}

int main() {
    auto nums = getVector();
    print(nums);
    delete nums;
    return 0;
}