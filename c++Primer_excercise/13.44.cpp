
#include <cstring>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class String {
public:
    String() : capacity(10), len(0) {
        start = alloc.allocate(capacity);
    } 
    String(char* buffer, int size) : len(0), capacity(0) {
        ensureSize(size);
        copy(0, buffer, size);
    }
    ~String() {
        free();
    }
    void append(char* buffer) {
        int size = strlen(buffer);
        ensureSize(size);
        copy(len, buffer, size);
    }
    string toString() {
        return string(start, len);
    }

private:
    allocator<char> alloc;
    char *start;
    int len;
    int capacity;

    void copy(int begin, char* buffer, int size) {
        char* end = uninitialized_copy_n(buffer, size, start + begin);
        len = end - start;
    }
    void free() {
        for (auto p = start + len; p != start;) {
            alloc.destroy(--p);
        }
        alloc.deallocate(start, capacity);
    }
    void ensureSize(int newWanted) {
        int expectSize = newWanted + len;
        if (expectSize > capacity) {
            if (capacity <= 0) {
                capacity = 8;
            }
            while (capacity < expectSize) capacity *= 2;
            auto newBuffer = alloc.allocate(capacity);
            uninitialized_copy_n(start, len, newBuffer);
            free();
            start = newBuffer;
        }
    }
};

int main()
{
    String str;
    str.append("Helloworld");
    str.append(" ");
    str.append("Mr.Zheng");
    str.append("\n");
    str.append("I guess you miss your friend very much !");

    cout << "str: " << str.toString() << endl;
    return 0;
}