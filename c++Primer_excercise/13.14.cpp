#include <iostream>

using namespace std;

static int _mysn = 1;

class numbered {
public:
    numbered() : mysn(_mysn++) {}

    int mysn;
};

void f(numbered s) {
    cout << s.mysn << endl;
}

int main()
{
    numbered a, b = a, c = b;
    f(a); f(b); f(c);
    return 0;
}

/**
 * 1, 1, 1
 */