
// Test fork vector

#include <iostream>
#include <vector>

using namespace std;

class X {
public:
    X(int number) : x(number) {}

    int x;
};

int main()
{
    vector<X> vRaw, vConstruct1(vRaw);
    vRaw.push_back(X(1));
    if (vConstruct1.size()) {
        cout << "vConstruct1 has value: " << vConstruct1[0].x << endl;
    } else {
        cout << "vConstruct1 has no value" << endl;
    }

    vector<X> vConstruct2(vRaw), vAssignment;
    if (vConstruct2.size()) {
        cout << "vConstruct2 has value: " << vConstruct2[0].x << endl;
    } else {
        cout << "vConstruct2 has no value" << endl;
    }
    vAssignment = vRaw;
    if (vAssignment.size()) {
        cout << "vAssignment has value: " << vAssignment[0].x << endl;
    } else {
        cout << "vAssignment has no value" << endl;
    }
    vRaw.push_back(X(2));
    if (vAssignment.size() > 1) {
        cout << "vAssignment has new Value " << vAssignment[1].x << endl;
    } else {
        cout << "vAssignment has no new value" << endl;
    }
    if (vConstruct2.size() > 1) {
        cout << "vConstruct2 has new value: " << vConstruct2[1].x << endl;
    } else {
        cout << "vConstruct2 has no new value" << endl;
    }
    return 0;
}

/**

vConstruct1 has no value
vConstruct2 has value: 1
vAssignment has value: 1
vAssignment has no new value
vConstruct2 has no new value

vector 的拷贝构造函数，拷贝赋值函数，会生成新的存储空间并复制数组内元素。

所以成员变量有容器类，拷贝构造函数会创建新的容器来存储。
唯一要考虑的是 如果容器内元素数量过多的话，应考虑使用智能指针。

*/