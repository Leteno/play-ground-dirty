
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class HasPtr {
public:
    HasPtr(const string& s = string(), int prio = 0) :
        ps(new string(s)), prio(prio), num(new size_t(1)) {}
    HasPtr(const HasPtr& ptr) {
        ++*ptr.num;
        ps = ptr.ps;
        num = ptr.num;
        prio = ptr.prio;
    }
    HasPtr& operator=(HasPtr ptr) {
        swap(*this, ptr);
        return *this;
    }
    bool operator<(HasPtr& ptr) {
        cout << "compare " << *ps << " with " << *ptr.ps << endl;
        return prio < ptr.prio;
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
    void setPrio(int prio) {
        this->prio = prio;
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

    vector<HasPtr> list;
    HasPtr item1("Hello", 1);
    HasPtr item2(" Mr.Zheng", 3);
    HasPtr item3(" World,", 2);
    list.push_back(item1);
    list.push_back(item2);
    list.push_back(item3);
    sort(list.begin(), list.end());

    for (auto it = list.begin(); it != list.end(); it++) {
        cout << it->get();
    }
    cout << endl;
    return 0;
}