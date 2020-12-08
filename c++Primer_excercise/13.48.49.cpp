
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class String {
public:
    String() : capacity(10), len(0) {
        cout << "default constructor" << endl;
        start = alloc.allocate(capacity);
    }
    String(char* buffer) : len(0), capacity(0) {
        cout << "constructor(buffer)" << buffer << endl;
        int size = strlen(buffer);
        ensureSize(size);
        copy(0, buffer, size);
    }
    String(const String& str) {
        cout << "Copy constructor" << endl;
        start = alloc.allocate(str.capacity);
        uninitialized_copy_n(str.start, str.len, start);
        capacity = str.capacity;
        len = str.len;
    }
    String& operator=(const String& str) {
        cout << "assignment function" << endl;
        if (str.start == start) {
            return *this;
        }
        free();
        start = alloc.allocate(str.capacity);
        uninitialized_copy_n(str.start, str.len, start);
        capacity = str.capacity;
        len = str.len;
        return *this;
    }
    String(String&& str) {
        cout << "move construction" << endl;
        start = str.start;
        len = str.len;
        capacity = str.capacity;

        str.start = nullptr;
        str.len = str.capacity = 0;
    }
    String& operator=(String&& str) {
        cout << "move assignment" << endl;
        if (&str != this) {
            start = str.start;
            len = str.len;
            capacity = str.capacity;

            str.start = nullptr;
            str.len = str.capacity = 0;
        }
    }
    ~String() {
        cout << "destruction" << endl;
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
/**
int main()
{

    String str("Hello");
    String str2("World");

    vector<String> list;
    list.push_back(std::move(str));
    list.push_back(std::move(str2));
    list.push_back(std::move(String("Mr.Zheng")));
    list.push_back(std::move(String("Please take shower, ok?")));

    return 0;
}

/**
constructor(buffer)Hello
Execute debugger commands using "-exec <command>", for example "-exec info registers" will list registers in use (when GDB is the debugger)
constructor(buffer)World
move construction
move construction
Copy constructor
destruction
constructor(buffer)Mr.Zheng
move construction
Copy constructor
Copy constructor
destruction
destruction
destruction
constructor(buffer)Please take shower, ok?
move construction
destruction
destruction
destruction
destruction
destruction
destruction
destruction
 */

int main() {

    String str("Hello");
    String str2("World");

    vector<String> list;
    list.push_back(str);
    list.push_back(str2);
    list.push_back(String("Mr.Zheng"));
    list.push_back(String("Please take shower, ok?"));
    return 0;
}

/**
constructor(buffer)Hello
Execute debugger commands using "-exec <command>", for example "-exec info registers" will list registers in use (when GDB is the debugger)
constructor(buffer)World
Copy constructor
Copy constructor
Copy constructor
destruction
constructor(buffer)Mr.Zheng
move construction
Copy constructor
Copy constructor
destruction
destruction
destruction
constructor(buffer)Please take shower, ok?
move construction
destruction
destruction
destruction
destruction
destruction
destruction
destruction
*/