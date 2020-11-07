#include <iostream>
#include <memory>
#include <vector>

std::shared_ptr<std::vector<int>> getVector() {
    return std::make_shared<std::vector<int>>(
        std::vector<int>{1, 2, 3}
    );
}

void print(std::shared_ptr<std::vector<int>> nums) {
    for (auto it = nums->begin(); it != nums->end(); it++) {
        std::cout << *it << std::endl;
    }
}

int main() {
    auto nums = getVector();
    print(nums);
    return 0;
}