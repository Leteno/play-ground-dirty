
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

class CharArray {
public:
    CharArray() : current(0), size(8) {
        std::allocator<char> alloc;
        char* p = alloc.allocate(size);
        data = std::make_shared<char*>(p);
        std::uninitialized_fill_n(p, size, 0);
    }

    const char* currentVal() {
        return *data;
    }

    void append(std::string append) {
        int _size = append.size();
        if (current + _size >= size) {
            std::allocator<char> alloc;
            int newSize = size + _size * 2;
            char* newArea = alloc.allocate(newSize);
            auto copyEndPtr = std::uninitialized_copy_n(*data, current, newArea);
            std::uninitialized_fill_n(copyEndPtr, newSize - current, 0);
            data = std::make_shared<char*>(newArea);
            this->size = newSize;
        }
        std::uninitialized_copy_n(append.begin(), _size, (*data) + current);
        current += _size;
    }

private:
    int current, size;
    std::shared_ptr<char*> data;
};


int main()
{
    CharArray a;

    for (int i = 0; i < 10000; i++) {
        std::vector<std::string> tests;
        tests.push_back("Hello");
        tests.push_back("World ");
        tests.push_back("Mr.Zheng");
        tests.push_back(" Love");
        tests.push_back(" You");
        tests.push_back(" Miss.");
        tests.push_back("Jiang");

        for (auto it = tests.begin(); it != tests.end(); it++) {
            std::cout << "adding " << *it << std::endl;
            a.append(*it);
            std::cout << "current: " << a.currentVal() << std::endl;
        }
        if (i == 5000 || i == 7500 || i == 9999) {
            continue;
        }
    }
    return 0;
}