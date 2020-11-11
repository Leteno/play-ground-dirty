
#include <iostream>
#include <memory>
#include <cstring>
#include <vector>

auto deleteLambda = [](char* chs){
    std::cout << "delete chars: " << chs << std::endl;
    delete [] chs;   
};

class Array {

public:
    Array() : current(0), size(8),
        str(new char[size], deleteLambda) {
    }

    void append(const char* buffer, int _size) {
        if (size < current + _size) {

            int newSize = getNewSize(_size);
            auto newData = new char[newSize];
            for (int i = 0; i <= current; i++) {
                newData[i] = str[i];
            }
            str.reset(newData, deleteLambda);
            size = newSize;
        }
        for (int i = 0; i < _size; i++, current++) {
            str[current] = buffer[i];
        }
        str[current] = '\0';
    }

    char* currentVal() {
        return str.get();
    }

private:
    int getNewSize(int wantedSize) {
        return size + wantedSize * 2 + 1;
    }
    int size;
    int current;
    std::shared_ptr<char[]> str;
};


int main() {

    Array a;

    auto tests = {
        "Hello",
        "World ",
        "Mr.Zheng",
        " Love",
        " You",
        " Miss.",
        "Jiang"
    };
    for (auto it = tests.begin(); it != tests.end(); it++) {
        std::cout << "adding " << *it << std::endl;
        a.append(*it, strlen(*it));
        std::cout << "current: " << a.currentVal() << std::endl;
    }

    return 0;
}

/***
adding Hello
current: Hello
adding World
delete chars: Hello
current: HelloWorld
adding Mr.Zheng
current: HelloWorld Mr.Zheng
adding  Love
delete chars: HelloWorld Mr.Zheng
current: HelloWorld Mr.Zheng Love
adding  You
current: HelloWorld Mr.Zheng Love You
adding  Miss.
delete chars: HelloWorld Mr.Zheng Love You
current: HelloWorld Mr.Zheng Love You Miss.
adding Jiang
current: HelloWorld Mr.Zheng Love You Miss.Jiang
delete chars: HelloWorld Mr.Zheng Love You Miss.Jiang

**/