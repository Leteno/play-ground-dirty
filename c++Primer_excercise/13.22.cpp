
#include <iostream>
#include <string>

using namespace std;

class HasPtr {
public:
    HasPtr() : number(nullptr), name(nullptr) {}
    HasPtr(int number, string name) : number(new int(number)), name(new string(name)) {}
    HasPtr(HasPtr& ptr) {
        number = new int(*ptr.number);
        name = new string(*ptr.name);
    }
    HasPtr &operator=(HasPtr& ptr) {
        int* oldNumber = number;
        string* oldName = name;

        number = new int(*ptr.number);
        name = new string(*ptr.name);
        delete oldNumber;
        delete oldName;
        return *this;
    }

    ~HasPtr() {
        cout << "destruction: " << *name << endl;
        delete number;
        delete name;
    }

    int *number;
    string* name;
};

int main() {

    HasPtr xiaoming(13, "XiaoMing");

    HasPtr xiaoming2(xiaoming), fakeId;
    fakeId = xiaoming;

    int* test = nullptr;
    delete test;

    *fakeId.number = 123;
    *fakeId.name = "Hacker";

    cout << "Xiaoming: " << *xiaoming.name << " " << *xiaoming.number << endl;

    *xiaoming2.number = 23;
    *xiaoming2.name = "xiaoming2";
    cout << "Xiaoming: " << *xiaoming.name << " " << *xiaoming.number << endl;

    return 0;
}