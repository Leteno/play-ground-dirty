

#include <iostream>
#include <string>

using namespace std;

class HasPtr {
public:
    HasPtr(const string& s = string()) :
        ps(new string(s)), prio(0), num(new size_t(1)) {}
    HasPtr(HasPtr& ptr) {
        ++*ptr.num;
        ps = ptr.ps;
        num = ptr.num;
        prio = ptr.prio;
    }
    HasPtr& operator=(HasPtr ptr) {
        swap(*this, ptr);
        return *this;
    }
    ~HasPtr() {
        cout << "destruct " << *ps << endl;
        if (--*num == 0) {
            cout << "Free now" << *ps << endl;
            delete ps;
            delete num;
        }
    }
    string& get() {
        if (num) {
            return *ps;
        }
        throw "HasPtr should be deconstructed";
    }
    void swap(HasPtr& lhs, HasPtr&rhs) {
        cout << "calling swap " << *lhs.ps << " " << *rhs.ps << endl;
        using std::swap;
        swap(lhs.ps, rhs.ps);
        swap(lhs.num, rhs.num);
        swap(lhs.prio, rhs.prio);
    }

private:
    string *ps;
    int prio;
    size_t *num;
};

int main() {
    HasPtr ptr("Hello");
    HasPtr ptr1(ptr), ptr2;
    ptr2 = ptr;
    ptr.get().append(" world");
    cout << "ptr1 " << ptr1.get() << endl;
    cout << "ptr2 " << ptr2.get() << endl;
    return 0;
}