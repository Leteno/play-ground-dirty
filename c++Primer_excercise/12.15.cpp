#include <iostream>
#include <memory>

struct destination {
    destination(std::string s): dest_str(s) {
        std::cout << "constructor destination" << std::endl;
    }
    ~destination() {
        std::cout << "destructor destination" << std::endl;
    }

    std::string dest_str;
};
struct connection {
    connection(destination* dest): dest{dest} {
        std::cout << "constructor connection" << std::endl;
    }
    ~connection() {
        std::cout << "destructor connection" << std::endl;
        dest = nullptr;
    }
    void disconnect() {
        std::cout << "disconnect " << dest->dest_str << std::endl;
    }
    destination* dest;
};

connection connect(destination* dest) {
    std::cout << "connect()" << std::endl;
    return connection(dest);
}

void disconnect(connection* conn) {
    std::cout << "disconnect()" << std::endl;
    conn->disconnect();
}

void f1(destination &d) {
    connection c = connect(&d);

    throw "I mean it";

    disconnect(&c);
}

void f2(destination &d) {
    connection c = connect(&d);
    std::shared_ptr<connection> cp(&c, [](connection* conn) {
        disconnect(conn);
    });

    throw "I mean it";

    disconnect(&c);
}

int main() {

    destination dest("Hello world");

    try {
        f1(dest);
    } catch (const char* msg) {
        // I don't see it.
    }

    std::cout << "f1 finish" << std::endl;

    try {
        f2(dest);
    } catch (const char* msg) {
        // I don't see it.
    }

    std::cout << "f2 finish" << std::endl;

    return 0;
}