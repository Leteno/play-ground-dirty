
#include <string>

using namespace std;

static int _id = 1;

class Employee {
public:
    Employee() : id(_id++) {}
    Employee(string name) : id(_id++), name(name) {}

private:
    int id;
    string name;
};